#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/init.h>		/* Needed for the macros */
#include <linux/pid.h>
#include <linux/cred.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");

static int pid = 0;

module_param(pid,int,0000);

static int __init startup(void)
{
	const struct cred *old;
	struct cred *new;
	struct task_struct *task;
	
	if (pid) {
		printk(KERN_INFO "Giving root powers to %d...\n",pid);
		rcu_read_lock();
		task = get_pid_task(find_vpid(pid),PIDTYPE_PID);
		if (task) {
			old = task->real_cred;
			new = prepare_creds();
			new->suid = new->uid = new->fsuid = new->euid = 0 ;
			get_cred(new);
			if (new->user != old->user)
				atomic_inc(&new->user->processes);
			rcu_assign_pointer(task->real_cred, new);
			rcu_assign_pointer(task->cred, new);
			if (new->user != old->user)
				atomic_dec(&old->user->processes);

			put_cred(old);
			put_cred(old);
		}
		rcu_read_unlock();
	}
	return 0;
}

static void __exit shutdown(void)
{
    printk(KERN_INFO "Unplugging module\n");
}

module_init(startup);
module_exit(shutdown);
