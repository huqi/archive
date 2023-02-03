import datetime
import os
import shutil
import sys

def getDate():
    today = datetime.date.today()
    return today.strftime("%Y%m%d")

def getDir(filename):
    return os.path.dirname(filename)

def getFilename(filename): 
    return os.path.split(filename)[-1]

def newDir(path, date):
    return os.path.join(path, date)

def checkAndCreateDir(path):
    if not os.path.exists(path):
        os.makedirs(path)

def moveFile(path, file):
    src = file
    dest = os.path.join(path, getFilename(file))
    shutil.move(src, dest)
    
def main(argv):
    filename = argv[1]
    dirStr = getDir(filename)
    dateStr = getDate()
    newDirStr = newDir(dirStr, dateStr)
    checkAndCreateDir(newDirStr)
    moveFile(newDirStr, filename)
    
if __name__ == "__main__":
    main(sys.argv)