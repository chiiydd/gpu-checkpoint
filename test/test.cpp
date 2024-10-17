
#include "cuda_hook.h"
#include "communication.h"
#include "communicator.h"

int main(){
    CuDriverCallStructure send_structure;
    CuDriverCallReplyStructure recv_structure;
    communicate_with_server(NULL, &send_structure, &recv_structure);

    return 0;
}