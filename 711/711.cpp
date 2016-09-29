#include <stdio.h>
#define range 42

int n[6], a[range], num_coins, sum, term=1, i, j, possible[147];
void read_to_array();
void set_possible_array();

int main(void) {
#ifndef ONLINE_JUDGE
	freopen("711.in", "r", stdin);
#endif
	while (scanf("%d %d %d %d %d %d", &n[0], &n[1], &n[2], &n[3], &n[4], &n[5]) == 6) {	
		if (n[0]==0 && n[1]==0 && n[2]==0 && n[3]==0 && n[4]==0 && n[5]==0)
			break;
		for(i=0; i<6; i++) if(n[i] > 6 ) n[i] = 6 + n[i]%2;		// reduce the number
		sum = 1*n[0] + 2*n[1] + 3*n[2] + 4*n[3] + 5*n[4] + 6*n[5];
		if(sum%2 != 0)
			printf("Collection #%d:\nCan't be divided.\n\n", term);
		else {
			for(i=0; i<range; i++) a[i] = 0;			// reset the *array all value to 0
			for(i=0; i<147; i++) possible[i] = 0;			// reset the *T_array all value to false
			possible[0]=1;
			read_to_array();					// put input into the array a[range]
			for(i=0; i<num_coins; i++) {
				for (j = 147 - a[i]; j >= 0; j--) 
					if (possible[j]) 
						possible[j + a[i]] = 1; 
			}
			printf("Collection #%d:\n", term);
			if( possible[sum/2] ) printf("Can be divided.\n\n");
			else printf("Can't be divided.\n\n");
		}
		term++;
	}
	return 0;
}

void read_to_array() {
	num_coins = n[0]+n[1]+n[2]+n[3]+n[4]+n[5];
	int i;
	for(i=0; i<sum; i++) {	
		int j=0;
		while(n[0]!=0) { a[j++] = 1; n[0]--;}
		while(n[1]!=0) { a[j++] = 2; n[1]--;}
		while(n[2]!=0) { a[j++] = 3; n[2]--;}
		while(n[3]!=0) { a[j++] = 4; n[3]--;}
		while(n[4]!=0) { a[j++] = 5; n[4]--;}
		while(n[5]!=0) { a[j++] = 6; n[5]--;}
	}
}

