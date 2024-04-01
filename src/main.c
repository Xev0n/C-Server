#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <string.h>

const char HOST[] = "localhost";
const int PORT = 9000;
const char SOCKET_NAME[] = "mysocket";

// Source: https://ftp.gnu.org/old-gnu/Manuals/glibc-2.2.3/html_chapter/libc_16.html
int create_socket(const char *filename) {

    struct sockaddr_un name;
    int sock;
    size_t size;

    /*
     The socket() function creates an unbound socket in a communications 
     domain, and returns a file descriptor that can be used in later 
     function calls that operate on sockets.
     The function takes the following arguments:
        domain
            Specifies the communications domain in which a socket is to be 
            created. 
        type
            Specifies the type of socket to be created. 
        protocol
            Specifies a particular protocol to be used with the socket. 
            Specifying a protocol of 0 causes socket() to use an unspecified
            default protocol appropriate for the requested socket type. 
     */
    sock = socket(PF_LOCAL, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("Could not create socket");
        exit (EXIT_FAILURE);
    }

    // Bind a name to the socket
    name.sun_family = AF_LOCAL;
    /*
        The C library function 
        char *strncpy(char *dest, const char *src, size_t n) copies up to 
        n characters from the string pointed to, by src to dest. 
        In a case where the length of src is less than that of n, 
        the remainder of dest will be padded with null bytes.
        The function takes the following arguments:
            dest
                This is the pointer to the destination array where the
                content is to be copied
            src
                this is the string to be copied
            n
                The number of characters to be copied from source
        The return value returns the pointer to the copied string.
    */
    strncpy(name.sun_path, filename, sizeof(name.sun_path));
    size = SUN_LEN(&name);

    if (bind(sock, (struct sockaddr *) &name, size) < 0) {
        perror("Could not bind socket");
        exit(EXIT_FAILURE);
    }

    return sock;
}

int main(int argc, char *argv[]) {
    printf("Creating socket listening on %s:%d\n", HOST, PORT);
    int sock = create_socket(SOCKET_NAME);
    
    // do cool stuff here
    
    //close(sock);
    return 0;
}
