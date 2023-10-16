#!/usr/bin/env python3
import argparse
import os
import re
from datetime import datetime

parser = argparse.ArgumentParser(
    description="Generate package.xml file for a release bundle.")
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


name = args.name
user = args.user
email = args.email
version = args.version
notes = args.notes


tools_dir = os.path.dirname(os.path.abspath(__file__))
work_dir = os.path.join(tools_dir, '..')

os.chdir(work_dir)

today = datetime.utcnow().strftime("%Y-%m-%d")

source_ext = "(c|cc|h|cpp|hpp|m4|w32|ini|frag|cmake|inl|in|py|gnu|yaml|def|pl|S|s|errordata|go|lds|num|asm|mod|peg|mk|rs|toml|sh|toolchain|flags)"
doc_ext = "(md|json|html|dot|graphml|png|gn|sha1|css|rst)"

special_docs = "(LICENSE.*|NOTICE|changelog.txt|CHANGELOG|THIRD-PARTY|README.*|readme|METADATA|CONTRIBUTORS|UPDATING|doc.config|THIRD-PARTY-LICENSES.txt)"
special_tests = "(ci-test.sh|format-check.sh|run_tests.*|sanitizer-blacklist.txt|run-clang-tidy.sh|benchmark-build-run.sh|break-tests.sh|generate-coverage.sh|test.xml)"
special_src = "(gen_api.php|gen_stub.php|CMakeLists.txt|post.sh|postun.sh|Makefile.*|build-buildspec.sh|build-deps.sh|objects.txt|go.*|BUILD.*|DEPS|install_and_run.sh|codemod.sh|requirements.txt|awscrt.stub.php)"
skip_files = "(package.xml.*|prepare_release.sh|codereview.settings|.*\\.o|.*\\.a|.*\\.obj|.*\\.lib|break-tests-android.sh|whitespace.txt|prepare_package_xml.sh|crypto_test_data.cc|flake.lock|flake.nix|.*\\.pdf|.*\\.svg|.*\\.docx|cbmc-proof.txt|codecov.*|litani.*|.*\\.toml|module\\.modulemap|cleanup.sh|^\..*)"

skip_directories = "(tests|test|AWSCRTAndroidTestRunner|docker-images|codebuild|fuzz|third_party|docs|generated-src|aws-lc|aws-crt-sys|ecdsa-fuzz-corpus|bin|examples|compliance|verification|dev-scripts|nix|^\..*)"

output_file_name = os.path.join(work_dir, 'package.xml')


def process_file(file_name, f):
    if re.match(skip_files, file_name):
        # This file is not part of the release bundle
        return
    f.write(f'<file name="{file_name}" role="')
    # Special cases
    if re.match(special_docs, file_name):
        f.write('doc')
    elif re.match(special_tests, file_name):
        f.write('test')
    elif re.match(special_src, file_name):
        f.write('src')
    else:
        # Extension based cases
        ext = file_name.split('.')[-1]
        if re.match(source_ext, ext):
            f.write('src')
        elif re.match(doc_ext, ext):
            f.write('doc')
        elif ext == 'php':
            f.write('script')
        else:
            f.write(f'{ext} - {file_name} - FAIL TO RECOGNIZE')
            print(f'{ext} - {file_name} - FAIL TO RECOGNIZE')
            exit(1)

    f.write('"/>\n')


def process_dir(dir_name, f):
    if re.match(skip_directories, dir_name):
        return

    f.write(f'<dir name="{dir_name}">\n')
    os.chdir(dir_name)
    for file_name in os.listdir():
        if os.path.isfile(file_name):
            process_file(file_name, f)
        else:
            process_dir(file_name, f)

    # Special cases for compiler features placed in tests directories in and s2n
    if dir_name == 's2n' and os.path.isdir('tests'):
        f.write('<dir name="tests">')
        f.write('<dir name="features">')
        os.chdir('tests/features')
        for a in os.listdir():
            process_file(a, f)
        os.chdir('../..')
        f.write('</dir>')
        f.write('</dir>')

    f.write('</dir>')
    os.chdir('..')


# Main code
with open(os.path.join(tools_dir, "package.xml-template_pre"), 'r') as f:
    template_pre = f.read()

template_pre = re.sub(r"{{{NAME}}}", name, template_pre)
template_pre = re.sub(r"{{{USER}}}", user, template_pre)
template_pre = re.sub(r"{{{EMAIL}}}", email, template_pre)
template_pre = re.sub(r"{{{TODAY}}}", today, template_pre)
template_pre = re.sub(r"{{{VERSION}}}", version, template_pre)
template_pre = re.sub(r"{{{NOTES}}}", notes, template_pre)

with open(output_file_name, "w") as f:
    f.write(template_pre)
    f.write('<dir name="/">\n')

with open(output_file_name, "a") as f:
    for file_name in os.listdir():
        if file_name == 'tests':
            f.write('<dir name="tests">\n')
            for test_file in os.listdir('tests'):
                f.write(
                    f'<file name="{os.path.basename(test_file)}" role="test" />\n')
            f.write('</dir>\n')
            continue

        if file_name == 'src':
            # skip the src directory as it is not part of the native extension
            continue

        if os.path.isfile(file_name):
            process_file(file_name, f)
        else:
            process_dir(file_name, f)

with open(output_file_name, "a") as f:
    f.write('</dir>\n')
    with open(os.path.join(tools_dir, "package.xml-template_post"), 'r') as template:
        f.write(template.read())
