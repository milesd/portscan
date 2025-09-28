/*
 * internet port scanner
 *
 * This program will scan a hosts TCP ports printing all ports that accept
 * connections, and if known, the service name. This program can be trivially
 * altered to do UDP ports also.
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

#define MAX_PORT 1024 /* scan up to this port */

int s;
struct sockaddr_in addr;
char rmt_host[100];

int
skan(int port) {
	int r;
	s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s < 0) {
		printf("ERROR: socket() failed\n");
		exit(0);
	}
	addr.sin_family = PF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(rmt_host);

	r = connect(s, (struct sockaddr*)&addr, sizeof(addr));

	close(s);
	if (r == -1) {
		return (1 == 0);
	}
	return (1 == 1);
}

int
main(int argc, char* argv[]) {
	int a, b, c, d, e, f;
	struct hostent* foo;
	struct servent* bar;

	if (argc < 2) {
		fprintf(stderr, "usage: %s <host> [highest port]\n", argv[0]);
		exit(0);
	}
	if (sscanf(argv[1], "%d.%d.%d.%d", &a, &b, &c, &d) != 4) {
		foo = gethostbyname(argv[1]);
		if (foo == NULL) {
			fprintf(stderr, "error: cannot resolve host %s\n", argv[1]);
			exit(0);
		}
		sprintf(rmt_host, "%d.%d.%d.%d", (unsigned char)foo->h_addr_list[0][0],
			(unsigned char)foo->h_addr_list[0][1],
			(unsigned char)foo->h_addr_list[0][2],
			(unsigned char)foo->h_addr_list[0][3]);
	} else {
		strncpy(rmt_host, argv[1], 99);
	}


	if (argc > 2) {
		f = atoi(argv[2]);
	} else
		f = MAX_PORT;

	fprintf(stdout, "Scanning host %s - TCP ports 1 through %d\n", rmt_host, f);

	for (e = 1; e <= f; e++) {
		char serv[100];
		if (skan(e)) {
			bar = getservbyport(htons(e), "tcp");
			printf("%d (%s) is running.\n", e, (bar == NULL) ? "UNKNOWN" :
				bar->s_name);
		}
	}
}
