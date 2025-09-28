# ****************************************************************************
#
# ****************************************************************************

CC = gcc -g
LDFLAGS = 

all: portscan

portscan: portscan.c
	${CC} ${LDFLAGS} portscan.c -o $@

clean:
	rm -f core *.o portscan portscan~
