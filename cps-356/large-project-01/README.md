# Questions

## 1. How to make scheduler run in `O(m)` time?

I think the simplest way to improve the time efficiency of the algorithm would be to store a list of runnable processes in addition to the full list of all processes. The list of runnable processes would need to be managed wherever process states are set, but assuming this is done, the scheduler could just loop through this list and thus only ever look at runnable processes.

This would result in `O(m)` performance for the scheduler, since it would be looping through runnable processes instead of all processes.

The round-robin part of the algorithm could be maintained by either using queue semantics for the list of runnable processes, or by simply ensuring that the list is sorted by process ID, since those only ever increment. The first option is preferable because of the edge case where PIDs loop back to `0`.

## 2. How to make scheduler run in O(log(m)) time?

## 3. What will happen if the process that is chosen to run does not release `ptable.lock`?

## 4. Based on the entire source code of `proc.c`, how can a zombie process be created?

Processes automatically go through the zombie state when `exit()` is called, but it's such a small period of time that we wouldn't ever notice. When `exit()` is called, the parent of the exiting process is made runnable, so once that parent calls `wait()` then it will take all of its zombie children and clear out the data for new processes to fill.

However, if, for whatever reason, the parent does not call `wait()` immediately, the child process will be stuck in the zombie state because `wait()` is the only function where zombie processes are cleaned up.

If the parent process exits without EVER calling `wait()` then the parent of the zombie child will be set to the `init` process, which will try to clean it up by calling `wait()` as it is supposed to (see line 65 of `init.c`). So, I don't think there is a way for processes to be left as zombies indefinitely...unless we never get around to running the `init` process again.

## 5. Does xv6 use preemptive scheduling?
