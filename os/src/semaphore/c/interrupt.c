/* it is an example */
//Author: github.com/jkhgit
//date: 2022.04.06

struct semaphore {
	int flag;
	int count;
	queueType queue;
};

static void semWait(semaphore s) {
	inhibit interrupts;
	s.count--;
	if (s.count < 0) {
		/* place this process in s.queue */
		/* block this process and allow interrupts */
	}
	allow interrupts
}

static void semSignal(semaphore s) {
	inhibit interrupts;
	s.count++;
	if (s.count <= 0) {
		/* remove a process P form s.queue */
		/* place process P on ready list */
	}
	allow interrupts;
}
