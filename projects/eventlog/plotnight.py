#!/usr/bin/env python
#
# process.py - take in csv log file and spit out something more useful
#
import argparse
from datetime import datetime
import time
import matplotlib.pyplot as plt
import pylab


parser = argparse.ArgumentParser(description="Process log csv file.")
parser.add_argument("filename", help="CSV log file")

args = parser.parse_args()

# how many items shall we keep track of?
n = 30

with open(args.filename, 'r') as infile:
  lines = infile.readlines()

index = 0

# Create list with every second of the night and set to 0 or 1
y = [0] * (int(lines[len(lines)-1]) - int(lines[0]))
z = [0] * (int(lines[len(lines)-1]) - int(lines[0]))
while index < (len(lines)-1):
  time = int(lines[index])-int(lines[0])
  y[time] = 1
  index += 1

for index in range(len(y)):
    if index < n:
        low = 0
    else:
        low = index - n

    if (index + n) > (len(y)):
        high = len(y)
    else:
        high = index + n

    for subindex in range(low,high):
        z[index] += y[subindex]

plt.plot(z)


pylab.show()
