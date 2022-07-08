dump_stack
==================

linux/kernel.h

.. code-block:: C

	dump_stack();

Outputs the called functions when coming to dump_stack().

ftrace
==================

/sys/kernel/debug/tracing

trace event or functions in kernel *su*

1. event::

	echo 1 > events/sched/sched_wakeup/enable
	echo 1 > tracing_on
	cat trace # or vi trace

+ finish event trace::

	cat /dev/null > trace
	echo 1 > events/sched/sched_wakeup/enable

2. function::

	sysctl kernel.ftrace_enabled=1             (ftrace enable)
	echo function > current_trace              (ftrace trace current_trace)
	echo hrtimer_interrupt > set_ftrace_filter (hrtimer_interrupt trace function)
	echo 1 > tracing_on                        (ftrace start)
	(wait...)
	echo 0 > tracing_on                        (ftrace finish)
	cat trace                                  (check result)

3. function graph::

	sysctl kernel.ftrace_enabled=1       (ftrace enable)
	echo function_graph > current_tracer (ftrace trace current_trace)
	echo 1 > tracing_on                  (ftrace start)
	(wait...)
	echo 0 > tracing_on                  (ftrace stop)
	cat or                               (check result)

4. specific function with graph::

	sysctl kernel.ftrace_enabled=1           (ftrace enable)
	echo function_graph > current_tracer     (ftrace trace current_trace)
	echo scheduler_tick > set_graph_function (ftrace trace `scheduler_tick`)
	echo 1 > tracing_on                      (ftrace start)
	(wait...)
	echo 0 > tracing_on                      (ftrace finish)
	cat or                                   (check result)

printk
==================

linux/kernel.h

.. code-block:: C

	printk("%s %d\n", __func__, __LINE__);

system call
==================

in linux::

	User space		Aplication
	=======================================
	Kernel space	device / network / ...

	User space <--(communication)--> User space: ipc
	User space <--(request)-- Kernel space: ipc / system call

strace
==================

- install::

	$ sudo apt install strace

e.g.

1. binary trace::

	$ strace ls

2. specific system call trace

target: ls, system call: open::

	$ strace -e open ls

target: ls, system call: open, read::

	$ strace -e trace=open,read ls /home

3. save strace result::

	$ strace -o output.txt ls

4. strace process *if strace PID=1725*::

	$ sudo strace -p 1725 -o output.txt

5. strace with print time info::

	strace -t -e open ls /home

6. print relative time between system calls::

	$ strace -r

7. create system call's info::

	$ strace -c ls /home

