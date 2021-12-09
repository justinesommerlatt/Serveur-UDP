//TP fait en intégralité, question 6 incluse



#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

int max(int * sockets){
    int max = sockets[0];
    for(int i = 1; i < sizeof(sockets); i++){
        if(sockets[i] > max){
            max = sockets[i];
        }
    }
    return max;
}

int create_socket(int*  sock){
    *sock = socket(AF_INET, SOCK_DGRAM, 0);
     if (sock < 0){
        perror("Error creating socket");
        exit(-1);
    }
    return *sock;
}

struct sockaddr_in init_sockaddr_in(struct sockaddr_in *sock_addr_in, int port){
    sock_addr_in->sin_family = AF_INET; 
    sock_addr_in->sin_port = htons(port); 
    sock_addr_in->sin_addr.s_addr = INADDR_ANY; 
    return *sock_addr_in;
}

void bind_socket(int sock, struct sockaddr_in sock_addr_in){
    if(bind(sock, (struct sockaddr*)&sock_addr_in, sizeof(sock_addr_in)) <0){
        perror("Error binding socket");
        exit(-1);
    }
}

void socket_processing(int sock, int port){
    struct sockaddr_in client_addr;
    char msg[1024];
    socklen_t client_addr_len = sizeof(struct sockaddr_in);
    if(recvfrom(sock, msg, 1024, 0, (struct sockaddr*)&client_addr, &client_addr_len) == -1){
        perror("Error recvfrom");
    }
    else{
        printf("Message (port %d) : %s\n", port, msg);
        client_addr.sin_port = htons(port + 1);
        printf("sendto port %d\n", htons(client_addr.sin_port));
        socklen_t client_addr_len = sizeof(struct sockaddr_in);
        if(sendto(sock, msg, strlen(msg), 0, (struct sockaddr*)&client_addr, client_addr_len) == -1){
            perror("Error sendto");
        }
    }
}

int main(int argc, char *argv[]) {
    if(argc != 3){
        printf("Number of argument invalid, 2 arguments needed, %d provided\n", argc-1);
        return -1;
    }

    int start_port = atoi(argv[1]);
    int end_port = atoi(argv[2]);
    int nb_ports = (end_port- start_port) / 2; // nombre de port qui vont être écoutés

    int * sockets = malloc(sizeof(int) * nb_ports); // allocation d'un tableau qui va contenir toutes les sockets
    struct sockaddr_in *tabSockaddr = malloc(sizeof(struct sockaddr_in) * nb_ports); // allocation d'un tableau qui va contenir toutes les sockaddr_in 
    for (int i = start_port, n = 0; i <= end_port; i+=2, n++){
        sockets[n] = create_socket(&sockets[n]); // création de la socket
        tabSockaddr[n] = init_sockaddr_in(&tabSockaddr[n], i); // init de sa sockaddr_in
        bind_socket(sockets[n], tabSockaddr[n]); // bind de la socket et sockaddr_in
    }

    while(1){
        fd_set fdSockets;
        FD_ZERO(&fdSockets);
        for (int i = start_port, n = 0; i <= end_port; i+=2, n++){
            FD_SET(sockets[n], &fdSockets);
        }
        if(select(max(sockets) + 1 , &fdSockets, NULL, NULL, 0) >=0){
            for (int i = start_port, n = 0; i <= end_port; i+=2, n++){
                if(FD_ISSET(sockets[n], &fdSockets)){
                    socket_processing(sockets[n], i);
                }
            }
        }
    }

    for (int i = start_port, n = 0; i <= end_port; i+=2, n++){
        close(sockets[n]);
    }
    free(sockets);
    free(tabSockaddr);
    return 0;
}