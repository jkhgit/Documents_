/* it is an example */
//Author: github.com/jkhgit
//date: 2022.04.07

/* Readers/Writers Problem */

/* Conditions:
 * 1. any number of readers may simultaneously read the file
 * 2. only one Writers at a time may wirte to the file
 * 3. if a writer is Writing to the file, no reader may read it. reverse of cource
 * => mutual exclution: readers <-> writer and writer <-> writer 
 * => no mutual exclution: readers <-> readers
 */

int readcount;
semaphore x = 1; // protect readcount
semaphore wsem = 1; // mutual exclution readers <-> writer

void reader() {
	while (true) {
		semWait(x); // "readcount" is shared resource among the readers
			readcount++;
			// no mutual exclution readers <-> readers
			// mutual exclution readers <-> writer
			if (readcount == 1) semWait(wsem);
		semSignal(x);
		READUNIT();
		semWait(x);
			readcount--;
			if (readcount == 0) semSignal(wsem);
		semSignal(x);
	}
}

void writer() {
	while (true) {
		semWait(wsem); //mutual exclution writer <-> writer
		WRITEUNIT();
		semSignal(wsem);
	}
}

void main() {
	readcount = 0;
	parbegin (reader, writer);
}

/* it has a trouble that prior: readers > writer
 * if reader is called at 1st and writer is called at 2nd, writer's status become "blocked"
 * in this situation, other reader is called at next, writer can become starvation
 */
