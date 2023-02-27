import os
import glob
import shutil

TOOLS_DIR = os.path.dirname(os.path.abspath(__file__))
WORK_DIR = os.path.join(TOOLS_DIR, '..')

# Remove specified directories
DIRS_TO_REMOVE = [
    '.deps',
    '.libs',
    'build',
    'include',
    'modules',
    'vendor']

# Remove specified files
FILES_TO_REMOVE = [
    'Makefile',
    'Makefile.fragments',
    'Makefile.global',
    'Makefile.objects',
    'config.guess',
    'config.h',
    'config.log',
    'config.nice',
    'config.status',
    'config.sub',
    'configure',
    'configure.in',
    'configure.ac',
    'install-sh',
    'libtool',
    'ltmain.sh',
    'missing',
    'mkinstalldirs',
    'run-tests.php',
    'awscrt.la',
    'composer.lock',
    'ext/awscrt.stub.php',
    'acinclude.m4',
    'aclocal.m4',
    'autom4te.cache']


def remove_files(files):
    for file in files:
        if os.path.exists(file):
            os.remove(file)


os.chdir(WORK_DIR)


for directory in DIRS_TO_REMOVE:
    shutil.rmtree(directory, ignore_errors=True)

# Remove all .lo and .o files
FILES_TO_REMOVE += glob.glob(os.path.join(WORK_DIR, '**/*.lo'))
FILES_TO_REMOVE += glob.glob(os.path.join(WORK_DIR, '**/*.o'))

# Remove all .la and .a files
FILES_TO_REMOVE += glob.glob(os.path.join(WORK_DIR, '**/*.la'))
FILES_TO_REMOVE += glob.glob(os.path.join(WORK_DIR, '**/*.a'))
# Remove all .tgz files
FILES_TO_REMOVE += glob.glob(os.path.join(WORK_DIR, '*.tgz'))

remove_files(FILES_TO_REMOVE)
