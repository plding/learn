#!/usr/bin/env python3
import sys
import os

sumVal = 0
for part in sys.stdin.read(int(os.environ.get("CONTENT_LENGTH"))).split("&"):
    _, val = part.split("=")
    sumVal += int(val)

print("Content-Type: text/html\r\n");
print(sumVal)
