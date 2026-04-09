# Custom Linux Scheduler Policy

Implementation of a custom scheduling policy in the Linux 2.6.38.1 kernel, extending the default scheduler to support deadline-based tasks with controlled execution time.

## Overview

This project modifies the Linux scheduler to prioritize custom tasks based on deadline-related parameters and terminate them once their computation time is exhausted.

Only tasks explicitly configured with custom scheduling parameters participate in the new policy. All other tasks fall back to the default Linux scheduler.

## Implementation Details

The following changes were made to the kernel:

1. **Task Initialization**
   - Default deadline values are set to `-1` for all existing tasks in `__sched_fork()`.
   - Tasks with `deadline_1 != -1` are treated as custom-scheduled tasks.

2. **Task Selection**
   - Implemented a new `pick_next_task_v2()` function.
   - Calculates a scheduling value for each custom task and selects the task with the greatest value.
   - If no custom tasks are found, returns `NULL` and the default scheduler is used.

3. **Scheduler Integration**
   - When a custom task is selected:
     - Its `vruntime` is set to `0`.
     - The default `pick_next_task()` is invoked to finalize scheduling.

4. **Completion Time Tracking**
   - Introduced a new `task_struct` field: `remaining_ct`.
   - Completion time is calculated as:
     ```
     x = now + remaining computation time
     ```

5. **Runtime Updates**
   - `remaining_ct` is updated inside `schedule()` when the previous task is a custom task (`deadline_1 > -1`).

6. **Task Termination**
   - When `remaining_ct` reaches zero:
     - The task is marked for termination (`tsk->to_kill = 1`).
     - The task is terminated via `do_exit()`.

7. **Cleanup**
   - `do_exit()` triggers one final `schedule()`.
   - The task is marked as dead in `finish_switch_task()` after the context switch.

## Prebuilt Kernel Image

A prebuilt kernel image (`bzImage`) is included in the repository.

This image was compiled from the modified Linux 2.6.38.1 kernel sources and already contains:
- The custom scheduling policy
- The extended `task_struct` fields
- All related scheduler and system call modifications

This allows the kernel to be booted directly (e.g. in QEMU) without recompiling the kernel.

## Known Issues

* `remaining_ct` is measured in nanoseconds but decreases much more slowly than expected.
* As a workaround during testing, tasks were terminated when remaining_ct <= ~1.98 seconds (≈ 1,980,000,000 ns) instead of `0`, to avoid excessively long runtimes.

## Testing

Two user-space test programs are provided to validate the scheduler behavior.

### Compilation

```bash
make all
```

Remove the executable using:

```bash
make clean
```

## Notes

*Kernel modifications are located inside the Linux 2.6.38.1 source tree.
*Only the files modified for this project are included in the repository, in their correct directory structure.




