from os import walk
from os.path import join

def get_lines(path):
	file = open(path)
	lines = file.readlines()
	file.close()
	return lines

def count_sloc(lines):
	sloc = 0
	for line in lines:
		if len(line) > 3:
			sloc += 1
	return sloc

loc = 0
sloc = 0
	
for root, dirs, files in walk('.'):
	if 'r2tk' in root:
		continue
	if 'FreeImage' in root:
		continue
	for file in files:
		if '.py' in file:
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
		