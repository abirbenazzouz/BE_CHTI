#include "gassp72.h"
#include <stdio.h>

extern int sommecarre(int);
int fanion = 0;
int main(void)
{
	int min = sommecarre(0);
	int max = min;
	int s=0;
	for(int i = 1; i<64; i++){
		s = sommecarre(i);
		if (s>max) {
				max = s;
			}
		else if (s<min){
				min = s;
		}
	}
		
	
	
while	(1)
	{

	}
}
