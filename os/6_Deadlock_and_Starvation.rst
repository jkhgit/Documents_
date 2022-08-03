Deadlock
==================

conditions
------------------

- mutual exclution
- hold and wait
- no pre-emption
- circular wait

*All* four conditions must be met.

trouble shooting: Breaking Breaking one of the four conditions

- mutual exclution (impossible)
- hold and wait 

1. Simultaneous processing of resources

2. *resource order*

- no pre-emption
- circular wait

Solve-Deadlock
==================

- Prevention
- Avoidance
- Detection

Prevention
------------------

static solution.

- resource get order

1. circular wait

p1 <- r1, p1 -> r2

p2 <- r2, p2 -> r3

p3 <- r3, p3 -> r1

2. resource order

p1 <- r1, p1 -> r2

p2 <- r2, p2 -> r3

p3 <- r3, p3 -> r1 (x)

p3 get r3 after get r1, so circular wait must be broken

Avoidance
------------------

dynamic solution.

: banker's algorithm

.. code-block:: C

  int resource_table[3] = {9, 3, 6}; // r1, r2, r3

  int claim_table[][3] = {
  /*	r1, r2, r3	*/
  	{3, 2, 2}, // p1
  	{6, 1, 3}, // p2
  	{3, 1, 4}, // p3
  	{4, 2, 2}  // p4
  }

  int alloc_table[][3] = {
  /*	r1, r2, r3	*/
  	{1, 0, 0}, // p1
  	{6, 1, 2}, // p2
  	{2, 1, 1}, // p3
  	{0, 0, 2}  // p4
  }

  int need_table[][3] = {
  /*	r1, r2, r3	*/
  	{2, 2, 2}, // p1
  	{0, 0, 1}, // p2
  	{1, 0, 3}, // p3
  	{4, 2, 0}  // p4
  }

int useful_table[3] = {1, 1, 1} // r1, r2, r3

Avoidance: Prevent the Deadlock situation *in advance.*

it is causes overhead

in this situation, p2: possible, others: impossible.

run p1 -> useful: 6, 1, 3 then, others: possible.


Detection
------------------

dynamic solution.

Detection: Kill the process that causes the deadlock

overhead(Avoidance) vs Deadlock damage(Detection)
