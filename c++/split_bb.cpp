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
long long global_min = 99999999;
std::vector<long long> array_size;
std::vector<vector<vector<long long> > > p;
std::vector<long long> p_shared;
std::vector<long long> shared_size;
std::vector<long long> con_lat;
std::vector<long long> glob_lat;
std::vector<long long> read_lat;
std::vector<long long> tex_lat;
std::vector<long long> tex2D_lat;
std::vector<long long> surf_lat;
std::vector<long long> s;
std::vector<vector<long long> > temp1;
std::vector<long long> contension{1,1,1,1,1,};
std::vector<long long> instr;
std::vector<vector<long long> > constant;
std::vector<vector<long long> > global;
std::vector<vector<long long> > texture1D;
std::vector<vector<long long> > texture2D;
std::vector<vector<long long> > surface;
vector<long long> instr_after;
vector<long long> instr_to_array;
struct Band{
long long GL;
long long TX;
};
long long max(long long x,long long y)
{
if(x>y) return x;
else return y;
}
long long total_instr;
struct Band* bb(long long i, long long j, long long band1_1,long long band2_1,vector<long long> D2D1_1,vector<long long> &l_s){
	vector<long long> l2;
	vector<long long> D2D1_2;
	struct Band* min=(struct Band *)malloc(sizeof(struct Band));
	if((i+1)>D2D1_1.size())
		{
		long long minimal=999999999;
		int toolarge=0;
		for(long long D=0;D<2;D++){
			vector<long long> D2D1;
			long long band1=band1_1;
			long long band2=band2_1;
			D2D1.assign(D2D1_1.begin(),D2D1_1.end());
			for(long long x=0;x<instr_after[instr_to_array[i]];x++)
				D2D1.push_back(D);
			if(j==0&&D2D1[i]==0)
				band1+=global[i][0]*glob_lat[2]+global[i][1]*glob_lat[1]+global[i][2]*glob_lat[0];
			else if(j==1&&D2D1[i]==0)
				band2+=texture1D[i][0]*tex_lat[2]+texture1D[i][1]*tex_lat[1]+texture1D[i][2]*tex_lat[0];
			else if(j==0&&D2D1[i]==1)
				band2+=texture2D[i][0]*tex2D_lat[2]+texture2D[i][1]*tex2D_lat[1]+texture2D[i][2]*tex2D_lat[0];
			else if(j==1&&D2D1[i]==1)
				band1+=surface[i][0]*surf_lat[2]+surface[i][1]*surf_lat[1]+surface[i][2]*surf_lat[0];
#ifdef BB
			if(max(band1,band2)>global_min)
        		{
                	min->GL=99999999;
                	min->TX=99999999;
			toolarge+=1;
                	continue;
        		}
#endif
			if((i+1)==total_instr) 
				{//min->GL=band1;min->TX=band2;
				//	l_s.push_back(j+D2D1[i]*2);
				//	return min;
				if (minimal>max(band1,band2)||(minimal==max(band1,band2)&&(min->GL+min->TX)>(band1+band2)))
				{
				minimal=max(band1,band2);
				min->GL=band1;min->TX=band2;
#ifdef BB
				if(global_min>minimal) global_min=minimal;
#endif
				D2D1_2.assign(D2D1.begin(),D2D1.end());
				l2.clear();
				}
				continue;
					}
			for(long long k=0;k<2;k++)
			{
				vector<long long> ls;
				ls.clear();
				struct Band* lastmin=bb(i+1,k,band1,band2,D2D1,ls);
				if ((minimal>max(lastmin->GL,lastmin->TX))||(minimal==max(lastmin->GL,lastmin->TX)&&(min->GL+min->TX)>(lastmin->GL+lastmin->TX)))	
				{
						minimal=max(lastmin->GL,lastmin->TX);
						min->GL=lastmin->GL;
						min->TX=lastmin->TX;
						l2.assign(ls.begin(),ls.end());
						D2D1_2.assign(D2D1.begin(),D2D1.end());
					}
			}
		}
		if(toolarge!=4)
		l2.insert(l2.begin(),j+D2D1_2[i]*2);
                l_s.assign(l2.begin(),l2.end());
                return min;
	}
	else{
	long long band1=band1_1;
	long long band2=band2_1;
	vector<long long> D2D1;
                        D2D1.assign(D2D1_1.begin(),D2D1_1.end());
                        
                        if(j==0&&D2D1[i]==0)
                                band1+=global[i][0]*glob_lat[2]+global[i][1]*glob_lat[1]+global[i][2]*glob_lat[0];
                        else if(j==1&&D2D1[i]==0)
                                band2+=texture1D[i][0]*tex_lat[2]+texture1D[i][1]*tex_lat[1]+texture1D[i][2]*tex_lat[0];
                        else if(j==0&&D2D1[i]==1)
                                band2+=texture2D[i][0]*tex2D_lat[2]+texture2D[i][1]*tex2D_lat[1]+texture2D[i][2]*tex2D_lat[0];
                        else if(j==1&&D2D1[i]==1)
                                band1+=surface[i][0]*surf_lat[2]+surface[i][1]*surf_lat[1]+surface[i][2]*surf_lat[0];
#ifdef BB
			if(max(band1,band2)>global_min)
                        {
                        min->GL=99999999;
                        min->TX=99999999;
			return min;
			}
#endif
                        if((i+1)==total_instr)
                                {min->GL=band1;min->TX=band2;
                                        l_s.push_back(j+D2D1[i]*2);
#ifdef BB
				if(global_min>max(band1,band2)) global_min=max(band1,band2);
#endif
                                        return min;
                                        }
                        long long minimal=999999999;
                        for(long long k=0;k<2;k++)
                        {
                                vector<long long> ls;
                                ls.clear();
                                struct Band* lastmin=bb(i+1,k,band1,band2,D2D1,ls);
                                if (minimal>max(lastmin->GL,lastmin->TX)||(minimal==max(lastmin->GL,lastmin->TX)&&(min->GL+min->TX)>(lastmin->GL+lastmin->TX)))
                                        {
                                                minimal=max(lastmin->GL,lastmin->TX);
                                                min->GL=lastmin->GL;
                                                min->TX=lastmin->TX;
                                                l2.assign(ls.begin(),ls.end());
                                        }
                        }
                                l2.insert(l2.begin(),j+D2D1[i]*2);
                                l_s.assign(l2.begin(),l2.end());
                return min;
	}
	}
