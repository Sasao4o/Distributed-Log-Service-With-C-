#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <csignal>
#include "serf-cpp/SerfAgent.h"

using namespace SerfCpp;

const char* QUEUE_NAME = "/my_queue";
const mode_t QUEUE_PERMISSIONS = 0660;
const size_t MAX_MSG_SIZE = 256;

// Signal handler for SIGINT (Ctrl+C)
// void sigintHandler(int sig) {
//     // Just ignore SIGINT in this example
// }

int main() {
    // Create message queue
    mqd_t mq;
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;
    SerfAgent agent;

    mq = mq_open(QUEUE_NAME, O_CREAT | O_RDWR, QUEUE_PERMISSIONS, &attr);
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        return 1;
    }

    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        return 1;
    } else if (child_pid == 0) { // Child process (producer)
        // Set up signal handler to ignore SIGINT
        //signal(SIGINT, sigintHandler);

        std::cout << "Child process executing system call..." << std::endl;

        // Execute the system call using system()
        std::string command = "serf agent &"; 
        if(system(command.c_str()) == 0){
            std::cout << "Command executed successfully." << std::endl;
            //initializeSerfAgent(nodeConfig.getIPAddress(), nodeConfig.getPort());
            if (mq_send(mq, "System call finished", 20, 0) == -1) {
                perror("mq_send");
            }
        } else {
            throw std::runtime_error("Failed to create serf agent with the specified config");
        }

        // Send a message to the parent indicating that the system call finished
        
        return 0;
    } else { // Parent process (consumer)
        std::cout << "Parent process waiting for notification..." << std::endl;

        char msg[MAX_MSG_SIZE];
        ssize_t bytes_read = mq_receive(mq, msg, MAX_MSG_SIZE, NULL);
        if (bytes_read == -1) {
            perror("mq_receive");
            return 1;
        }

        std::cout << "Parent process received notification: " << msg << std::endl;
        std::cout<<"Trying to connect ....."<<std::endl;
        agent.Connect();

        // Cleanup
        mq_close(mq);
        mq_unlink(QUEUE_NAME);
    }

    return 0;
}
