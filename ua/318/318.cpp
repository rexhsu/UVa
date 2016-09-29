#include <stdio.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAX_KEY 500
#define swap(x, y) ((t) = (x), (x) = (y), (y) = (t))

int t;
int num_keys, num_rows, distance[MAX_KEY][MAX_KEY], shortest[MAX_KEY];

int main(void) {

	int cases = 0;
#ifndef ONLINE_JUDGE
	freopen("318.in","r",stdin);
#endif

	while(1)
	{
		int i, j, k, key_1, key_2, seconds;
		cases++;
		// Reset arrays
		memset(shortest, -1, sizeof(shortest));
		for(i=0; i<MAX_KEY; i++)
			memset(distance[i], -1, sizeof(distance[i]));

		/********************debug message**********************
		  for(i=0; i<MAX_KEY; i++)
		  {
		  distance[0][i] = i;
		  distance[i][0] = i;
		  }
		/*******************************************************/

		scanf("%d %d", &num_keys, &num_rows);
		if(num_keys == 0 && num_rows == 0) break;	// End of input

		if(cases != 1) printf("\n");
		printf("System #%d\n", cases);

		if(num_keys == 0 || num_rows == 0) {	// No node or no path
			printf("The last domino falls after 0.0 seconds, at key domino 1.\n");
			continue;
		}

		for(i=0; i<num_rows; i++)	// scanf inputs and construct distance[][]
		{
			scanf("%d %d %d", &key_1, &key_2, &seconds);
			if(key_2 < key_1) swap(key_2, key_1);
			distance[key_1][key_2] = seconds;
		}

		/* store the distance[1][i] */
		for(i=1; i<=num_keys; i++) shortest[i] = distance[1][i];

		/* Warshall algorithm */
		for(k=1; k<=num_keys; k++)
			for(j=1; j<=num_keys; j++)
				if(distance[1][k] + distance[k][j] < distance[1][j] && distance[1][k]>0 && distance[k][j]>0)
					distance[1][j] = distance[1][k] + distance[k][j];

		/* set shortest[i] to be the shortest path from single source KEY #1
		   at the same time restore the distance[1][i] */
		for(i=1; i<=num_keys; i++) swap(shortest[i], distance[1][i]);

		shortest[1] = 0;	// shortest path from 1 to 1 is ZERO

		/**************************debug message ********************************
		  for(i=0; i<=num_keys; i++)
		  {
		  for(j=0; j<=num_keys; j++)
		  printf("%4d", distance[i][j]);
		  printf("\n");
		  }
		  printf("Shortest[] : ");
		  for(i=1; i<=num_keys; i++)
		  {
		  printf("%d ", shortest[i]);
		  }
		  printf("\n");
		//*************************************************************************/

		/* find the longest time */
		float max, min, dis = 0, longest = 0;
		int xa, xb;
		for(i=1; i<=num_keys; i++)
		{
			for(j=i; j<=num_keys; j++)
			{
				max = (float)shortest[i];
				if(distance[i][j] >= 0) 
				{
					min = (float)shortest[j];
					// You can easily understand below function if you draw a graph just have three points: 1, xa, xb
					dis = max + (0.5)*((float)distance[i][j] - (max-min));
					/* no matter max is greater or not the result is the same:
					   (1/2)(distance[i][j]) + (1/2)(max) + (1/2)(min) */

					if(dis>longest) 
					{
						longest = dis;
						xa = i; 
						xb = j;
						if(xa>xb) swap(xa, xb);		// output format must xa<xb
						if(longest == max) xb = 0;	// last domino is i
						if(longest == min)			// last domino is j
						{
							xa = xb;
							xb = 0;
						}
					}
				}
			}
		}

		// debug message
		//		printf("time = %.1f\n", longest);

		if(xb==0)	// that mean the last domino is key domino
			printf("The last domino falls after %.1f seconds, at key domino %d.\n",  longest, xa);
		else
			printf("The last domino falls after %.1f seconds, between key dominoes %d and %d.\n",  longest, xa, xb);
	}

	return 0;
}

