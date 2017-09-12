#include <stdio.h>
#include "packet.h"

#ifndef DEBUG_UTILS_H
#define DEBUG_UTILS_H

#define DEBUGS1(s) fprintf(stderr, "DEBUG: %s\n", s)
#define DEBUGSX(s) fprintf(stderr, "DEBUG: %u\n", s)
#define DEBUGN(d, s) fprintf(stderr,"DEBUG: %s: %d\n",d,s)
#define DEBUGS(d, s) fprintf(stderr,"DEBUG: %s: %s\n",d, s)
#define INFON(d, s) fprintf(stdout, "INFO: %s: %d\n", d, s)
#define INFOS(d, s) fprintf(stdout, "INFO: %s: %s\n", d, s)


void debug_print_pkt(struct packet *);
void debug_print_hdr(struct header *);

#endif
