#!/usr/bin/env python
import os
import struct

urandom = open('/dev/urandom', 'r')
def getstring(size = None):
    if size == None:
        tmp = urandom.read(2)
        size = struct.unpack("H", tmp)
    return ''.join(chr(i >> 1) for i in urandom.read(tmp))

def getyear():
    tmp = urandom.read(4)
    ret = struct.unpack("i")
    if ret == 0:
        return getyear()
    else: return ret
