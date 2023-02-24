import argparse
import os
import subprocess
import xml.dom.minidom


parser = argparse.ArgumentParser(description='PECL Package generator')
parser.add_argument("--name", help="Name of the package", required=True)
parser.add_argument(
    "--user", help="Username of the package maintainer", required=True)
parser.add_argument(
    "--email", help="Email address of the package maintainer", default='aws-sdk-common-runtime@amazon.com')
parser.add_argument(
    "--version", help="Version number of the package", required=True)
parser.add_argument(
    "--notes", help="Release notes for the package", default='New release')
args = parser.parse_args()

PACKAGE = 'awscrt'
NAME = args.name
USER = args.user
EMAIL = args.email
VERSION = args.version
NOTES = args.notes

TOOLS_DIR = os.path.dirname(os.path.abspath(__file__))
WORK_DIR = os.path.join(TOOLS_DIR, '..')

subprocess.run(['python3', f'{TOOLS_DIR}/cleanup_build.py'], check=True)

os.chdir(WORK_DIR)

subprocess.run(['git', 'submodule', 'update',
               '--init', '--recursive'], check=True)

subprocess.run(['python3', f'{TOOLS_DIR}/prepare_pecl_package_xml.py', '--name', NAME, '--user', USER,
                '--email', EMAIL, '--version', VERSION, '--notes', NOTES], check=True)
try:
    with open('package.xml', 'r') as f:
        package_xml = f.read()
    doc = xml.dom.minidom.parse('package.xml')
    doc.encoding = 'UTF-8'
    xml_str = doc.toprettyxml(indent=' ', newl='')
    with open('package.xml', 'w') as f:
        f.write(xml_str)
    subprocess.run(['pear', 'package-validate'], check=True)
    subprocess.run(['pear', 'package'], check=True)
except subprocess.CalledProcessError as e:
    print(f'ERROR PROCESSING review package.xml: {e}')
    exit(1)

print(f'Size of {PACKAGE}-{VERSION}.tgz: {os.path.getsize(f"{PACKAGE}-{VERSION}.tgz") / 1024 / 1024:.2f} MB')
