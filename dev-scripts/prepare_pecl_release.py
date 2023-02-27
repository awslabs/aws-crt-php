import argparse
import os
import subprocess
import xml.dom.minidom
import sys


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


def run(args):
    print(f"$ {subprocess.list2cmdline(args)}")
    subprocess.check_call(args)


run(['python3', f'{TOOLS_DIR}/cleanup_build.py'])

os.chdir(WORK_DIR)

run(['git', 'submodule', 'update', '--init', '--recursive'])

try:
    run(['python3', f'{TOOLS_DIR}/prepare_pecl_package_xml.py', '--name', NAME, '--user', USER,
                    '--email', EMAIL, '--version', VERSION, '--notes', NOTES])
except subprocess.CalledProcessError as e:
    sys.exit(f'ERROR PROCESSING review package.xml: {e}')

with open('package.xml', 'r') as f:
    package_xml = f.read()
doc = xml.dom.minidom.parse('package.xml')
doc.encoding = 'UTF-8'
xml_str = doc.toprettyxml(indent=' ', newl='')
with open('package.xml', 'w') as f:
    f.write(xml_str)
run(['pear', 'package-validate'])
run(['pear', 'package'])

print(f'Size of {PACKAGE}-{VERSION}.tgz: {os.path.getsize(f"{PACKAGE}-{VERSION}.tgz") / 1024 / 1024:.2f} MB')
