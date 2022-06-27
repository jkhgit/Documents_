/* it is an example */
//Author: github.com/jkhgit
//date: 2022.04.06

monitor boundedbuffer;
char buffer [size_of_buffer];
int nextin, nextout;
int count;
cond notfull, notempty

void append(char x) {
	if (count == N) cwait(notfull);
	buffer[netxin] = x;
	nextin = (nextin + 1) % N;
	count++;
	csignal(notempty);
}

void take(char x) {
	if (count == 0) cwait(notempty);
	x = buffer[nextout];
	nextout = (nextout + 1) % N;
	count--;
	csignal(notfull);
}
{
	nextin = 0, nextout = 0, count = 0;
}

void producer() {
	char x;
	while (true) {
		produce(x);
		append(x);
	}

}

void consumer() {
	char x;
	while (true) {
		take(x);
		consume(x);
	}
}

void main() {
	parbegin (producer, consumer);
}
