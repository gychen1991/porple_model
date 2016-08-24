#!/usr/bin/python

"""
usage: ./configure.py *.txt configure.txt stride.txt
"""

import sys
import os
import string

f = open(str(sys.argv[1]),'r')
stride_file = str(sys.argv[2])
late = open("latency.txt",'a')
Mem = {}
for line in f:
	s = line.strip()
	s = s.split()
	if s[0].upper() == "CONSTANT":
		constant_size = s[1]
		con_lat = s[2]
		L2_size = s[3]
		L2_cache_line = s[4]
		L2_lat = s[5]
		L1_size = s[6]
		L1_cache_line = s[7]
		L1_lat = s[8]
		exe_command = "./constant_noprintout.py " +constant_size+" "+con_lat+" "+L2_size+" "+L2_cache_line+" "+L2_lat+" "+L1_size+" "+L1_cache_line+" "+L1_lat+" "+stride_file
		os.system(exe_command)
		late.write("constant "+con_lat+" "+L2_lat+" "+L1_lat+"\n")
	elif s[0].upper() == "GLOBAL":
		global_size = s[1]
                glo_lat = s[2]
                L2_size = s[3]
                L2_cache_line = s[4]
                L2_lat = s[5]
                L1_size = s[6]
                L1_cache_line = s[7]
                L1_lat = s[8]
		exe_command = "./global_noprint.py "+global_size+" "+ glo_lat+" "+L2_size+" "+L2_cache_line+" "+L2_lat+" "+L1_size+" "+L1_cache_line+" "+L1_lat+" "+ \
stride_file
		os.system(exe_command)
		late.write("global "+glo_lat+" "+L2_lat+" "+L1_lat+"\n")
        elif s[0].upper() == "READONLY":
                global_size = s[1]
                glo_lat = s[2]
                L2_size = s[3]
                L2_cache_line = s[4]
                L2_lat = s[5]
                L1_size = s[6]
                L1_cache_line = s[7]
                L1_lat = s[8]
                exe_command = "./readonly_noprint.py "+global_size+" "+ glo_lat+" "+L2_size+" "+L2_cache_line+" "+L2_lat+" "+L1_size+" "+L1_cache_line+" "+L1_lat+" "+ \
stride_file
                os.system(exe_command)
                late.write("readonly "+glo_lat+" "+L2_lat+" "+L1_lat+"\n")
	elif s[0] == "texture":
		size_1Dfetch = s[1]
		size_1D = s[2]
		size_2D = s[3]
		tex_lat = s[4]
		L2_size = s[5]
		L2_cache_line = s[6]
		L2_lat = s[7]
		L1_size = s[8]
		L1_cache_line = s[9]
		L1_lat = s[10]
		exe_command = "./texture_noprintout.py "+size_1Dfetch+" "+size_1D+" "+size_2D+" "+tex_lat+" "+L2_size+" "+L2_cache_line+" "+L2_lat+" "+L1_size+" "+L1_cache_line+" "+L1_lat+" "+stride_file
		os.system(exe_command)
		late.write("texture "+tex_lat+" "+L2_lat+" "+L1_lat+"\n")
	elif s[0].upper() == "SHARED":
		shared_size = s[1]
		banks = s[2]
		sh_lat = s[3]
		exe_command = "./shared_noprintout.py "+shared_size+" "+banks+" "+sh_lat+" "+stride_file
		os.system(exe_command)
		late.write("shared "+sh_lat+"\n")
			
			
late.close()
os.system("./bb_noshared_div.py "+str(stride_file))
