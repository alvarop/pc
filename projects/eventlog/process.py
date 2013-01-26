#!/usr/bin/env python
#
# process.py - take in csv log file and spit out something more useful
#
import argparse
from datetime import datetime
import time

parser = argparse.ArgumentParser(description="Process log csv file.")
parser.add_argument("filename", help="CSV log file")

args = parser.parse_args()

with open(args.filename, 'r') as infile:
  lines = infile.readlines()

index = 0
current_minute = 0
count = 0
current_day = 0

# Get current timestamp
today = int(time.time())

# Get current day
today = today - today % 86400

# Get last night (Midnight minus 4 hours)
last_night = today - 14400

print "Today is ", today

while index < (len(lines)-1):
  line = lines[index].strip().split(',')
  nextline = lines[index+1].strip().split(',')

  # Don't print anything other than last night
  if int(line[0]) < last_night:
    index +=1
    continue

  day = int(line[0]) - int(line[0]) % 86400
  if day > current_day:
    current_day = day

  if line[3]=='1' and nextline[3]=='0': 
    for seconds in range(int(line[0]),int(nextline[0])-1):
      minute = seconds - seconds % 60;
      print seconds
#      if minute > current_minute:
#        current_minute = minute
#        dt = datetime.fromtimestamp(minute).timetuple()
#        print "%04d/%02d/%02d" % (dt.tm_year, dt.tm_mon, dt.tm_mday),
#        print "%02d:%02d:%02d,%d" % (dt.tm_hour,dt.tm_min,dt.tm_sec,count)
#        count = 0
      count += 1

  index += 1


