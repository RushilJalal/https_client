#include <sys/socket.h>
#include <netinet/in.h>
#include <openssl/ssl.h>
#include <string.h>
#include <stdio.h>

void main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0); // creates new socket
    struct sockaddr_in addr = {
        AF_INET,
        htons(443),       // converts HTTPS port 443 from host byte order to network byte order
        htonl(0x08080808) // google dns - 8.8.8.8 - convert from host byte to network byte order
    };

    connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)); // open a connection on socket fd

    SSL_CTX *ctx = SSL_CTX_new(TLS_method()); // ssl context object
    SSL *ssl = SSL_new(ctx);                  // ssl object
    SSL_set_fd(ssl, sockfd);                  // connect ssl object to fd
    SSL_connect(ssl);                         // init tls connection using handshake

    char *req = "GET / HTTP/1.1\r\nHost: 8.8.8.8\r\n\r\n";
    SSL_write(ssl, req, strlen(req)); // write 'num' bytes to TLS/SSL connection

    char buffer[1024] = {0};
    SSL_read(ssl, buffer, sizeof(buffer) - 1);

    printf("Response:\n%s\n", buffer);
}
