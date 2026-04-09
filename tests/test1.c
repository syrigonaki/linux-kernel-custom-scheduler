
#include <unistd.h>
#include<stdio.h>

int main() {
	set_scheduling_params(1,5,2000);
	while(1);

	return 0;
} 
