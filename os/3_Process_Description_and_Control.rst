Process
==================
process: a instance of running program
program: program cmd group

[program] -> (run)
			: process
				thread 1
				thread 2
				thread 3

*resource utilize -> by process*

multi-batch: change process by wait
time-sharing: change process by time
real-time transaction system: Round-Robin scheduling (RR)

2-state process model
------------------

*state*:
1. Not Running: not running program
2. Running: running program

*os*:
Dispatch

case ::
	1. (enter) -> "Not Running" -> Dispatch(OS) -> "Running" -> (exit)

	2. "Runnint" -> (pause) > "Not Running" -> (exit)

5-state process model
------------------

(if a single core)

*state*:
1. Ready: ready to run programs. they are at *program queue* (just wait running)
2. Running: run program it is only one process
3. Block: wait events. they are at *blocked queue*. if events are occured, they move to *program queue*
4. Blocked/suspended: when memory capacity is low, Move blocked processes to HDD
5. Ready/suspended: when memory capacity is low, Move Ready processes to HDD


*os*:
Dispatch

5 ~ 8: prcess swapping

case ::
	1. "New" -> (admit) -> "Ready" -> Dispatch -> "Running" -> (release) -> (exit)

	2. "Running" -> (time out) -> "Ready"

	3. "Running" -> (event wait) -> "Block"

	4. "Block" -> (events occurs) -> "Ready"

	5. "Block" -> (suspend) -> "Blocked/suspended"

	6. "Block/suspended" -> (activate) -> "Blocked"

	7. "Ready" -> (suspend) -> "Ready/suspended"

	8. "Ready/suspended" -> (suspend) -> "Ready"

Exception
------------------

1. Exception: e.g. divide by zero
2. Interrupt: intended exception(I/O) e.g.time quantum
3. SWI: software interrupt (Supervisor call, cmd)

Supervisor call (=system call) Use: SWI
	User mode -> System mode

*time quantum*: system call... Timer(H/W) -> ISR -> "os ~> CPU"
*Trap*: unintended exception

Cause of process err
------------------
1. process isolation
2. synchronization
3. mutual execlusion    e.g. if "process 1" use resource 'A',
									another process can't access 'A'.
4. deadlock
	one of process get resource 'A',
		don't release resource 'A'. => use scheduling


*process control block (PCB)*
1. program
2. data
3. context (process state)

PCB::

	Identifier
	---------------
	State
	---------------
	Priroity
	---------------
	Program counter
	---------------
	Memory pointer
	---------------
	Context data
	---------------
	I/O state
	information
	---------------
	Accounting
	information
	---------------
	...

Context switching
------------------

ps switching, save current ps's register & restore next ps
multi process are use same CPU

e.g.::
	ps 1 -> ps 2 
	
	CPU
	(ps 1)             ---> pc = 200
	r1 0 				context (backup)
	r2 1				r1 0
	r3 100				r2 1
	r4 200				r3 100
	pc = 200			r4 200

					 <context switching>

						(jump to id 2)			 CPU
						context (restore) --->  (ps 2)
						r1 22					r1 22
						r2 18					r2 18
						r3 0					r3 0
						r4 400					r4 400
						pc = 1100				pc = 1100


Process Management
------------------
1. Program code
2. A set of data

Processor(CPU): switching process make use of "time"

e.g.::
	App 1 -> App 2 -> App 3 -> App 4 -> App 1 -> ... (every 200ms)

Memory: switching process make use of "space"

e.g.::
	App 1 (addr 1000 ~ 2000)
	App 2 (addr 5000 ~ 8000)
	App 3 (addr 12000 ~ 12500)

Process New-creation
------------------

Cause
1. program run
2. os service call
3. user log in
4. start application
5. process spawn (parents ps, child ps)
etc...

order (kernel)
1st assigned pid
2nd allocate space for Process
3rd init PCB
4th set the appropriate linkages *.dll .so ...*
5th create or expand other data structure

Process Termination (exit)
------------------
1. normal completion
2. os service call
3. user log off
4. quitting application
etc...

Memory Management 
==================

1, process isolation
2. auto allocation Management
3. support of modular programing
4. protection and access control: virtual memory
5. long term storage

Memory map
------------------
process is in program.
process has stack

User Processes in Virtual memory
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
.Process Identifier
.Process State
.Process Control Information  __(PCB)
.User Stack
.Data
.Program Code
.Shared Address Space __(Application)

*physics: they are scattered in many space*
*process image*

Page
------------------

program ... Virtual Memory (paging)
			=> OS (MMU):
				=> Physical Memory

size >= 4kb: Unit of Memory Management Unit

Virtual vs Physics
------------------
Program: Virtual Memory
Real save: Physical Memory

Modes (Hardware)
==================
1. User Mode (Application)
- less-privileged mode
2. System Mode (OS, kernel mode)
- more-privileged mode

Kernel::
	Process Management: scheduling, sync(resource share), IPC
	Memory Management: page, swapping, segment...
	I/O Management:buffer, I/O channels, Interrupt, Monitoring...
	Support Functionsi:

Mode switching
------------------
User <.......> System

User -> SWI:(ISR) -> System
System -> User (always)
*Interrupt*: I/O
