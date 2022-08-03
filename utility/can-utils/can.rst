can
==================

refer to: *linux/Documentation/networking/can.rst*

protocol can / 2.0A / 2.0B / fd

2.0A: normal format

2.0B: extended format

fd: flexible bitrate & max 64 byte data

frame
------------------

[CAN 2.0A]: standard (44 + 8N)
::

  SOF(1) ID(11) RTR(1) IDE(1) RB(1) DLC(4) DATA(8N) CRC(15) DEL(1) ACK(2) EOF(7)

  <------------------------------------44+8N----------------------------------->

[CAN 2.0B]: extended (64 + 8N)
::

  SOF(1) ID(11) SRR(1) IDE(1) EID(18) RTR(1) RB(2) DLC(4) DATA(8N) CRC(15) DEL(1) ACK(2) EOF(7)

  <-----------------------------------------64+8N--------------------------------------------->

*RB: reserved*

params
------------------

- bitrate: speed of can-bus
- clk: clock of can device
- nbr: Nominal Bit Time: 1 / (bitrate)
- segments:
  1. sync: 1(fix)
  2. prop-seg: x
  3. phase-seg1: y
  4. phase-seg2: z
- sample-point: sync~phase-seg1, (1 + x + y) / (1 + x + y + z)
- tq: time quantum: nbr / (1 + x + y + z)

stuff bit
------------------

If the same bit comes out five times in a row, the next bit must use one opposite bit.

# e.g. some signal
::
  01010000010010...

stuff bit: 10bit, it is not affect data

command
==================

1. set & up
::
  [ ip link set ${CAN} type ${TYPE} bitrate ${BITRATE} ]

  $ ip link set canX type can bitrate 125000
  $ ip link set canX up

2. check node info
::
  [ ip ${OPTION} link show canX ] option: -d[etails] -s[tatistics] ...

  $ ip -d link show canX
