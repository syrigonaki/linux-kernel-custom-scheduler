/*Aikaterini Syrigonaki - csd5109*/
#include<linux/kernel.h>
#include<linux/uaccess.h>
#include<linux/errno.h>
#include<linux/sched.h>
#include<linux/hy345_param_header.h>

asmlinkage long sys_get_scheduling_params(struct d_params __user * params) {

	struct d_params parameters;

        printk(KERN_INFO "Aikaterini Syrigonaki - csd5109 : get_scheduling_params\n");	
	if (params==NULL) return EINVAL;

	
	
	if (!access_ok(VERIFY_READ, params, sizeof(struct d_params))) return EINVAL;
	if (copy_from_user(&parameters, params, sizeof(struct d_params))) return EINVAL;

	parameters.deadline_1 = current->deadline_1;
	parameters.deadline_2 = current->deadline_2;
	parameters.computation_time = current->computation_time;
	
	if (!access_ok(VERIDY_WRITE, params, sizeof(struct d_params))) return EINVAL;
	if (copy_to_user(params, &parameters, sizeof(struct d_params))) return EINVAL;

	return 0;



}
