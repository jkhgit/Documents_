example
==================

can setting
------------------

1. setting
::
	$ ip link set can0 type can bitrate 125000
	$ ip link set can0 up
	$ ip -d link show can0

2. can info
::
	bitrate 125000 sample-point 0.875
	tq 500 prop-seg 6 phase-seg1 7 phase-seg2 2 sjw 1 # sync-seg = 1 (fixed)
	mcp251x: tseg1 3..16 tseg2 2..8 sjw 1..4 brp 1..64 brp-inc 1
	clock 8000000 numtxqueues 1 numrxqueues 1 gso_max_size 65536 gso_max_segs 65535

*paprams calculation*

- bitrate: 125K
- Tbit: 1 / 125K = 8us
- seg: sync-seg + prog-seg + phase-seg1 + phase-seg2 = 1 + 6 + 7 + 2 = 16
- tq: 16 / Tbit = 16 / 8us = 500ns

targets
------------------

1. receive target
::
	candump can0

2. transmit target
::
	cansend can0 500#a5.a5.a5.a5.a0.a0.a0.a0

oscilloscope
------------------

case 1. use 1ch

 1ch: GND - BUS-L

case 2. use 2ch

- 1ch: GND - BUS-H
- 2ch: GND - BUS-L

standard can signal
::
	01010000010000010100010100101101001011010010110100101101000001101000001101000001101000001 ..............
	|  |   | |  || |    |       |       |       |       |       ||       ||       ||       || \      \      \
	|  |   | |  || |    |       |       |       |       |       ||       ||       ||       ||  \      \      \
	|  |   | |  || |    |       |       |       |       |       ||       ||       ||       ||   \      \      \
	S 5|  0| | 0|| |    |    a.5|    a.5|    a.5|    a.5|    a.0||    a.0||    a.0||    a.0||    \      \      \
	O        |   | |    |                                        |        |        |        |     \      \      \
	F        |   R | CTR|                                        |        |        |        |      \      \      \
	         |   B |                                             |        |        |        |       |     |      |
	         |     |                                             |        |        |        |       |     |      |
	         stuff stuff                                         stuff    stuff    stuff    stuff   | CRC |  EOF |

*Make sure to check the 1-bit time with the oscilloscope*
