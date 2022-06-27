/* it is an example */
//Author: github.com/jkhgit
//date: 2022.04.14

/* Conditions:
 * 1. No two philoshphers can use the same fork at the same time (mutual exclution)
 * 2. No philosopher ust starve to death (avoid deadlock and starvation)
 */

semaphore fork[5] = {1};
semaphore room = {4}
int i;

void philoshpher (int i) {
	think();
	semWait(room); // save from starvation
	semWait(fork[i]); // mutual exclution & resource order
	semWait(fork[(i+1) % 5]);
	eat();
	semSignal(fork[(i+1) % 5]);
	semSignal(fork[i]);
	semSignal(room);
}

int main() {
	parbegin (philoshpher(0), philoshpher(1), philoshpher(2),
			philoshpher(3), philoshpher(4));

	return 0;
}
