/* it is an example */
//Author: github.com/jkhgit
//date: 2022.04.07

/* Readers/Writers Problem Using message passing */

/* Conditions:
 * 1. any number of readers may simultaneously read the file
 * 2. only one Writers at a time may wirte to the file
 * 3. if a writer is Writing to the file, no reader may read it. reverse of cource
 * => mutual exclution: readers <-> writer and writer <-> writer 
 * => no mutual exclution: readers <-> readers
 */

void reader(int i) {
	message rmsg;
	while (true) {
		rmsg = i;
		send(readrequest, rmsg);
		receive(mbox[i], rmsg);
		READUNIT();
		rmsg = i;
		send(finished, rmsg);
	}
}

void writer(int j) {
	message rmsg;
	while (true) {
		rmsg = j;
		send(writerequest, rmsg);
		receive(mbox[j], rmsg);
		WRITEUNIT();
		rmsg = j;
		send(finished, rmsg);
	}
}

void controller() {
	while (true) {
		if (count > 0) {
			if (!empty(finished)) {
				receive(finished, msg);
				count++;
			}
			else if (!empty(writerequest)) {
				receive(writerequest, msg);
				writer_id = msg.id;
				count = count - 100;
			}
			else if (!empty(readrequest)) {
				receive(readrequest, msg);
				count--;
				send(msg.id, "OK");
			}
		}
		if (count == 0) {
			send(writer_id, "OK");
			receive(finished, msg);
			count = 100;
		}
		while (count < 0) {
			receive(finished, msg);
			count++;
		}
	}
}
