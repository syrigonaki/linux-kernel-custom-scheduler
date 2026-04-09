/*Aikaterini Syrigonaki - csd5109*/
#include<linux/kernel.h>
#include<linux/errno.h>
#include<linux/sched.h>


asmlinkage long sys_set_scheduling_params(long deadline_1, long deadline_2, long computation_time) {
	
	struct task_struct * curr_task = current;

	printk(KERN_INFO "Aikaterini Syrigonaki - csd5109 : set_scheduling_params\n");
	
	if (deadline_1 <=0 || computation_time <=0 || deadline_2 <= 0) return EINVAL;
	if (deadline_2 <= deadline_1) return EINVAL;
	if (computation_time/1000 > deadline_2) return EINVAL;
	
	curr_task->deadline_1 = deadline_1;
	curr_task->deadline_2 = deadline_2;
	curr_task->to_kill = 0;
	curr_task->computation_time = computation_time;
	curr_task->remaining_ct = computation_time * 1000000;
	return 0;
}

