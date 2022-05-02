Threads
==================
process vs thread
*resources are allocated on a process-by-process basis*

process: running program
thread: a unit of execution (like exec functions)

*concurrency(look like) vs parallel(physics)*

case
------------------
1. [1 proces 1 thread] e.g. MS DoS
2. [1 process multi threads] e.g. Java VM
3. [multi process 1 thread] e.g. classic os
4. [multi process multi thread] e.g. Linux, Windows ...

scheduling & dispatching
------------------
os
user level
kernel level

(ULT)
	App & Thread		User level
@@@@@@@@@@@@@@@@@@@@@@@@@
	Process				Kernel level

(KLT)
	App & Thread		User level
@@@@@@@@@@@@@@@@@@@@@@@@@
	Process & Thread	Kernel level

state
------------------
thread has states
Running, Ready, Blocked, etc ...
=> TCB

process has its state.
thread also has its state. => concurrency (if unicore)
thread also do "context switching". it is faster than process's

synchronize
------------------
Resources are allocated and protected on a process-by-process basis
if killed process, All thread are killed.


+) *multi instance*
