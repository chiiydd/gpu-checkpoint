#include "communication.h"
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int communicate_with_server(const char *socket_name, CuDriverCallStructure *send_structure, CuDriverCallReplyStructure *recv_structure);
