Concurrency
==================

routine

p1 ---(p1 backcup)---> p2 ---(p2 backup)---> p3 ...

*Problems arise in shared resources as they try to maintain concurrency in limited resources.*

for concurrency,
	- atomic operation
	- critical section
	- deadlock
	- livelock
	- mutual exclution
	- starvation

e.g.

shared resource a = 100

.. code-block:: C

	/* process 1 */
	a = a + 10;
	/* process 2 */
	a = a - 10;

reverse assemble ...

.. code-block:: Assembly

	/* process 1 */
	MOV r1, a // line 1
	ADD r1, r1, 10 // line 2
	MOV a, r1 // line 3

	/* process 2 */
	MOV r1, a // line 4
	ADD r1, r1, ~10+1 // line 5
	MOV a, r1 // line 6

if interrupt occured at line 1, 
p1 (ready) -> a = 100 (p1 registers backup)
p2 (exit) -> a = 90
p1 (exit) -> a = 110

then, it is *wrong*

.. code-block:: C

	a = 100;
	a = a + 10;
	a = a - 10; // a = 110

So, concurrency is need *mutual exclution*::
"Special section that use shared resources do not lose permission to execute."
Special section:*critical section*
to do not lose permission to execute: *atomic operation*

Mutual exclution
==================

for concurrency, os must solve situation that multi processes use shared resources.
so almost processes have *critical section*.
side effects: *deadlock*, *starvation*

- atomic operation

interrupt enable/disable: The simplest and most ignorant

- critical section

protected section from program switching.

in critical section, there is guaranteed *mutual exclution*.

=> use *atomic operation* as the method

- deadlock

a state in which the same shared resource is required but each has a different one

p1 (r1, r2) p2

p1 has r1

p2 has r2

p1 request r2 and p2 request r1

but Nothing can be done. because *mutual exclution*

- starvation

problems of resources like deadlock / livelock or program prior, state in which a process is not running

Semaphore
==================

a integer var (flag) for support *mutual exclution*
if os doesn't use semaphores, There may be the following problems
there are several examples about *atomic operation* for *mutual exclution*
it's goot method but it's not replacements

For *mutual exclution*

case 1. enter function.

.. code-block:: C

	int flag = 1;

	void enter() { //there is critical section
		while (flag != 1); // Line 1
			flag = 0; // Line 2
	}

	void exit() {
		...
	}

	int main() {
		...
		// <<- interrupt disable
		enter(); // Line 3
		// <<- interrupt enable
		/* critical section */
		exit();
		flag = 1;

		return 0;
	}

*Disadvantage: it also causes deadlock and starvation*

case 2. Hardware Support funcs

(1) compare_and_swap

.. code-block:: C

	const int n = m; // number of processes
	int bolt;
	void P(int i) {
		while (true) {
			while (compare_and_swap(&bolt, 0, 1) == 1); // Line 1
				/* critical section */ //Line 2
			bolt = 0; // Line 3
			/* remainder */
		}
	}

	int main() {
		bolt = 0;
		parbegin (P(1), P(2), P(3), ... P(m));

		return 0;
	}

+ Line 1: check value of *bolt* and write 1 in *bolt*
		if (*bolt* == 0), access *critical section*
+ Line 2: *bolt* = 1. regardless of the *bolt* value, 1 was written in Line 1.
+ Line 3: *bolt* initialize

(2) exchange

.. code-block:: C

	const int n = m; // number of processes
	int bolt;
	void P(int i) {
		while (ture) {
			int keyi = 1;
			do exchange(&keyi, &bolt); // Line 1
			while (keyi != 0); // Line 2
			/* critical section */ // Line 3
			bolt = 0; // Line 4
			/* remainder */
		}
	}

	int main() {
		bolt = 0;
		parbegin (P(1), P(2), P(3), ... P(m));

		return 0;
	}

+ Line 1: change value *keyi* <---> *bolt*
		then, if (*keyi* == 0), access critical section
