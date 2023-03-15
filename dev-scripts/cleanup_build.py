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
    'cmake_build',
    'include',
    'modules',
    'vendor',
    'autom4te.cache']

# Remove specified files
FILES_TO_REMOVE = [
    'Makefile',
    'Makefile.fragments',
    'Makefile.global',
    'Makefile.objects',
    'config.guess',
    'config.h',
    'config.h.in',
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
    'ext/awscrt.dep',
    'composer.lock',
    'acinclude.m4',
    'aclocal.m4',
    '**/*.lo',
    '**/*.o',
    '**/*.la',
    '**/*.a',
    '*.tgz']

os.chdir(WORK_DIR)


for directory in DIRS_TO_REMOVE:
    shutil.rmtree(directory, ignore_errors=True)

for pattern in FILES_TO_REMOVE:
    for filepath in glob.glob(pattern):
        os.remove(filepath)
