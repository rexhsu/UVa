#include<stdio.h>
#include<string.h>

#define max_junction 45

int max_road;

int ptr;
int node_count[max_junction];
int road_table[2000];
int road[2][2000];
int path[2000];
int target;

void circuit(int node, int street)
{
	int i;
	int point1 ,point2;

	point1 = node;
	for(i=1;i<=max_road;i++)
	{
		if (road_table[i]==1)
		{
			if (point1==road[0][i] || point1==road[1][i])
			{
				if (point1 == road[0][i])
					point2 = road[1][i];
				else
					point2 = road[0][i];

				road_table[i] = 0;
				circuit(point2, i);
			}
		}
	}

	if (i==max_road+1)
	{
		path[ptr] = street;
		ptr++;
		return;
	}
}

int count()
{
	int i;
	for (i=0;i<max_junction;i++)
		if (node_count[i]!=0 && node_count[i]%2!=0) return 1;
	return 0;
}

int main()
{
	int node1, node2, walk;
	int i, j=0;

#ifndef ONLINE_JUDGE
	freopen("302.in","r",stdin);
#endif

	while(1)
	{
		scanf("%d %d",&node1, &node2);

		if (node1==0 && node2==0) break;

		memset(node_count, 0, sizeof(node_count));
		memset(road_table, 0, sizeof(road_table));

		max_road = 0;

		ptr = 0;
		target = node1;
		if (target > node2) target = node2;

		while(1) {
			if (node1==0 && node2==0) break;
			node_count[node1]++;
			node_count[node2]++;
			scanf("%d",&walk);
			if (walk > max_road) max_road = walk;
			road_table[walk] = 1;
			road[0][walk] = node1;
			road[1][walk] = node2;
			scanf("%d %d",&node1, &node2);
		}

		if (count() == 1) {
			printf("Round trip does not exist.\n\n");
			continue;
		}
		circuit(target, 0);
		for(i=ptr-2;i>=0;i--) {
			if (!j) {
				printf("%d",path[i]);
				j = 1;
			} else
				printf(" %d",path[i]);
		}
		j = 0;
		printf("\n\n");
	}
	return 0;
}

