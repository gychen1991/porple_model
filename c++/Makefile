CC=g++ -O3 -std=c++11

all: global_check texture1D_32 texture2D_32 sur2D_struct constant_struct split split_fermi split_bb
global_check: global_check.cpp
	$(CC) -o $@ $^
texture1D_32: texture1D_32.cpp
	$(CC) -o $@ $^
texture2D_32: texture2D_32.cpp
	$(CC) -o $@ $^
sur2D_struct: sur2D_struct.cpp
	$(CC) -o $@ $^
constant_struct: constant_struct.cpp
	$(CC) -o $@ $^
split: split.cpp
	$(CC) -o $@ $^
split_fermi: split_fermi.cpp
	$(CC) -o $@ $^
split_bb: split_bb.cpp
	$(CC) -o $@ $^
clean:
	find . -perm +100 -type f -delete
