# HTTPS Client

### This is a very simple implementation of a HTTPS client that connects to Google's DNS server over HTTPS, sends a GET request and prints the server's response.

## Compilation

`gcc main.c -o https_client -lssl -lcrypto`