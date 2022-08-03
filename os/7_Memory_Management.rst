Address
==================

Address: Location of memeory

Fragment
==================

fragment:

What happens when the amount of memory a program requires is greater or less than the amount of memory remaining

- internal fragment
- external fragment

Memory
==================

Requirements

- Relocation:

Required for swap between main memory and secondary memory

- protection:

Do not invade different memory spaces.

- Sharing:

Memory to be shared should be shared.

View

- Logical view:

Conceptually easy-to-see description of complex physical memory structures

- Physical view

Memory manageent
==================

frame / partition / page / segment

- frame: physical memory address
- partition: divide memory into parts
- paging: divide memory static sizes normally 4KB
- segment: divide memory dynamic sizes

partition
------------------
- fixed partitioning:

alloced partition size are equal (x)
alloced size are fixed (o)

- dynamic partitioning

alloced size are not fixed (o)

*dynamic*: runtime.

when running process, divide & allcate memory amount of process's requirements.

Best-fit:

- search all space, and select best fit

First-fit:

- search and select first appropriate space

Next-fit:

- search and select first appropriate space, then

next search: start searching after the last selected space.


partition common...

Memory allocated to one program must be *continuous*.

So, partitioning causes both internal fragment and external fragment

e.g. (fixed partitioning)

part 0: 0x0000 ~ 0x1000
part 1: 0x1001 ~ 0x3000
part 2: 0x3001 ~ 0x7000
part 3; 0x7001 ~ 0xA000

processes

p1 memory size: 0x1000

p2 memory size: 0x2000

p3 memory size: 0x2000

p4 memory size: 0x1000

p5 memory size: 0x3000

p6 memory size: 0x4000

- internal fragment

p1 -> part 0

p2 -> part 1

p3 -> part 2

p4 -. part 2

p5 -> part 3

part 2 occured internal fragment...

-external fragment

finish p2.

when run p6, memory has no space

page
------------------

divide *fixed size* (normal: 4KB)

page is address of process.

frame is address of physical memory.

Only internal fragments occur.

All processes have *page table*.

when context switching, they save frame offset based on pages.

if p1 need 64KB, it is divided by 4KB and scattered across physical addresses.

p1 has 16 entries (16 * 4KB)

Address: pageNum + offset

e.g. 32 bit address space

case 1. page# 31 ~ 26 offset# 25 ~ 0

[address register]::

  +--------+--------+
  |31~26(6)|25~0(26)|
  +========+========+
  |pageNum | offset | offset;00110100100111100110010100
  +--------+--------+

[page table]::

  +-----+--------+
  |page | frame  |
  +=====+========+
  |0    | 000101 |
  +-----+--------+
  |1    | 000110 |
  +-----+--------+
  |2    | 011001 |
  +-----+--------+
  ...

process's address: 0 -> 1 -> 2 ...

physical address:

	 31~26			25~0
	000110 00110100100111100110010100

Processes think they are using a series of addresses because of the page tables.

the number of page: 2^6 = 64

the size of page: 2^26 = 2^6 * 2^20 = 64MB

case 2. page# 31 ~ 12 offset# 11 ~ 0.

[address register]::

  +---------+--------+
  |31~12(20)|11~0(26)|
  +=========+========+
  |pageNum  | offset |
  +---------+--------+

the number of page: 2^20 = 1M

the size of page: 2^12 = 2^2 * 2^10 = 4KB

segment
------------------

divide *different sizes*

so each length shall be stored in segmentation.

Only external fragments occur.

e.g. 32 bit address space

[address register]::

	+--------+--------+
	|31~28(4)|27~0(28)|
	+========+========+
	|segment | offset | offset; ..0030
	+--------+--------+

[segmentation]::

	+---+------+------------+
	|idx|Length|Base address|
	+===+======+============+
	|0  |  L0  | 0xffd00000 |
	+---+------+------------+
	|1  |  L1  | 0xffd00000 |
	+---+------+------------+
	|2  |  L2  | 0xffd00000 |
	+---+------+------------+
	...

if segment = 1,

physical address (frame):

Base address + offset = 0xffd00030 then,

compare with L1. *verify out of memory*.
