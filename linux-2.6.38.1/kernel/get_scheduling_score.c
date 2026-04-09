#include<linux/kernel.h>
#include<linux/sched.h>
#include<linux/ktime.h>


asmlinkage long sys_get_scheduling_score() {
  	struct timespec ts;	
	struct task_struct * curr_task = current;
	long d3;
	ktime_get_ts(&ts);
	d3 = ts.tv_sec; 
	printk(KERN_INFO "Aikaterini Syrigonaki - csd5109 : get_scheduling_score\n");
	
	long d1 = curr_task->deadline_1;
	long d2 = curr_task->deadline_2;
	printk(KERN_INFO "D2 %ld  D3 %ld\n", d2,d3);  
	if (d3<d1) return 100;
	if (d3>d2) return 0;
	else return (((d2-d3)*100)/(d2-d1));

}
