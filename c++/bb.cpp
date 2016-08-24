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
int global_min = 99999999;
std::vector<int> array_size;
std::vector<vector<vector<int> > > p;
std::vector<int> p_shared;
std::vector<int> shared_size;
std::vector<int> con_lat;
std::vector<int> glob_lat;
std::vector<int> read_lat;
std::vector<int> tex_lat;
std::vector<int> s;
std::vector<vector<int> > temp1;
std::vector<int> contension{0,0,0,0,0,0};


int cluster[5]={0,1,1,1,1};
int L1[5]={0,2,4,5,5};
int L2[5] ={1,3,3,3,3};
int sh_lat;
int cal_lat(int k, int j, vector<int> &conten)
{
	
	int latency = 0;
	if (j==0){
		if (p[k][j][0]==99999999)
			return 9999999;
		else{
			latency = p[k][j][1]/conten[0]*con_lat[2]+p[k][j][2]/conten[1]*con_lat[1]+(p[k][j][0]-p[k][j][1]/conten[0]-p[k][j][2]/conten[1])*con_lat[0];
			if(k!=0)
				latency *=5;
   			
		}
	}
	else if (j==1){	
		if (p[k][j][0]==99999999)
			return 9999999;
		else{
			latency =  p[k][j][1]/conten[2]*glob_lat[2]+p[k][j][2]/conten[3]*glob_lat[1]+(p[k][j][0]-p[k][j][1]/conten[2]-p[k][j][2]/conten[3])*glob_lat[0];
	
   			
		}
	}
	else if (j==2){
		if (p[k][j][0]==99999999)
			return 9999999;
		else{
			latency =  p[k][j][1]/conten[4]*read_lat[2]+p[k][j][2]/conten[3]*read_lat[1]+(p[k][j][0]-p[k][j][1]/conten[4]-p[k][j][2]/conten[3])*read_lat[0];
			
   			
		}
	}
	else if (j==3 or j==4){
		if (p[k][j][0]==99999999)
			return 9999999;
		else{
			latency =  p[k][j][1]/conten[5]*tex_lat[2]+p[k][j][2]/conten[3]*tex_lat[1]+(p[k][j][0]-p[k][j][1]/conten[5]-p[k][j][2]/conten[3])*tex_lat[0];
			
   			
		}
	}

return latency;	
	
}

int first_j(int k,int j,vector<int> &c2,int share,int total_tem, vector<int> &conten2,vector<int> &state2,vector<int> &l_s)
{

	
vector<int> state3;
state3.assign(state2.begin(),state2.end());
vector<int> c;
c.assign(c2.begin(),c2.end());
vector<int> conten;
conten.assign(conten2.begin(),conten2.end());
if(j<5){
	if (c[cluster[j]]<array_size[k])
		return (99999999);
	int mini=10000000;
	vector<int> l2;
	conten[L1[j]]+=1;
	conten[L2[j]]+=1;
	state3[k]=j;
	int total = 0;
	
	
	for(int  i =0 ;i<=k;i++)
		{
		total += cal_lat(i,state3[i],conten);}
	
	c[cluster[j]]=c[cluster[j]]-array_size[k];
	if(total>global_min)
		return 99999999;
	if (k==(array_size.size()-1))
		{
		l_s.push_back(j);
		return total;
		}
	for(int  i=0;i<5;i++)
		{vector<int> c1;
		 vector<int> conten1;
		 vector<int> state1;
		 c1.assign(c.begin(),c.end());
		 conten1.assign(conten.begin(),conten.end());
		state1.assign(state3.begin(),state3.end());
		vector<int> ls;
		int last_min=first_j(k+1,i,c1,share,total,conten1,state1,ls);
		if(mini>last_min)
			{
				mini=last_min;
				l2.assign(ls.begin(),ls.end());
			}
		}
		l2.insert(l2.begin(),j);
		l_s.assign(l2.begin(),l2.end());
	return mini;
}
	
}


