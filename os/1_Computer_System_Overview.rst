Os
==================
Window, Android, MacOs, Linux...

*for*
1. Resource Utilization *
2. User Interface (GUI, CLI)

Concepts
------------------
CPU # logical concept
Micro Processor # physical concept
GPU
SIMD
DSP
(etc ...)

CPU, Register
------------------
PC # Program Counter
IR # Instruction Register
MAR # Memory Address Register
MBR # Memory Buffer Register
Execution Unit

Resource
------------------
1. Processor # ISA ...
2. Main memory # volatile
3. I/O modules # usb, sata, pci, ...
4. System Bus


System
------------------
START - Fetch - Excute - Interrupt Check or HALT

1. normal operation
2. exception
	2-1. exception # Divide by zero, Invalid memory ...
	2-2. Interrupt # I/O devices, Timer ...
	2-3. S/W Interrupt # os system call

* ISR = Interrupt Service Routine (Interrupt handler)

Memory Hierarchy
==================

- amount
- speed
- expense

1. cpu # e.g. 1ns
2. cache # e.g. 4ns
3. main-memory # e.g. 100ns
4. HDD # e.g. 10ms

case1. cpu <-> main-memory # a + b = c
a(100ns) +(1ns) b(100ns) = c(100ns) # 301ns

case2. cpu <-> cache # a + b = c
a(4ns) +(1ns) +b(4ns) = c(4ns)

=> principle of Locality (temporal, spatial)
	...use cache memory
	cpu + cache => C.A
	main-memory + HDD => os (virtual memory)


    *word        block*
*cpu <---> cache <---> main-memory*
    *fast        slow*


