
// ... set socket to non-blocking mode ...

fd_set readfds;
struct timeval timeout;

while (1) {
    FD_ZERO(&readfds);
    FD_SET(sockfd, &readfds); // Add socket to the set

    timeout.tv_sec = 1; // Timeout of 1 second
    timeout.tv_usec = 0;

    int ret = select(sockfd + 1, &readfds, NULL, NULL, &timeout);

    if (ret == -1) {
        perror("select()");
        // ... handle error ...
    } else if (ret == 0) {
        printf("Timeout\n"); // No data available
    } else {
        if (FD_ISSET(sockfd, &readfds)) { // Socket is readable
            int nbytes = read(sockfd, buffer, sizeof(buffer));
            // ... process data ...
        }
    }
}