+ Line 4: *bolt* initialize

Disadvantage: busy waiting, starvation

*Semaphores* solve almost Disadvantages.

Semaphore

.. code-block:: C

	const int n = m; // number of processes
	semaphore s = 1;
	/* semaphore */
	struct semaphore {
		int count;
		queueType queue; // Other structures may be used
	}

	void semWait(semaphore s) {
		s.count--;
		if (s.count < 0) {
			/* place this process in s.queue */
		}
	}

	void semSignal(semaphore s) {
		s.count++;
		if (s.count <= 0) {
			/* remove a process P from s.queue */
			/* place process P on ready list */
		}
	}

	void P(int i) {
		while (true) {
			semWait(s);
			/* critical section */
			semSignal(s);
			/* remainder */
		}
	}

	int main() {
		parbegin (P(1), P(2), P(3), ... P(m));

		return 0;
	}

*semaphore 's' process 'p'*

s = n, n: accessable(critical section) number of process

s = 0, p: accessable critical section

s < 0, p: can't access critical section, another process is already in use.

+ *mutex*

"lock", "unlock" in same process.

semaphore (wait, signal) ~ mutex (lock, unlock)

producer-consumer problem
------------------

producer: 1 or more. make data, push *buffer*

consumer: only 1. take data in *buffer*

so, shated resource: *buffer*

In particular, it is assumed to be an *infinite buffer*.

An Incorrect Solution to the *Infinite-Buffer* producer/consumer Problem Using semaphores

expect trouble
- buffer access (it will support mutual exclution)
- buffer empty

.. code-block:: C

	int n; // number of data

	void producer() {
		while (true) {
			prodece();
			append();
			n++;
		}
	}

	void consumer() {
		while (true) {
			take();
			n--;
			consume();
		}
	}

	int main() {
		n = 0;
		parbegin (producer, consumer);

		return 0;
	}

In this case, critical section is 2 area.

- producer's critical section

.. code-block:: C

	append();
	n++;

- consumer's critical section

.. code-block:: C

	take();
	n--;

because they are associated with *buffer*

Using semaphore

.. code-block:: C

	int n; // number of data
	semaphore s = 1; // protect buffer

	void producer() {
		while (true) {
			prodece();
			semWait(s); // add semaphore
			append();
			n++;
			semSignal(s); // add semaphore
		}
	}

	void consumer() {
		while (true) {
			semWait(s); // add semaphore
			take();
			n--;
			semSignal(s); // add semaphore
			consume();
		}
	}

	int main() {
		n = 0;
		parbegin (producer, consumer);

		return 0;
	}

then, when buffer is empty,

it will be waiting infinitely.

.. code-block:: C

	int n; // number of data
	semaphore s = 1; // protect buffer
	semaphore delay = 0; // program syncronization

	void producer() {
		while (true) {
			prodece();
			semWait(s); // protect buffer
			append();
			n++;
			if (n == 1) semSignal(delay); // sync
			semSignal(s); // protect buffer
		}
	}

	void consumer() {
		while (true) {
			semWait(s); // protect buffer
			take();
			n--;
			semSignal(s); // protect buffer
			consume();
			if (n == 0) semWait(delay); // sync
		}
	}

	int main() {
		n = 0;
		parbegin (producer, consumer);

		return 0;
	}

syncronization: new semaphore delay init 0.

when consumer run semWait, semaphore value -1, waiting right away

then producer push data (n: 0 -> 1), semSignal(delay) delay = 0

consumer escape waiting status

But, when running consumer at first, it is also trouble

.. code-block:: C

	int n; // number of data
	semaphore s = 1; // protect buffer
	semaphore delay = 0; // program syncronization

	void producer() {
		while (true) {
			prodece();
			semWait(s);
			append();
			n++;
			if (n == 1) semSignal(delay);
			semSignal(s);
		}
	}

	void consumer() {
		semWait(delay); // trouble shooting running at first
		while (true) {
			semWait(s);
			take();
			n--;
			semSignal(s);
			consume(); // Line 1
			if (n == 0) semWait(delay); // Line 2
		}
	}

	int main() {
		n = 0;
		parbegin (producer, consumer);

		return 0;
	}

