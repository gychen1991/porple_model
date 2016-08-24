@By [Guoyang Chen][1] (gychen1991@gmail.com)


## This is the model for estimation of data placements.


There are two versions of the tool: python and c++;

In both versions, we have:

__configure.py__: script to run all estimations;

__configure.txt__: records memory hierarchy of GPU hardware

__test_traces__: array access traces collected from running GPU kernels.

# C++ version: 
	support surface memory and more accurate model,
	More details in paper:
	1. [PORPLE-new model][2]
	2. [Coherence Free Multiview][3]
	

# Python version: 
	support more flexible memory hierarchy of GPU hardwares;
	More details see paper:
	1. [PORPLE-Micro][4]
	

#To compile:

	cd c++
	make

# To run:

	cd c++ or python
	configure.py configure.txt ../test_traces/mm_stride.txt

[1]:http://research.csc.ncsu.edu/nc-caps/gchen11/index.html
[2]:http://ieeexplore.ieee.org/xpl/login.jsp?tp=&arnumber=7106396&url=http%3A%2F%2Fieeexplore.ieee.org%2Fxpls%2Fabs_all.jsp%3Farnumber%3D7106396
[3]: http://research.csc.ncsu.edu/nc-caps/gchen11/ics16.pdf
[4]: http://research.csc.ncsu.edu/nc-caps/gchen11/micro14.pdf





