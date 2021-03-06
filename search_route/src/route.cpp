#include "route.h"
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>

using namespace std;

typedef struct Node
{
	int nodeID;
	int edgeID;
	int len;
	int weight;
	int used;
	struct Node *nextN;
}Node;

/*typedef struct hNode
{
	int nodeID;
	struct Node *nextN;
}hNode;*/

struct Node *head[600];

void buildMap(char *topo[5000], int edge_num);
void insertNode(int degeID, int nodeIDs, int nodeIDe, int edgeLen);
void init();
void shortest_route(int start, int end, int *keyNode, int len);
int finNext(int current, int *keyNode, int len, int end);
bool iskey(int temp, int *keyNode, int len);

//你要完成的功能总入口
void search_route(char *topo[5000], int edge_num, char *demand){
    //unsigned short result[] = {2, 6, 3};//示例中的一个解
	//cout<<"hello world!"<<endl;
	init();
	buildMap(topo, edge_num);
	int start, end;
	char *keyNode, keychar[50];
	keyNode = (char*)malloc(50);
	char com;
	sscanf(demand, "%d%c%d%c%s", &start, &com, &end, &com, keychar);
	int key[50]; //读取要经过的点
	int key_num = 1;
	int i = 1;
	int len = strlen(keychar);
	keyNode = keychar;
	sscanf(keyNode, "%d", &key[0]);
	keyNode = keyNode+1;
	while(i < len)
	{
		i+=2;
		keyNode = keyNode+1;
		sscanf(keyNode, "%d", &key[key_num++]);
		keyNode = keyNode+1;
	}
	cout<<key[key_num-2]<<endl;
	head[start] -> weight =0;
	shortest_route(start, end, key, key_num);
}

void buildMap(char *topo[5000], int edge_num)
{
	int len = 0;
	while (len < edge_num)
	{
		int edgeID, nodeIDs, nodeIDe, edgeLen; 
		char com;
		sscanf(topo[len], "%d%c%d%c%d%c%d", &edgeID, &com, &nodeIDs, &com, &nodeIDe, &com, &edgeLen);
		insertNode(edgeID, nodeIDs, nodeIDe, edgeLen);
		++len;
	}
}

void insertNode(int edgeID, int nodeIDs, int nodeIDe, int edgeLen)
{
	Node *Nodeh = head[nodeIDs];
	Node *p;
	p = (Node*)malloc(sizeof(Node));
	p -> edgeID = edgeID;
	p -> nodeID = nodeIDe;
	p -> len = edgeLen;
	while (Nodeh ->nextN != NULL)
	{
		Nodeh = Nodeh -> nextN;
	}
	Nodeh ->nextN = p;
	p -> nextN = NULL;
}

void init()
{
	for (int i = 0; i < 600; i++)
	{
		head[i] = (Node*)malloc(sizeof(Node));
		head[i] -> nextN = NULL;
		head[i] -> weight = INT_MAX;
		head[i] ->used = 0;
	}
}

void shortest_route(int start, int end, int *keyNode, int len)
{
	int current;
	vector <int> result;
	result.push_back(start);
	current = start;
	/*Node *p = head[current] -> nextN;
	while (p!=NULL)
	{
		cout<<p->nodeID<<endl;
		p = p->nextN;
	}
	system("pause");*/
	while (current != end)
	{
		current = finNext(current, keyNode, len, end);
		result.push_back(current);
		head[current]->used = 1;
		cout<<current<<endl;
	}
}

int finNext(int current, int *keyNode, int len, int end)
{
	int lengh, temp, flag = 0, lenghk, key=0;
	Node *p = head[current] -> nextN;
	while (p != NULL)
	{
		if (p->nodeID == end)
		{
			return end;
		}
		lengh = head[current] -> weight + p -> len;
		lenghk = head[current] -> weight + p -> len;
		if (iskey(p->nodeID, keyNode, len) && !(head[p->nodeID]->used))
		{
			flag = 1;
		}else{flag = 0;}
		switch (flag)
		{
		case 0:
			if ((head[p->nodeID]->weight > lengh) && !key && !(head[p->nodeID]->used))
		{ 
			temp = p->nodeID;
			head[p->nodeID]->weight = lengh;
		}
			break;
		case 1:
			if ((head[p->nodeID]->weight >= lenghk) && !(head[p->nodeID]->used))
		{
			key = 1;
			temp = p->nodeID;
			head[p->nodeID]->weight = lengh;
		}
			break;
		}
		p = p->nextN;
	}
	return temp;
}

bool iskey(int temp,int *keyNode, int len)
{
	for (int i = 0; i < len; i++)
	{
		if (keyNode[i] == temp)
		{
			return 1;
		}
	}
	return 0;
}