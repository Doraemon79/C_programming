import os
import sys
import shutil
import argparse
import timeit
import time
from distutils.util import strtobool

def user_yes_no_query(question):
    sys.stdout.write('%s [y/n]\n' % question)
    while True:
        try:
            return strtobool(raw_input().lower())
        except ValueError:
            sys.stdout.write('Please respond with \'y\' or \'n\'.\n')

def copyLargeFile(src, dest, buffer_size):

    if os.path.isdir(dest):
      print 'Sorry %s is a directory, use a file instead1' % dest
      sys.exit(3)

    t0 = time.clock()
    with open(src, 'rb') as fsrc:
        with open(dest, 'wb') as fdest:
            shutil.copyfileobj(fsrc, fdest, buffer_size)
    print time.clock() - t0

def copyDirectory(src, dst, symlinks=True, ignore=None):
    if not os.path.exists(dst):
        os.makedirs(dst)
    else:
        user_yes_no_query('Directory %s exists. Do you want to overwrite it?3' % dst )
        t0 = time.clock()
    for item in os.listdir(src):
        s = os.path.join(src, item)
        d = os.path.join(dst, item)
        if os.path.isdir(s):
            copytree(s, d, symlinks, ignore)
            #print time.clock() - t0
        else:
            if not os.path.exists(d) or os.stat(src).st_mtime - os.stat(dst).st_mtime > 1:
                shutil.copy2(s, d)
    print time.clock() - t0

def copy_file(source, dest):
    #print'Ignazio 5 source %s'  % source
    #print'Ignazio 5 dest %s'  % dest

    if not os.path.isfile(source):
        #print "Source file %s does not exist." % source
        #print'Ignazio 5'
        print "Source file %s does not  exist." % source
        sys.exit(3)
    if  os.path.isfile(dest):
     #print'Ignazio 7 %s' % dest
     if user_yes_no_query('File %s exists. Do you want to overwrite it?' % dest ):
        #t = timeit.Timer("print 'main statement'", "print 'setup'")
        t0 = time.clock()
        try:

            #print'Ignazio 8 %s' % dest
            shutil.copy(source, dest)
            #t.timeit()
            print time.clock() - t0
        except IOError, e:
            print "Could not copy file %s to destination %s" % (source, dest)
            print e
            sys.exit(3)
    else:
        shutil.copy(source, dest)
        #print'Ignazio 9 %s' % dest


parser = argparse.ArgumentParser(description='copy files and directories', epilog='./Test.py -i myfile.txt -o anotherfile.txt')
parser.add_argument('-i','--input',  nargs='?', help='Input file name', type=str)
#parser.add_argument('-i','--input',  nargs='?', help='Input file name', type=str)
parser.add_argument('-o','--output',nargs='?', help='output file name', type=str, default=None)
parser.add_argument('-d','--inputDir',nargs='?', help='directory file name', type=str)
parser.add_argument('-s','--size',nargs='?', help='buffer size', type=int)
args = parser.parse_args()
#F=read(args.filename)

if args.size is  None:
   args.size = 0
else:
    S=args.size

I=args.input
O=args.output
D=args.inputDir

#F=args.input
#print 'Size is %s' % args.size
#print 'I is %s' % args.input
#print 'O is %s' % args.output
#print 'D is %s' % args.inputDir
#user_yes_no_query('Do you want to continue?')
#if args.inputDir != '':
#    copyDirectory(D,O)
#el
#print'Ignazio 1'
if args.size != 0:
        #print'Ignazio 2'
        copyLargeFile(I,O,S)
elif args.inputDir is not None:
        #print'Ignazio 3'
        copyDirectory(D,O)
else:
    if args.output is None:
        path=os.path.split(I)[1]
        O=os.getcwd() +'/'+ path
        print'Ignazio 6 %s' % O
    #print'Ignazio 4'
    copy_file(I,O)
