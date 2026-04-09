# Linux Kernel Custom Scheduler & System Calls

This project implements a custom deadline-based scheduling policy in the **Linux 2.6.38.1 kernel**. It extends the process descriptor (`task_struct`), introduces three new system calls for user-space interaction, and modifies the core scheduler logic to prioritize tasks based on custom scheduling scores.

## Features

### 1. Custom Scheduling System Calls
Added a specialized interface for user-space programs to communicate with the kernel:
* **`set_scheduling_params`**: Configures deadline parameters ($d1, d2$) and computation time ($ct$).
* **`get_scheduling_params`**: Safely retrieves parameters using `copy_to_user`.
* **`get_scheduling_score`**: Computes the real-time scheduling priority of the process.

### 2. Deadline-Based Scheduler Policy
Modified the core Linux scheduler (`kernel/sched.c`) to implement a prioritized selection algorithm:
* **Task Selection:** Implemented `pick_next_task_v2()`, which selects the task with the highest calculated scheduling value among custom tasks.
* **Fall-back Mechanism:** If no custom tasks are active, the system seamlessly falls back to the default Linux scheduler.
* **Execution Control:** Introduced `remaining_ct` (Completion Time) tracking. Tasks are automatically terminated via `do_exit()` once their allocated computation time is exhausted.

## Kernel Modifications
The implementation involved modifying key areas of the kernel source tree:
* **Process Management:** Modified `include/linux/sched.h` to expand `task_struct`.
* **System Call Table:** Registered new syscalls in `arch/x86/kernel/syscall_table_32.S` and `unistd_32.h`.
* **Scheduler Core:** Integrated custom logic into `schedule()` and `__sched_fork()`.
* **Memory Safety:** Used `access_ok` and `copy_from_user` to ensure secure data transfer between kernel and user space.

## Repository Structure
* **/linux-2.6.38.1**: Contains the specific modified source files in their correct directory structure.
* **/test_programs**: C programs and Makefiles to validate syscalls and scheduler behavior.
* **bzImage**: A prebuilt, compiled kernel image ready for booting in QEMU.

## Testing
User-space test programs are included to validate the behavior of the new system calls and the scheduler's prioritization.

### Compilation
```bash
make all
```

##  Technical Challenges & Observations

* **Clock Frequency & Timing Precision:** Tthe `remaining_ct` (measured in nanoseconds) decremented at a slower rate than the wall-clock time. 
* **Workaround:** To ensure consistent task termination during evaluation, the scheduler was configured to trigger `do_exit()` when `remaining_ct` reached a threshold (≈ 1.98s) rather than absolute zero. This suggests a scaling discrepancy between the guest kernel's Jiffies and the host hardware's high-resolution timers.
