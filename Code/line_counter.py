#	File: line_counter.py
#	Authors: Thomas Sievert, Lars Woxberg
#	Date created: 2012-04-27

from os import walk
from os.path import join

class IgnoreException(Exception):
	"""Raised when .ignore file is mis-formatted."""
	def __init__(self, value):
		self.value = value
		
	def __str__(self):
		return repr(self.value)

def get_ignore():
	lines = getlines('line_counter.ignore')
	files = []
	dirs = []
	for line in lines:
		if line.startswith('#'):
			continue
		if line.endswith('\n'):
			line = line[:-1]
		if line.startswith('dir '):
			dirs.append(line[4:])
		elif line.startswith('file '):
			files.append(line[5:])
		else:
			raise IgnoreException("Invalid .ignore file: %s") % line
	return files, dirs
			
def get_lines(path):
	file = open(path)
	lines = file.readlines()
	file.close()
	return lines

def count_sloc(lines):
	sloc = 0
	for line in lines:
		line = line.strip()
		if len(line) > 3:
			sloc += 1
	return sloc

def valid_root(ignore_dirs, name):
	valid = True
	for dir in ignore_dirs:
		if name.endswith(dir):
			valid = False
			break
	return valid
	
def valid_file(ignore_files, name):
	valid = True
	for file in ignore_files:
		if name.endswith(file):
			valid = False
			break
	return valid
	
loc = 0
sloc = 0

ignore_files, ignore_roots = get_ignore()

for root, dirs, files in walk('.'):
	if not valid_root(ignore_roots, root):
		continue
	for file in files:
		if not valid_file(ignore_files, file):
			continue
		path = join(root, file)
		lines = get_lines(path)
		file_loc = len(lines)
		file_sloc = count_sloc(lines)
		print "%s has %d loc and %d sloc" % (path, file_loc, file_sloc)
		loc += file_loc
		sloc += file_sloc
		
print "Total lines of code: %d" % loc
print "Total source lines of code: %d" % sloc