int main(int argc, char *argv[])
{
struct timespec t1,t2,t3;
clock_gettime(CLOCK_MONOTONIC,&t1);
std::vector<int>  size_of;
std::vector<int> dimension;
std::vector<int> block_X;
std::vector<int> block_Y;

std::vector<vector<int> > stride;

int count = 0;

 string line;
    ifstream myfile(argv[1]);
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

    

for(int  i =0; i<count;i++)
{
	if (dataTable[i][0]=="dimension")
		for(int  j = 1; j<dataTable[i].size();j++)
		dimension.push_back(std::stol(dataTable[i][j]));
		//dimension.assign(dataTable[i].begin()+1,dataTable[i].end());
	else if (dataTable[i][0]=="sizeof")
		 for(int  j = 1; j<dataTable[i].size();j++)
                size_of.push_back(std::stol(dataTable[i][j]));

	else if (dataTable[i][0]=="block_X")
		 for(int  j = 1; j<dataTable[i].size();j++)
                block_X.push_back(std::stol(dataTable[i][j]));

	else if (dataTable[i][0]=="block_Y")
		 for(int  j = 1; j<dataTable[i].size();j++)
                block_Y.push_back(std::stol(dataTable[i][j]));

	else if (dataTable[i][0]=="array_size")
		 for(int  j = 1; j<dataTable[i].size();j++)
                array_size.push_back(std::stol(dataTable[i][j]));
	else
	{
		vector<int> temp;
		for (int j = 0; j<6;j++)
		{
			temp.push_back(std::stol(dataTable[i][j]));
		}
		stride.push_back(temp);
	}

}
count=0;
ifstream myfile1("configure.txt");
dataTable.clear();
//vector<vector<string>  > dataTable;
 
    if (myfile1.is_open())
    {
        while (getline (myfile1,line))
        {  count ++;
           stringstream ss(line);
           vector<string> row;
           string entry;
 
           while (ss >> entry)
			   row.push_back(entry);
           dataTable.push_back(row);
        }
        myfile1.close();
    }

    else cout << "Unable to open file";
int global_size = 0;

for(int  i=0;i<count;i++)
{
	if (dataTable[i][0]=="constant")
		{
		s.push_back(std::stol(dataTable[i][1]));
		con_lat.push_back(std::stol(dataTable[i][2]));
		con_lat.push_back(std::stol(dataTable[i][5]));
		con_lat.push_back(std::stol(dataTable[i][8]));
		}
		//dimension.assign(dataTable[i].begin()+1,dataTable[i].end());
	else if (dataTable[i][0]=="global")
		 {
		//cout<<dataTable[i][1]<<endl;
		global_size =std::stol(dataTable[i][1]);
		s.push_back(global_size);
		//cout<<global_size<<endl;cout<<"7"<<endl;
		glob_lat.push_back(std::stol(dataTable[i][2]));
                glob_lat.push_back(std::stol(dataTable[i][5]));
		glob_lat.push_back(std::stol(dataTable[i][8]));
		
		}

	else if (dataTable[i][0]=="texture")
		{
                tex_lat.push_back(std::stol(dataTable[i][4]));
		tex_lat.push_back(std::stol(dataTable[i][7]));
		tex_lat.push_back(std::stol(dataTable[i][10]));
		}

	else if (dataTable[i][0]=="readonly")
		{
		s.push_back(std::stol(dataTable[i][1]));
                read_lat.push_back(std::stol(dataTable[i][2]));
		read_lat.push_back(std::stol(dataTable[i][5]));
		read_lat.push_back(std::stol(dataTable[i][8]));
		}

	else if (dataTable[i][0]=="shared")
		 sh_lat=std::stol(dataTable[i][3]);
	else continue;
}

dataTable.clear();
ifstream myfile2("output.txt");
count=0;
    //vector<vector<string>  > dataTable;

 
    if (myfile2.is_open())
    {
        while (getline (myfile2,line))
        {  count ++;
           stringstream ss(line);
           vector<string> row;
           string entry;
 
           while (ss >> entry)
			   row.push_back(entry);
           dataTable.push_back(row);
        }
        myfile2.close();
    }

    else cout << "Unable to open file";


std::vector<int> temp;

//p = new vector<int> **[array_size.size()];
for(int  i=0;i<count;i++)
{	
	
	if (dataTable[i][0]=="constant")
		for(int  j =0;j<dataTable[i].size()/3;j++)
			{temp.clear();temp1.clear();
			temp.push_back(std::stol(dataTable[i][3*j+1]));
			temp.push_back(std::stol(dataTable[i][3*j+2]));
			temp.push_back(std::stol(dataTable[i][3*j+3]));
			
			temp1.push_back(temp);
			p.push_back(temp1);
			
			}
		//dimension.assign(dataTable[i].begin()+1,dataTable[i].end());
	else if (dataTable[i][0]=="global")
		 for(int  j =0;j<dataTable[i].size()/3;j++)
			{temp.clear();temp.push_back(std::stol(dataTable[i][3*j+1]));
			temp.push_back(std::stol(dataTable[i][3*j+2]));
			temp.push_back(std::stol(dataTable[i][3*j+3]));
			p[j].push_back(temp);
			}


	else if (dataTable[i][0]=="readonly")
		for(int  j =0;j<dataTable[i].size()/3;j++)
			{temp.clear();temp.push_back(std::stol(dataTable[i][3*j+1]));
			temp.push_back(std::stol(dataTable[i][3*j+2]));
			temp.push_back(std::stol(dataTable[i][3*j+3]));
			
			p[j].push_back(temp);
			}
	else if (dataTable[i][0]=="texture1D")
		for(int  j =0;j<dataTable[i].size()/3;j++)
			{temp.clear();temp.push_back(std::stol(dataTable[i][3*j+1]));
			temp.push_back(std::stol(dataTable[i][3*j+2]));
			temp.push_back(std::stol(dataTable[i][3*j+3]));
			
			p[j].push_back(temp);
			}
	else if (dataTable[i][0]=="texture2D")
		for(int  j =0;j<dataTable[i].size()/3;j++)
			{temp.clear();temp.push_back(std::stol(dataTable[i][3*j+1]));
			temp.push_back(std::stol(dataTable[i][3*j+2]));
			temp.push_back(std::stol(dataTable[i][3*j+3]));
			
			p[j].push_back(temp);
			}
	else if (dataTable[i][0]=="Shared")
		 for(int  j =1;j<dataTable[i].size();j++)
			{shared_size.push_back(std::stol(dataTable[i][j]));
			}
	else if (dataTable[i][0]=="shared")
		 for(int  j =1;j<dataTable[i].size();j++)
			{p_shared.push_back(std::stol(dataTable[i][j]));
			}
	else continue;
}
/*for(int i=0;i<p.size();i++)
 {for(int j=0;j<p[i].size();j++)
  {for(int z=0;z<p[i][j].size();z++)
   cout<<p[i][j][z]<<" ";
   cout<<",";
  }
cout<<endl;
}*/
std::sort(stride.begin(),stride.end());
clock_gettime(CLOCK_MONOTONIC,&t2);
cout<<t2.tv_sec-t1.tv_sec+(t2.tv_nsec-t1.tv_nsec)/1.e9<<endl;
//cout<<p[0][1][0]<<endl;
int min=99999999;
vector<int> ll;
int shared_total = 6*1024;
vector<int> ls;
vector<int> s1;
vector<int> contension1;
vector<int> state;
for(int j=0;j<4;j++)
{
s1.assign(s.begin(),s.end());
ls.assign(array_size.size(),-1);
contension1.assign(contension.begin(),contension.end());
state.assign(array_size.size(),-1);
vector<int> state1;
state1.assign(state.begin(),state.end());

int lastmin=first_j(0,j,s1,shared_total,0,contension1,state1,ls);
if(min>lastmin)
	{min=lastmin;
	ll.assign( ls.begin(),ls.end());
}
}
for(int x=0;x<ll.size();x++)
cout<<ll[x]<<",";
cout<<min<<endl;
//for(int  i =0;i<stride.size();i++)
//cout<<stride[i][0]<<" "<<stride[i][1]<<" "<<stride[i][2]<<" "<<stride[i][3]<<" "<<stride[i][4]<<" "<<stride[i][5]<<" "<<endl;
//cout<<size_of<<endl;
/*int global_size = atoi(argv[1]);
int glo_lat = atoi(argv[2]);
int L2_size = atoi(argv[3]);
int L2_cache_line = atoi(argv[4]);
int L2_lat = atoi(argv[5]);
int L1_size = atoi(argv[6]);
int L1_cache_line = atoi(argv[7]);
int L1_lat = atoi(argv[8]);
if(L2_cache_line < L1_cache_line)
	L2_cache_line = L1_cache_line;
if(L2_size == 0)
 L2_cache_line = size_of[0];
if(L1_size == 0){
 L1_cache_line = size_of[0];
 L1_cache_line = L2_cache_line;
}

if(L2_cache_line < L1_cache_line)
 L2_cache_line = L1_cache_line;
int L1_lines = L1_size/L1_cache_line;
int L2_lines = L2_size/L2_cache_line;
int x=0;
string printout = "global ";
int array = int(stride[x][0]);
int array_next = array;
int rw = int(stride[x][1]);
int exp = int(stride[x][2]);
int loop = int(stride[x][3]);
int index = int(stride[x][5]);
int warp = int(stride[x][4]);
int print1 = 0;
int cache_line = L1_cache_line;
//array_total=[]
int total = 0;
int total_cache_line=0;
std::vector<int> access;
std::vector<int> access_cache_line;
std::vector<int> collect_cache_line;
std::vector<int> L1;
std::vector<int> L2;
int L1_hit = 0;
int L2_hit = 0;
int collect_find = -1;
int L1_find = -1;
int L2_find = -1;
while(x<stride.size())
{
	array_next = int(stride[x][0]);
	int rw_next = int(stride[x][1]);
 	int exp_next = int(stride[x][2]);
 	int loop_next = int(stride[x][3]);
 	int warp_next = int(stride[x][4]);
 	int index_next = int(stride[x][5]);
	x = x + 1;
	if(array == array_next)
	{	
		if(rw==rw_next && exp==exp_next && loop==loop_next && warp/32==warp_next/32)
		{
			index = index_next;
			collect_find = find(collect_cache_line.begin(),collect_cache_line.end(),index_next*size_of[array_next]/cache_line)-collect_cache_line.begin();
			L1_find = find(L1.begin(),L1.end(),index_next*size_of[array_next]/L1_cache_line)-L1.begin();
			if(rw_next ==0 && L1_find < L1.size() \
			&&collect_find>=collect_cache_line.size()  \
			&&abs(L1.size()-L1_find)<=L1_lines)
			{
				L1_hit += 1;
				L1.erase(L1_find+L1.begin());
				L1.push_back(index_next*size_of[array_next]/L1_cache_line);
			}
			else{
				if (rw_next == 0)
				 {
					if(L1_find<L1.size())
						L1.erase(L1_find+L1.begin());
					L1.push_back(index_next*size_of[array_next]/L1_cache_line);
				}
				L2_find = find(L2.begin(),L2.end(),index_next*size_of[array_next]/L2_cache_line)-L2.begin();
				if(L2_find<L2.size() \
				   && collect_find >= collect_cache_line.size() \
				  && abs(L2.size()-L2_find)<=L2_lines)
				{	
					L2_hit += 1;
					L2.erase(L2_find+L2.begin());
					L2.push_back(index_next*size_of[array_next]/L2_cache_line);
				}
				else{
					if(L2_find<L2.size())
						L2.erase(L2_find+L2.begin());
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
			access_cache_line.push_back(collect_cache_line.size());
			collect_cache_line.clear();
			collect_find = find(collect_cache_line.begin(),collect_cache_line.end(),index_next*size_of[array_next]/cache_line)-collect_cache_line.begin();
                        L1_find = find(L1.begin(),L1.end(),index_next*size_of[array_next]/L1_cache_line)-L1.begin();
                        if(rw_next ==0 && L1_find < L1.size() \
                        &&collect_find>=collect_cache_line.size()  \
                        &&abs(L1.size()-L1_find)<=L1_lines)
                        {
                                L1_hit += 1;
                                L1.erase(L1_find+L1.begin());
                                L1.push_back(index_next*size_of[array_next]/L1_cache_line);
                        }
                        else{
                                if (rw_next == 0)
                                 {
                                        if(L1_find<L1.size())
                                                L1.erase(L1_find+L1.begin());
                                        L1.push_back(index_next*size_of[array_next]/L1_cache_line);
                                }
                                L2_find = find(L2.begin(),L2.end(),index_next*size_of[array_next]/L2_cache_line)-L2.begin();
                                if(L2_find<L2.size() \
                                   && collect_find >= collect_cache_line.size() \
                                  && abs(L2.size()-L2_find)<=L2_lines)
                                { 
                                        L2_hit += 1;
                                        L2.erase(L2_find+L2.begin());
                                        L2.push_back(index_next*size_of[array_next]/L2_cache_line);
                                }
                                else{
                                        if(L2_find<L2.size())
                                                L2.erase(L2_find+L2.begin());
                                        L2.push_back(index_next*size_of[array_next]/L2_cache_line);
                                }
                        }

                        collect_cache_line.push_back(index_next*size_of[array_next]/cache_line);


		}

	}
	else{
		access_cache_line.push_back(collect_cache_line.size());
		for(int  yy=0;yy<access_cache_line.size();yy++)
		{
			total_cache_line += access_cache_line[yy];
		}
		cout<<"array "<<array<<" has "<<total_cache_line<<" transactions,"<<L1_hit<<" L1 hits,"<<L2_hit<<" L2 hits"<<endl;
		array = array_next;
		exp = exp_next;
		loop = loop_next;
		warp = warp_next;
		rw = rw_next;
		total = 0;
		total_cache_line = 0;
		L1_hit = 0;
		L2_hit = 0;
		L1.clear();
		L2.clear();
		access_cache_line.clear();
		collect_cache_line.clear();
		collect_cache_line.push_back(index_next*size_of[array_next]/cache_line);
		L1.push_back(index_next*size_of[array_next]/L1_cache_line);
		L2.push_back(index_next*size_of[array_next]/L2_cache_line);
	}

}
access_cache_line.push_back(collect_cache_line.size());
for(int  yy=0;yy<access_cache_line.size();yy++)
 {
      total_cache_line += access_cache_line[yy];
 }
cout<<"array "<<array_next<<" has "<<total_cache_line<<" transactions,"<<L1_hit<<" L1 hits,"<<L2_hit<<" L2 hits"<<endl;
array = array_next;
//exp = exp_next;
loop = loop_next;
warp = warp_next;
rw = rw_next;
total = 0;
total_cache_line = 0;
 L1.clear();
L2.clear();
access_cache_line.clear();
collect_cache_line.clear();
 collect_cache_line.push_back(index_next*size_of[array_next]/cache_line);
L1.push_back(index_next*size_of[array_next]/L1_cache_line);
L2.push_back(index_next*size_of[array_next]/L2_cache_line);

*/
clock_gettime(CLOCK_MONOTONIC,&t3);
cout<<"time for global: "<<t3.tv_sec-t2.tv_sec+(t3.tv_nsec-t2.tv_nsec)/1.e9<<endl;
  return 0;
//sscanf(p+=n,"%s%n",&pp,&n);
/*while(sscanf(p+=n,"%d%n",&x,&n)>0)
{
 printf("%d ",x);
}

while(p=fgets(buf,sizeof(buf),f))
{
	
}
int line[6];
fscanf(f,"%d %d %d %d %d %d",&line[0],&line[1],&line[2],&line[3],&line[4],&line[5] );

printf("%d %d %d %d %d %d\n", line[0],line[1],line[2],line[3],line[4],line[5]);
*/
//return 0;
}