long long cluster[5]={0,1,1,1,1};
long long L1[5]={0,2,4,5,5};
long long L2[5] ={1,3,3,3,3};
long long sh_lat;


int main(int argc, char *argv[])
{
struct timespec t1,t2,t3;
clock_gettime(CLOCK_MONOTONIC,&t1);
std::vector<long long>  size_of;
std::vector<long long> dimension;
std::vector<long long> block_X;
std::vector<long long> block_Y;

std::vector<vector<long long> > stride;

long long count = 0;

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

    

for(long long  i =0; i<count;i++)
{
	if (dataTable[i][0]=="dimension")
		for(long long  j = 1; j<dataTable[i].size();j++)
		dimension.push_back(std::stol(dataTable[i][j]));
		//dimension.assign(dataTable[i].begin()+1,dataTable[i].end());
	else if (dataTable[i][0]=="sizeof")
		 for(long long  j = 1; j<dataTable[i].size();j++)
                size_of.push_back(std::stol(dataTable[i][j]));

	else if (dataTable[i][0]=="block_X")
		 for(long long  j = 1; j<dataTable[i].size();j++)
                block_X.push_back(std::stol(dataTable[i][j]));

	else if (dataTable[i][0]=="block_Y")
		 for(long long  j = 1; j<dataTable[i].size();j++)
                block_Y.push_back(std::stol(dataTable[i][j]));

	else if (dataTable[i][0]=="array_size")
		 for(long long  j = 1; j<dataTable[i].size();j++)
                array_size.push_back(std::stol(dataTable[i][j]));
	else
	{
		vector<long long> temp;
		for (long long j = 0; j<6;j++)
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
long long global_size = 0;

for(long long  i=0;i<count;i++)
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

	else if (dataTable[i][0]=="texture1D")
		{
                tex_lat.push_back(std::stol(dataTable[i][4]));
		tex_lat.push_back(std::stol(dataTable[i][7]));
		tex_lat.push_back(std::stol(dataTable[i][10]));
		}
	 else if (dataTable[i][0]=="texture2D")
                {
                tex2D_lat.push_back(std::stol(dataTable[i][4]));
                tex2D_lat.push_back(std::stol(dataTable[i][7]));
                tex2D_lat.push_back(std::stol(dataTable[i][10]));
                }
	else if (dataTable[i][0]=="readonly")
		{
		s.push_back(std::stol(dataTable[i][1]));
                read_lat.push_back(std::stol(dataTable[i][2]));
		read_lat.push_back(std::stol(dataTable[i][5]));
		read_lat.push_back(std::stol(dataTable[i][8]));
		}
	else if (dataTable[i][0]=="surface")
                 {
                //cout<<dataTable[i][1]<<endl;
                //cout<<global_size<<endl;cout<<"7"<<endl;
                surf_lat.push_back(std::stol(dataTable[i][2]));
                surf_lat.push_back(std::stol(dataTable[i][5]));
                surf_lat.push_back(std::stol(dataTable[i][8]));

                }
/*
	else if (dataTable[i][0]=="shared")
		 sh_lat=std::stol(dataTable[i][3]);
*/
	else continue;
}

dataTable.clear();
ifstream myfile2("output_DP2.txt");
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


long long temp=0;

long long i=0;
long long array_no=0;
while(dataTable[i][0]=="constant")
{
	if(std::stol(dataTable[i][1])==array_no)
	temp++;
	else{
	instr.push_back(temp);
	temp=1;
	array_no=std::stoll(dataTable[i][1]);
	}
	i++;
}
instr.push_back(temp);
while(i<count)
{
vector<long long> temp;
	if(dataTable[i][0]=="constant")
	{
	
	temp.push_back(std::stol(dataTable[i][3]));
	temp.push_back(std::stol(dataTable[i][4]));
	temp.push_back(std::stol(dataTable[i][5]));
	constant.push_back(temp);
	i++;
	}
	
        else if(dataTable[i][0]=="global")
        {
        temp.push_back(std::stol(dataTable[i][3]));
        temp.push_back(std::stol(dataTable[i][4]));
        temp.push_back(std::stol(dataTable[i][5]));
	global.push_back(temp);
	i++;
        }
	else if(dataTable[i][0]=="texture1D")
        {
        temp.push_back(std::stol(dataTable[i][3]));
        temp.push_back(std::stol(dataTable[i][4]));
       	temp.push_back(std::stol(dataTable[i][5]));
	texture1D.push_back(temp);
	i++;
        }
	else if(dataTable[i][0]=="texture2D")
        {
        temp.push_back(std::stol(dataTable[i][3]));
        temp.push_back(std::stol(dataTable[i][4]));
        temp.push_back(std::stol(dataTable[i][5]));
	texture2D.push_back(temp);
	i++;
        }
	else if(dataTable[i][0]=="surface")
        {
        temp.push_back(std::stol(dataTable[i][3]));
        temp.push_back(std::stol(dataTable[i][4]));
        temp.push_back(std::stol(dataTable[i][5]));
	surface.push_back(temp);
	i++;
        }
	else {i++;continue;}
}	
std::sort(stride.begin(),stride.end());
clock_gettime(CLOCK_MONOTONIC,&t2);
cout<<t2.tv_sec-t1.tv_sec+(t2.tv_nsec-t1.tv_nsec)/1.e9<<endl;
std::vector<vector<string > > worklist;
worklist.assign(dataTable.begin(),dataTable.end());
long long prev=0;
long long put=0;
long long unprev=0;
// determine constant array,extract them
for(long long i =0;i<instr.size();i++)
{
	if(array_size[i]>=s[i]) continue;
	for(long long j=0;j<instr[i];j++)
	{
		if((std::stoi(worklist[unprev][3])*con_lat[2]+std::stoi(worklist[unprev][4])*con_lat[1]+std::stoi(worklist[unprev][5])*con_lat[0])*5<= \
		std::stoi(worklist[count/5+unprev][3])*glob_lat[2]+std::stoi(worklist[count/5+unprev][4])*glob_lat[1]+std::stoi(worklist[count/5+unprev][5])*glob_lat[0])
		{
		cout<<"array "<<i<<", expression "<<j<<" put in constant memory\n";
		put += 1;
		global.erase(prev+global.begin());
		texture1D.erase(prev+texture1D.begin());
		texture2D.erase(prev+texture2D.begin());
		surface.erase(prev+surface.begin());
		//instr[i]--;	
		prev--;
		}
		prev++;
		unprev++;
	}

	if(put!=0) {instr[i]-=put;s[i]-=array_size[i];}
	put=0;
}
#ifdef DEBUG
for(long long i =0;i<global.size();i++)
{cout<<global[i][0]<<" "<<global[i][1]<<" "<<global[i][2]<<endl;
cout<<texture2D[i][0]<<" "<<texture2D[i][1]<<" "<<texture2D[i][2]<<endl;
cout<<surface[i][0]<<" "<<surface[i][1]<<" "<<surface[i][2]<<endl;
}
#endif
for(long long i=0;i<instr.size();i++)
{
	if(instr[i]!=0) {instr_after.push_back(instr[i]); cout<<instr[i]<<endl;
	}
}
for(long long i=0;i<instr_after.size();i++)
{	total_instr+=instr_after[i];
for(long long  j=0;j<instr_after[i];j++)
        instr_to_array.push_back(i);
}
for(long long i=0;i<instr_to_array.size();i++)
{cout<<instr_to_array[i]<<endl;}
//vector<long long> D2D1;
/*long long location=0;
//determin 1D or 2D, only consider the traffic
for(long long i=0;i<instr_after.size();i++){
	long long sum1D=0;
	long long sum2D=0;
	if(instr_after[i]==0) continue;
	for(long long j =0 ;j<instr_after[i];j++){
	sum1D += global[location][0]+global[location][1]+global[location][2];
	sum2D += surface[location][0]+surface[location][1]+surface[location][2];
	location++;
	}
	if(sum1D<=sum2D)
	{
 for(long long j =0 ;j<instr_after[i];j++)
	D2D1.push_back(0);
	}
	else{
 for(long long j =0 ;j<instr_after[i];j++)
	D2D1.push_back(1);
	}
}*/
// choose from global or texture 1D
long long band1=0; long long band2=0;
//for(long long i=0; i<global.size();i++)
//{
//for(long long i=0;i<D2D1.size();i++)
long long min=999999999;
struct Band *mini=(struct Band*)malloc(sizeof(struct Band));
long long record;
vector<long long> D2D1;
vector<long long> ll;
for(long long i=0;i<2;i++){
vector<long long> list;
struct Band* bb2=bb(0,i,band1,band2,D2D1,list);
long long lastmin=max(bb2->GL,bb2->TX);
if((min>lastmin)||(min==lastmin&&(mini->GL+mini->TX)>(bb2->GL+bb2->TX)))
	{
		min=lastmin;
		mini->GL=bb2->GL;
		mini->TX=bb2->TX;
		record=i;
		ll.assign(list.begin(),list.end());
		}
}
//}
for(int x=0;x<ll.size();x++)
cout<<ll[x]<<",";
cout<<min<<endl;

clock_gettime(CLOCK_MONOTONIC,&t3);
cout<<"time for global: "<<t3.tv_sec-t2.tv_sec+(t3.tv_nsec-t2.tv_nsec)/1.e9<<endl;
  return 0;
}
