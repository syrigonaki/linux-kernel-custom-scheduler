#ifndef _HY345_SCHEDULING_PARAMS_H
#define _HY345_SCHEDULING_PARAMS_H

#include <linux/types.h>

struct d_params {
	long deadline_1; 
	long deadline_2; 
	long computation_time;  
};

#endif 
