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
		print("======================Constant==================")
		exe_command = "./constant_struct " +constant_size+" "+con_lat+" "+L2_size+" "+L2_cache_line+" "+L2_lat+" "+L1_size+" "+L1_cache_line+" "+L1_lat+" "+stride_file
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
		print("======================Global==================")
		exe_command = "./global_check "+global_size+" "+ glo_lat+" "+L2_size+" "+L2_cache_line+" "+L2_lat+" "+L1_size+" "+L1_cache_line+" "+L1_lat+" "+ \
stride_file
		os.system(exe_command)
		late.write("global "+glo_lat+" "+L2_lat+" "+L1_lat+"\n")
	
#        elif s[0].upper() == "READONLY":
#                global_size = s[1]
#                glo_lat = s[2]
#                L2_size = s[3]
#                L2_cache_line = s[4]
#                L2_lat = s[5]
#                L1_size = s[6]
#                L1_cache_line = s[7]
#                L1_lat = s[8]
#                exe_command = "./../scripts/texture1D_32 "+global_size+" "+ glo_lat+" "+L2_size+" "+L2_cache_line+" "+L2_lat+" "+L1_size+" "+L1_cache_line+" "+L1_lat+" "+ \
#stride_file
#                os.system(exe_command)
#                late.write("readonly "+glo_lat+" "+L2_lat+" "+L1_lat+"\n")
	elif s[0] == "texture1D":
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
		print("======================Texture 1D==================")
		exe_command = "./texture1D_32 "+size_1Dfetch+" "+tex_lat+" "+L2_size+" "+L2_cache_line+" "+L2_lat+" "+L1_size+" "+L1_cache_line+" "+L1_lat+" "+stride_file
		os.system(exe_command)
		late.write("texture1D "+tex_lat+" "+L2_lat+" "+L1_lat+"\n")
	elif s[0] == "texture2D":
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
		print("======================Texture 2D==================")
                exe_command = "./texture2D_32 "+size_1Dfetch+" "+tex_lat+" "+L2_size+" "+L2_cache_line+" "+L2_lat+" "+L1_size+" "+L1_cache_line+" "+L1_lat+" "+stride_file
                os.system(exe_command)
                late.write("texture2D "+tex_lat+" "+L2_lat+" "+L1_lat+"\n")
	elif s[0].upper() == "SURFACE":
                global_size = s[1]
                glo_lat = s[2]
                L2_size = s[3]
                L2_cache_line = s[4]
                L2_lat = s[5]
                L1_size = s[6]
                L1_cache_line = s[7]
                L1_lat = s[8]
		print("======================Surface 2D==================")
                exe_command = "./sur2D_struct "+global_size+" "+ glo_lat+" "+L2_size+" "+L2_cache_line+" "+L2_lat+" "+L1_size+" "+L1_cache_line+" "+L1_lat+" "+ \
stride_file
                os.system(exe_command)
                late.write("surface "+glo_lat+" "+L2_lat+" "+L1_lat+"\n")
#	elif s[0].upper() == "SHARED":
#		shared_size = s[1]
#		banks = s[2]
#		sh_lat = s[3]
#		exe_command = "./../scripts/shared_noprintout.py "+shared_size+" "+banks+" "+sh_lat+" "+stride_file
#		os.system(exe_command)
#		late.write("shared "+sh_lat+"\n")
			
			
late.close()
os.system("./split "+str(stride_file))
