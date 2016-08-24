#include <stdio.h>
#include <stdlib.h>
#include <algorithm>//#include <list>
#include <vector>
#include <iostream>
#include <string.h>
#include <boost/tokenizer.hpp>
#include <fstream>
#include <sstream>
#include <math.h>
using namespace std;
using namespace boost;
int main(int argc, char *argv[])
{
	struct timespec t1,t2,t3;
	clock_gettime(CLOCK_MONOTONIC,&t1);
	std::vector<long>  size_of;
	std::vector<long> dimension;
	std::vector<long> block_X;
	std::vector<long> block_Y;
	std::vector<long> array_size;
	std::vector<vector<long> > stride;
	long count = 0;
	string line;
	ifstream myfile (argv[9]);
	vector<vector<string>  > dataTable;
 
	if (myfile.is_open())
	{
		while (getline (myfile,line))
		{  count ++;
		   stringstream ss(line);
		   vector<string> row;
		   string entry;
 
		   while (ss >> entry)
			   row.push_back(entry);
		   dataTable.push_back(row);
		}
		myfile.close();
	}

	else cout << "Unable to open file";

	for(long i =0; i<count;i++)
	{
		if (dataTable[i][0]=="dimension")
			for(long j = 1; j<dataTable[i].size();j++)
			dimension.push_back(std::stol(dataTable[i][j]));
			//dimension.assign(dataTable[i].begin()+1,dataTable[i].end());
		else if (dataTable[i][0]=="sizeof")
			 for(long j = 1; j<dataTable[i].size();j++)
					size_of.push_back(std::stol(dataTable[i][j]));

		else if (dataTable[i][0]=="block_X")
			 for(long j = 1; j<dataTable[i].size();j++)
					block_X.push_back(std::stol(dataTable[i][j]));

		else if (dataTable[i][0]=="block_Y")
			 for(long j = 1; j<dataTable[i].size();j++)
					block_Y.push_back(std::stol(dataTable[i][j]));

		else if (dataTable[i][0]=="array_size")
			 for(long j = 1; j<dataTable[i].size();j++)
					array_size.push_back(std::stol(dataTable[i][j]));
		else
		{
			vector<long> temp;
			for (long j = 0; j<6;j++)
			{
				temp.push_back(std::stol(dataTable[i][j]));
			}
			stride.push_back(temp);
		}

	}
	std::sort(stride.begin(),stride.end());
	clock_gettime(CLOCK_MONOTONIC,&t2);
	cout<<t2.tv_sec-t1.tv_sec+(t2.tv_nsec-t1.tv_nsec)/1.e9<<endl;
	//for(long i =0;i<stride.size();i++)
	//cout<<stride[i][0]<<" "<<stride[i][1]<<" "<<stride[i][2]<<" "<<stride[i][3]<<" "<<stride[i][4]<<" "<<stride[i][5]<<" "<<endl;
	//cout<<size_of<<endl;
	long global_size = atol(argv[1]);
	long glo_lat = atol(argv[2]);
	long L2_size = atol(argv[3]);
	long L2_cache_line = atol(argv[4]);
	long L2_lat = atol(argv[5]);
	long L1_size = atol(argv[6]);
	long L1_cache_line = atol(argv[7]);
	long L1_lat = atol(argv[8]);
	long L1_lines; 
	long L2_lines;
	long x=0;
	string prlongout = "global ";
	long array = long(stride[x][0]);
	long array_next = array;
	long rw = long(stride[x][1]);
	long exp = long(stride[x][2]);
	long loop = long(stride[x][3]);
	long index = long(stride[x][5]);
	long warp = long(stride[x][4]);
	long prlong1 = 0;
	long cache_line = L1_cache_line;
	if(L1_size==0)
	{
		cache_line = L2_cache_line;
		if(L2_size==0)
			cache_line = 32;
	}
	L1_cache_line =cache_line;
	if(L2_cache_line<cache_line)
	L2_cache_line = cache_line;
	L1_lines= L1_size/L1_cache_line;
	L2_lines= L2_size/L2_cache_line;
	//array_total=[]
	long total = 0;
	long total_cache_line=0;
	std::vector<long> access;
	std::vector<long> access_cache_line;
	std::vector<long> collect_cache_line;
	std::vector<long> L1;
	std::vector<long> L2;
	long L1_hit = 0;
	long L2_hit = 0;
	long collect_find = -1;
	long L1_find = -1;
	long L2_find = -1;
	ofstream output;
	output.open("output_DP2.txt",std::ios_base::app);
	while(x<stride.size())
	{
		array_next = long(stride[x][0]);
		long rw_next = long(stride[x][1]);
		long exp_next = long(stride[x][2]);
		long loop_next = long(stride[x][3]);
		long warp_next = long(stride[x][4]);
		long index_next = long(stride[x][5]);
		x = x + 1;
		if(array == array_next&&rw==rw_next&&exp==exp_next)
		{	
			if(loop==loop_next && warp/32==warp_next/32)
			{
				index = index_next;
				collect_find = find(collect_cache_line.begin(),collect_cache_line.end(),index_next*size_of[array_next]/cache_line)-collect_cache_line.begin();
				L1_find = find(L1.begin(),L1.end(),index_next*size_of[array_next]/L1_cache_line)-L1.begin();
				if(rw_next ==0 && L1_find < L1.size() \
				&&collect_find>=collect_cache_line.size()  \
				)
				{
					L1_hit += 1;
					L1.erase(L1_find+L1.begin());
					L1.push_back(index_next*size_of[array_next]/L1_cache_line);
				}
				else if(rw_next==0&&L1_find<L1.size()&&collect_find<collect_cache_line.size())
				{continue;}
				else if(rw_next==0&&L1_find>=L1.size()&&collect_find<collect_cache_line.size())
				{continue;}
				else if(L1_find>=L1.size()&&collect_find>=collect_cache_line.size()){
					if (rw_next == 0&&L1_lines>0)
					 {
						if(L1.size()>=L1_lines)
							L1.erase(L1.begin());
						L1.push_back(index_next*size_of[array_next]/L1_cache_line);
					}
					L2_find = find(L2.begin(),L2.end(),index_next*size_of[array_next]/L2_cache_line)-L2.begin();
					if(L2_find<L2.size() \
					   && collect_find >= collect_cache_line.size() \
					  )
					{	
						L2_hit += 1;
						L2.erase(L2_find+L2.begin());
						L2.push_back(index_next*size_of[array_next]/L2_cache_line);
					}
					else if(L2_find<L2.size() \
						&& collect_find <collect_cache_line.size()
					)
					{continue;}
					else if(L2_find>=L2.size()&&collect_find<collect_cache_line.size())
					{continue;}
					else if(L2_find>=L2.size()&&collect_find>=collect_cache_line.size()&&L2_lines>0)
					{
						if(L2.size()>=L2_lines)
							L2.erase(L2.begin());
						L2.push_back(index_next*size_of[array_next]/L2_cache_line);
					}
				}
				
				if(collect_find >= collect_cache_line.size())
				collect_cache_line.push_back(index_next*size_of[array_next]/cache_line);
			}
			else{
				exp = exp_next;
				loop = loop_next;
				warp = warp_next;
				rw = rw_next;
				index = index_next;
				array=array_next;
				access_cache_line.push_back(1+(collect_cache_line.size()-1));
				collect_cache_line.clear();
				collect_find = find(collect_cache_line.begin(),collect_cache_line.end(),index_next*size_of[array_next]/cache_line)-collect_cache_line.begin();
							L1_find = find(L1.begin(),L1.end(),index_next*size_of[array_next]/L1_cache_line)-L1.begin();
							if(rw_next ==0 && L1_find < L1.size() \
							&&collect_find>=collect_cache_line.size()  \
							)
							{
									L1_hit += 1;
									L1.erase(L1_find+L1.begin());
									L1.push_back(index_next*size_of[array_next]/L1_cache_line);
							}
							else if(rw_next==0&&L1_find<L1.size()&&collect_find<collect_cache_line.size())
							{continue;}
							else if(rw_next==0&&L1_find>=L1.size()&&collect_find<collect_cache_line.size())
							{continue;}
							else if(L1_find>=L1.size()&&collect_find>=collect_cache_line.size()){
									if (rw_next == 0&&L1_lines>0)
									 {
											if(L1.size()>=L1_lines)
													L1.erase(L1.begin());
											L1.push_back(index_next*size_of[array_next]/L1_cache_line);
									}
									L2_find = find(L2.begin(),L2.end(),index_next*size_of[array_next]/L2_cache_line)-L2.begin();
									if(L2_find<L2.size() \
									   && collect_find >= collect_cache_line.size() \
									  )
									{
											L2_hit += 1;
											L2.erase(L2_find+L2.begin());
											L2.push_back(index_next*size_of[array_next]/L2_cache_line);
									}
									else if(L2_find<L2.size() \
											&& collect_find <collect_cache_line.size()
									)
									{continue;}
									else if(L2_find>=L2.size()&&collect_find<collect_cache_line.size())
									{continue;}
									else if(L2_find>=L2.size()&&collect_find>=collect_cache_line.size()&&L2_lines>0)
									{
											if(L2.size()>=L2_lines)
													L2.erase(L2.begin());
											L2.push_back(index_next*size_of[array_next]/L2_cache_line);
									}
							}
				collect_cache_line.push_back(index_next*size_of[array_next]/cache_line);


			}

		}
		else{
			access_cache_line.push_back(collect_cache_line.size());
			for(long yy=0;yy<access_cache_line.size();yy++)
			{
				total_cache_line += access_cache_line[yy];
			}
			//cout<<"array "<<array<<" expr "<<exp<<" has "<<L1_hit<<" L1 hits,"<<L2_hit<<" L2 hits "<<total_cache_line-L1_hit-L2_hit<<" global."<<endl;
			output <<"global "<<array<<" "<<exp<<" "<<L1_hit<<" "<<L2_hit<<" "<<total_cache_line-L1_hit-L2_hit<<"\n";
			array = array_next;
			exp = exp_next;
			loop = loop_next;
			warp = warp_next;
			rw = rw_next;
			index=index_next;
			total = 0;
			total_cache_line = 0;
			L1_hit = 0;
			L2_hit = 0;
			L1.clear();
			L2.clear();
			access_cache_line.clear();
			collect_cache_line.clear();
			collect_cache_line.push_back(index_next*size_of[array_next]/cache_line);
			if(L1_lines>0)
			L1.push_back(index_next*size_of[array_next]/L1_cache_line);
			if(L2_lines>0)
			L2.push_back(index_next*size_of[array_next]/L2_cache_line);
		}

	}
	access_cache_line.push_back(collect_cache_line.size());
	for(long yy=0;yy<access_cache_line.size();yy++)
	 {
		  total_cache_line += access_cache_line[yy];
	 }
	//cout<<"array "<<array_next<<" expr "<<exp<<" has "<<L1_hit<<" L1 hits, "<<L2_hit<<" L2 hits,"<<total_cache_line-L1_hit-L2_hit<<" global."<<endl;
	output <<"global "<<array<<" "<<exp<<" "<<L1_hit<<" "<<L2_hit<<" "<<total_cache_line-L1_hit-L2_hit<<"\n";
	array = array_next;

	clock_gettime(CLOCK_MONOTONIC,&t3);
	cout<<"time for global: "<<t3.tv_sec-t2.tv_sec+(t3.tv_nsec-t2.tv_nsec)/1.e9<<endl;
	  return 0;
	//sscanf(p+=n,"%s%n",&pp,&n);
	/*while(sscanf(p+=n,"%d%n",&x,&n)>0)
	{
	 prlongf("%d ",x);
	}

	while(p=fgets(buf,sizeof(buf),f))
	{
		
	}
	long line[6];
	fscanf(f,"%d %d %d %d %d %d",&line[0],&line[1],&line[2],&line[3],&line[4],&line[5] );

	prlongf("%d %d %d %d %d %d\n", line[0],line[1],line[2],line[3],line[4],line[5]);
	*/
	output.close();
	return 0;
}
