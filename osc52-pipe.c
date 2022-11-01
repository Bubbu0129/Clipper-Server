#include <stdio.h>
#include <stdlib.h>

static const char base64_table[65] = 
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	"abcdefghijklmnopqrstuvwxyz"
	"0123456789+/";

static char cache[3];
static char* end = cache + 3;

int caching(void){
	char* pos;
	for (pos = cache; pos < end; pos++)
		if ((*pos = getchar()) == EOF)
			return (pos - cache);
	return -1;
}

int main(int argc, char* argv[]){
	// Find TTY device
	char* TTY_PATH;
	if (argc == 1)
		TTY_PATH = getenv("SSH_TTY");
	else
		TTY_PATH = argv[1];
	if (! TTY_PATH){
		fprintf(stderr, "Cannot locate TTY device. \nUsage: %s <TTY>\n", *argv);
		exit(EXIT_FAILURE);
	}
	// Direct output to TTY
	FILE* tty = freopen(TTY_PATH, "a+", stdout);
	if (! tty) {
		fprintf(stderr, "Cannot load TTY device %s. \nUsage: %s <TTY>.\n", TTY_PATH, *argv);
		exit(EXIT_FAILURE);
	}
	// OSC Header
	fputs("\e]52;c;", stdout);
	// Base64 Encryption
	// Body
	int state;
	char* pos;
	while ((state = caching()) == -1){
		pos = cache;
		putchar(base64_table[  *pos >> 2  ]);
		putchar(base64_table[((*pos++ & 0x03) << 4) | (*pos >> 4)]);
		putchar(base64_table[((*pos++ & 0x0f) << 2) | (*pos >> 6)]);
		putchar(base64_table[  *pos & 0x3f]);
	}
	// Rear
	pos = cache;
	switch (state){
		case 1:
			putchar(base64_table[  *pos >> 2]);
			putchar(base64_table[(*pos++ & 0x03) << 4]);
			putchar('='); putchar('=');
			break;
		case 2:
			putchar(base64_table[  *pos >> 2]);
			putchar(base64_table[((*pos++ & 0x03) << 4) | (*pos >> 4)]);
			putchar(base64_table[ (*pos++ & 0x0f) << 2]);
			putchar('=');
			break;
		default: // case 0 or -1:
			break;
	}
	// OSC Tail
	putchar('\a');

	return 0;
}


