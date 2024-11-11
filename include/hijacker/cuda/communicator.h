#include "communication.h"
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int communicate_with_server(const char *socket_name, CuDriverCallStructure *send_structure, CuDriverCallReplyStructure *recv_structure);
int communicate_with_server_extra(const char *socket_name, CuDriverCallStructure *send_structure, CuDriverCallReplyStructure *recv_structure,void *jitOptions,void **jitOptionsValues,void* libraryOptions,void **libraryOptionValues);
int communicate_with_server_launchkernel(const char *socket_name, CuDriverCallStructure *send_structure, CuDriverCallReplyStructure *recv_structure,void *parameters_metadata);