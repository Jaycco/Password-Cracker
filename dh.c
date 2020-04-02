/* modified from Client for 5.1.1-5.1.3 from sample code */

#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

/* code modified from Modular Exponentiation geeksforgeeks.org */
int power(int a, unsigned int b, int p)
{
    int result = 1;
    a = a % p;
    while (b > 0)
    {
        if (b & 1)
            result = (result*a) % p;
        b = b >> 1;
        a = (a * a) % p;
    }
    return result;
}
/* code modified from Modular Exponentiation geeksforgeeks.org */

/* modified from Client for 5.1.1-5.1.3 from sample code */
int main(int argc, char ** argv)
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent * server;

    portno = 7800;

    /* Translate host name into peer's IP address ;
     * This is name translation service by the operating system */
    server = gethostbyname("172.26.37.44");

    char buffer[256];

    if (argc < 1)
    {
        fprintf(stderr, "usage %s b-in-decimal\n", argv[0]);
        exit(EXIT_FAILURE);
    }


    if (server == NULL)
    {
        fprintf(stderr, "ERROR, no such host\n");
        exit(EXIT_FAILURE);
    }

    /* Building data structures for socket */

    bzero((char *)&serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;

    bcopy(server->h_addr_list[0], (char *)&serv_addr.sin_addr.s_addr, server->h_length);

    serv_addr.sin_port = htons(portno);

    /* Create TCP socket -- active open
     * Preliminary steps: Setup: creation of active open socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("ERROR opening socket");
        exit(EXIT_FAILURE);
    }

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("ERROR connecting");
        exit(EXIT_FAILURE);
    }

    /* Send username
    */
    printf("Send the username: \n");

    strcat(buffer, "zengbinz");
    strcat(buffer, "\n");

    printf("----%s----\n", buffer);

    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0)
    {
        perror("ERROR writing to socket");
        exit(EXIT_FAILURE);
    }

    /* get b from argv and send g^b(modp) to server */
    int result, b, A;
    int g = 15;
    int p = 97;
    b = atoi(argv[1]);
    result = power(g, b, p);
    sprintf(buffer, "%d", result);
    strcat(buffer, "\n");
    printf("b:---%d--", b);
    printf("Send the g^b(modp)---%s---\n", buffer);
    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0)
    {
        perror("ERROR writing to socket");
        exit(EXIT_FAILURE);
    }

    /* get A */
    n = read(sockfd, buffer, 255);
    if (n < 0)
    {
        perror("ERROR reading from socket");
        exit(EXIT_FAILURE);
    }
    buffer[n] = 0;
    A = atoi(buffer);

    /* send A^b(modp) to server */
    result = power(A, b, p);
    sprintf(buffer, "%d", result);
    strcat(buffer, "\n");
    printf("Send the (g^b)^a(modp)---%s---\n", buffer);
    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0)
    {
        perror("ERROR writing to socket");
        exit(EXIT_FAILURE);
    }

    /* read success message */
    n = read(sockfd, buffer, 255);
    if (n < 0)
    {
        perror("ERROR reading from socket");
        exit(EXIT_FAILURE);
    }
    buffer[n] = 0;
    printf("%s\n", buffer);


    close(sockfd);

    return 0;
}
/* modified from Client for 5.1.1-5.1.3 from sample code */






