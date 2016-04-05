#include "route.h"
#include "io.h"
#include "stdio.h"
#include<iostream>
using namespace std;
int main(int argc, char *argv[])
{
    char *topo[5000];
    int edge_num;
    char *demand;
    int demand_num;

    char topo_file[10] = "topo.csv";
    edge_num = read_file(topo, 5000, topo_file);
    if (edge_num == 0)
    {
        printf("Please input valid topo file.\n");
        return -1;
    }
	
    char demand_file[15] = "demand.csv";
    demand_num = read_file(&demand, 1, demand_file);
    if (demand_num != 1)
    {
        printf("Please input valid demand file.\n");
        return -1;
    }
	cout<<"searching....."<<endl;
    search_route(topo, edge_num, demand);

   // char *result_file = argv[3];
   // write_result(result_file);
   // release_buff(topo, edge_num);
   // release_buff(&demand, 1);
	return 0;
}

