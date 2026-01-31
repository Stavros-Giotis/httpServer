#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>


int main() {
    int server_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    
    
    //Create the Socket File Descriptor and check if it returns 0(=failure)
    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    // Forcefully attaching socket to the port 8080
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    //Adress definition
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //Listen on 0.0.0.0
    address.sin_port = htons(8080); // Port 8080

    //Bind the socket to the address and check if the generic pointer we asked worked 
    if(bind(server_fd,(struct sockaddr *)& address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    //listen to the current socket
    if(listen(server_fd, 1) != 0) {
        perror("listening failed");
        exit(EXIT_FAILURE);
    }

    while(1) {
        printf("\nWaiting for a connection...\n");
        int new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);
                
        //Read the data from the socket
        char buffer[1024] = {0};
        read(new_socket, buffer, 1024);
        
        char *hello = "HTTP/1.1 200 OK\n\nHello from C!";
        write(new_socket, hello, strlen(hello));

        // print what we received
        printf("Received Request:\n%s\n", buffer);

        close(new_socket);
    }
    return 0;

}

