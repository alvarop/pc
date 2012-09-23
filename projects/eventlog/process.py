#!/usr/bin/env python
#
# process.py - take in csv log file and spit out something more useful
#
import argparse
from datetime import datetime

parser = argparse.ArgumentParser(description="Process log csv file.")
parser.add_argument("filename", help="CSV log file")

args = parser.parse_args()

with open(args.filename, 'r') as infile:
  lines = infile.readlines()

index = 0

while index < (len(lines)-1):
  line = lines[index].strip().split(',')
  nextline = lines[index+1].strip().split(',')
 
  if line[3]=='1' and nextline[3]=='0': 
    dt = datetime.fromtimestamp(int(line[0])).timetuple()
    count = int(nextline[0])-int(line[0])
    print "%04d/%02d/%02d" % (dt.tm_year, dt.tm_mon, dt.tm_mday),
    print "%02d:%02d:%02d,%d" % (dt.tm_hour,dt.tm_min,dt.tm_sec,count)

  index += 1
