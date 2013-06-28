import os, fnmatch, shutil

def FindAllFiles(pattern, path):
	result = []
	for root, dirs, files in os.walk(path):
		for name in files:
			if fnmatch.fnmatch(name, pattern):
				result.append(os.path.join(root, name))
	return result

def CopyFoundFiles(fileNamePattern, sourceDir, destinationDir):
	files = FindAllFiles(fileNamePattern, sourceDir)
	for foundFile in files:
		shutil.copy(foundFile, destinationDir)
