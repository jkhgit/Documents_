/* it is an example */
//Author: github.com/jkhgit
//date: 2022.04.06

struct semaphore {
	int flag;
	int count;
	queueType queue;
};

static void semWait(semaphore s) {
	while (compare_and_swap(s.flag, 0, 1) == 1) {
	}
	s.count--;
	if (s.count < 0) {
		/* place this process in s.queue */
		/* block this process and set s.flag to 0 */
	}
	s.flag = 0;
}

static void semSignal(semaphore s) {
	while (compare_and_swap(s.flag, 0, 1) == 1) {
	}
	s.count++;
	if (s.count <= 0) {
		/* remove a process P form s.queue */
		/* place process P on ready list */
	}
	s.flag = 0;
}
