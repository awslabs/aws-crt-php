import os
import glob
import shutil

TOOLS_DIR = os.path.dirname(os.path.abspath(__file__))
WORK_DIR = os.path.join(TOOLS_DIR, '..')


def remove_files(files):
    for file in files:
        if os.path.exists(file):
            os.remove(file)


os.chdir(WORK_DIR)

# Remove specified directories
dirs_to_remove = ['.deps', '.libs', 'build', 'include', 'modules', 'vendor']
for directory in dirs_to_remove:
    shutil.rmtree(directory, ignore_errors=True)

# Remove specified files
files_to_remove = ['Makefile', 'Makefile.fragments', 'Makefile.global', 'Makefile.objects',
                   'config.guess', 'config.h', 'config.log', 'config.nice', 'config.status',
                   'config.sub', 'configure', 'configure.in', 'configure.ac', 'install-sh',
                   'libtool', 'ltmain.sh', 'missing', 'mkinstalldirs', 'run-tests.php',
                   'awscrt.la', 'composer.lock', 'ext/awscrt.stub.php', 'acinclude.m4', 'aclocal.m4',
                   'autom4te.cache']

# Remove all .lo and .o files
files_to_remove += glob.glob(os.path.join(WORK_DIR, '**/*.lo'))
files_to_remove += glob.glob(os.path.join(WORK_DIR, '**/*.o'))

# Remove all .la and .a files
files_to_remove += glob.glob(os.path.join(WORK_DIR, '**/*.la'))
files_to_remove += glob.glob(os.path.join(WORK_DIR, '**/*.a'))
# Remove all .tgz files
files_to_remove += glob.glob(os.path.join(WORK_DIR, '*.tgz'))

remove_files(files_to_remove)
