#include "packet.h"
#include "stringutils.h"
#include "debugutils.h"
#include <netinet/in.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <error.h>


int sendpkt(int sock, void *pkt, int flag, unsigned int seq_id, char * payload,  struct sockaddr_in *remote_r, unsigned int remote_length){
  
  fill_packet(pkt, flag, seq_id, payload);
  return sendwithsock(sock, pkt, remote_r, remote_length);

}

int waitforpkt(int sock, void *prev_pkt,void *pkt, struct sockaddr_in *from_addr, unsigned int * from_addr_length_r, struct sockaddr_in *remote, unsigned int remote_length){
  int nbytes;
  DEBUGS1("Wait for Pkt Method : Start");
  while(1) {
    nbytes = recvwithsock(sock, pkt, from_addr, from_addr_length_r);
    
    if(nbytes == PACKET_SIZE){ 
      DEBUGN("Bytes Received", nbytes);
      break;
    }
    /*else if(nbytes == EAGAIN || nbytes == EWOULDBLOCK)*/
    else {
      DEBUGS1("No Response Tramsmitting again");
      nbytes = sendwithsock(sock, prev_pkt, remote, remote_length);
      DEBUGN("Bytes Sent", nbytes);
    }
  }
  DEBUGS1("Wait for Pkt Method : End");
  return nbytes;
}
int sendwithsock(int sock, void *pkt, struct sockaddr_in *remote, unsigned int remote_length) {
  // TODO: Surety that this command is sent as a single chunk
  return sendto(sock, pkt, PACKET_SIZE, 0, (struct sockaddr *)remote, remote_length);
}

int recvwithsock(int sock, void *pkt, struct sockaddr_in * from_addr, unsigned int * from_addr_length_r) {
  // recvfrom stores the information of sender in from_addr
  // This will keep on blocking in case the messages are lost while in flight
  return recvfrom(sock, pkt, PACKET_SIZE, 0, (struct sockaddr *)from_addr, from_addr_length_r);
}

void fill_packet(struct packet* pkt, short int flag, short int seq_id, char *payload){
	fill_header(pkt, flag, seq_id);
	fill_payload(pkt, payload);
}
void fill_header(struct packet* pkt, short int flag, short int seq_id){
  bzero(pkt, sizeof(struct packet));
  pkt->hdr.seq_id = seq_id;
  pkt->hdr.flag = flag;
}

void fill_payload(struct packet* pkt, char *payload){
  bzero(pkt->payload, sizeof(pkt->payload));
  if (pkt->hdr.flag == ACK) { 
    // Do Nothing
  } else if (pkt->hdr.flag == READ) {
    // Sending file name in the packet; only for seq_id == 0
    if (pkt->hdr.seq_id == 0) {
      strcpy(pkt->payload, get_second_string(payload));
      pkt->hdr.offset = (unsigned short) (strlen(payload) - 4); // get filename.txt 4:"get "
    
    }
  } else if (pkt->hdr.flag == 2) {
  } else if (pkt->hdr.flag == 3) {
  } else if (pkt->hdr.flag == 4) {
  } else if (pkt->hdr.flag == 5) {
  } else if (pkt->hdr.flag == 6) {
  } 
}