Line 2: this line use shared resource 'n', there is not protected section.

if interrupt occure in Line 1, it is problem.

It is producer/consumer solution in *infinite buffer*

.. code-block:: C

	int n; // number of data
	semaphore s = 1; // protect buffer
	semaphore delay = 0; // program syncronization

	void producer() {
		while (true) {
			prodece();
			semWait(s);
			append();
			n++;
			if (n == 1) semSignal(delay);
			semSignal(s);
		}
	}

	void consumer() {
		int m; // a local variable
		semWait(delay);
		while (true) {
			semWait(s);
			take();
			n--;
			m = n;
			semSignal(s);
			consume();
			if (m == 0) semWait(delay);
		}
	}

	int main() {
		n = 0;
		parbegin (producer, consumer);

		return 0;
	}

we can use "the number of data" as semaphore

.. code-block:: C

	semaphore n = 0; // semaphore and number of data
	semaphore s = 1; // protect buffer

	void producer() {
		while (true) {
			prodece();
			semWait(s);
			append();
			semSignal(s);
			semSignal(n);
		}
	}

	void consumer() {
		while (true) {
			semWait(n);
			semWait(s)
			take();
			semSignal(s);
			consume();
		}
	}

	int main() {
		parbegin (producer, consumer);

		return 0;
	}

but buffer is not infinite.
so buffer used *circular buffer*
and we have to check *"is buffer full?"*

<circular buffer>

b[1] b[2] b[3] ... b[size_of_buffer]

append: b[1] -> b[2] -> ... b[size_of_buffer] -> b[1] -> b[2] -> ...

take: b[1] -> b[2] -> ... b[size_of_buffer] -> b[1] -> b[2] -> ...

there is a solution that is deal with buffer full in *circular buffer*

.. code-block:: C

	semaphore n = 0; // semaphore and number of data
	semaphore e = size_of_buffer; // semaphore and size of buffer
	semaphore s = 1; // protect buffer

	void producer() {
		while (true) {
			prodece();
			semWait(e);
			semWait(s);
			append();
			semSignal(s);
			semSignal(n);
		}
	}

	void consumer() {
		while (true) {
			semWait(n);
			semWait(s)
			take();
			semSignal(s);
			semSignal(e);
			consume();
		}
	}

	int main() {
		parbegin (producer, consumer);

		return 0;
	}

semaphore n: for syncronization: number of data
semaphore e: for syncronization: size of buffer
semaphore s: for mutual exclution: protect shared resource

Finally, semaphore are used for *mutual exclution* & *syncronization*

==================

+ message paasing

Comunicate process and process
act *mutual exclution* & *syncronization*

Send
	- blocking
	- nonblocking e.g. speed sensor

Receive
	- blocking
	- nonblocking

Addressing
	- Direct
		- send
		- receive
			- explicit
			- implict
	- InDirect
		- static
		- dynamic
		- ownership

message format

	TLV: Tag-Length ----value----

		<-(header)-><-(payload)->

.. code-block:: C

	/* producer/consumer problem */
	const int capacity = size_of_buffer;
	null = '/0';

	int i;

	void producer() {
		message pmsg;
		while (true) {
			receive(mayproduce, pmsg);
			pmsg = produce();
			send(consume, pmsg);
		}
	}

	void consumer() {
		message cmsg;
		while (true) {
			receive(mayconsume, cmsg);
			consume(cmsg);
			send(mayproduce, null);
		}
	}

	int main() {
		create_mailbox(mayproduce);
		create_mailbox(mayconsume);
		for (int i = 1; i <= size_of_buffer; i++) send(mayproduce, null);
		parbegin(producer, consumer);
	}


