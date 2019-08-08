#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctype.h>
#include <strings.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdint.h>

#define SERVER_STRING   "Server: tinyhttpd/0.1.0\r\n"

void accept_request(void *);
void error_die(const char *);
int get_line(int, char *, int);
int startup(u_short *);
void not_found(int);
void unimplemented(int);

/**********************************************************************/
/* A request has caused a call to accept() on the server port to
 * return.  Process the request appropriately.
 * Parameters: the socket connected to the client */
/**********************************************************************/
void accept_request(void *arg)
{
    int client = (intptr_t) arg;
    char buf[1024];
    size_t numchars;
    char method[255];
    char url[255];
    char path[255];
    size_t i, j;
    struct stat st;
    int cgi = 0;    /* becomes true if server decides this is a CGI
                     * program */
    char *query_string = NULL;

    numchars = get_line(client, buf, sizeof(buf));
    i = 0; j = 0;
    while (!isspace(buf[i]) && (i < sizeof(method) - 1)) {
        method[i] = buf[i];
        i++;
    }
    j = i;
    method[i] = '\0';

    if (strcasecmp(method, "GET") && strcasecmp(method, "POST")) {
        unimplemented(client);
        return;
    }

    if (strcasecmp(method, "POST") == 0)
        cgi = 1;

    i = 0;
    while (isspace(buf[j]) && (j < numchars))
        j++;
    while (!isspace(buf[j]) && (i < sizeof(url) - 1) && (j < numchars)) {
        url[i] = buf[j];
        i++;
        j++;
    }
    url[i] = '\0';

    if (strcasecmp(method, "GET") == 0) {
        query_string = url;
        while ((*query_string != '?') && (*query_string != '\0'))
            query_string++;
        if (*query_string == '?') {
            cgi = 1;
            *++query_string = '\0';
        }
    }

    sprintf(path, "htdocs%s", url);
    if (path[strlen(path) - 1] == '/')
        strcat(path, "index.html");
    if (stat(path, &st) == -1) {
        while (numchars > 0 && strcmp("\n", buf)) /* read & discard headers */
            numchars = get_line(client, buf, sizeof(buf));
        not_found(client);
    } else {
        if ((st.st_mode & S_IFMT) == S_IFDIR)
            strcat(path, "/index.html");
        if ((st.st_mode & S_IXUSR) || (st.st_mode & S_IXGRP) || (st.st_mode & S_IXOTH))
            cgi = 1;
        if (!cgi)
            printf("server_file(client, path);\n");
        else
            printf("execute_cgi\n");
    }

    close(client);
}

/**********************************************************************/
/* Print out an error message with perror() (for system errors; based
 * on value of errno, which indicates system call errors) and exit the
 * program indicating an error. */
/**********************************************************************/
void error_die(const char *sc)
{
    perror(sc);
    exit(1);
}

/**********************************************************************/
/* Get a line from a socket, whether the line ends in a newline,
 * carriage return, or a CRLF combination.  Terminates the string read
 * with a null character.  If no newline indicator is found before the
 * end of the buffer, the string is terminated with a null.  If any of
 * the above three line terminators is read, the last character of the
 * string will be a linefeed and the string will be terminated with a
 * null character.
 * Parameters: the socket descriptor
 *             the buffer to save the data in
 *             the size of the buffer
 * Returns: the number of bytes stored (excluding null) */
/**********************************************************************/
int get_line(int sock, char *buf, int size)
{
    int i = 0;
    char c = '\0';
    int n;

    while (i < size - 1 && c != '\n') {
        n = recv(sock, &c, 1, 0);
        if (n > 0) {
            if (c == '\r') {
                n = recv(sock, &c, 1, MSG_PEEK);
                if (n > 0 && c == '\n')
                    recv(sock, &c, 1, 0);
                else
                    c = '\n';
            }
            buf[i++] = c;

        } else {
            c = '\n';
        }
    }
    buf[i] = '\0';

    return i;
}

/**********************************************************************/
/* This function starts the process of listening for web connections
 * on a specified port.  If the port is 0, then dynamically allocate a
 * port and modify the original port variable to reflect the actual
 * port.
 * Parameters: pointer to variable containing the port to connect on
 * Returns: the socket */
/**********************************************************************/
int startup(u_short *port)
{
    int httpd = 0;
    int on = 1;
    struct sockaddr_in name;

    httpd = socket(AF_INET, SOCK_STREAM, 0);
    if (httpd == -1)
        error_die("socket");
    memset(&name, 0, sizeof(name));
    name.sin_family = AF_INET;
    name.sin_port   = htons(*port);
    name.sin_addr.s_addr = htonl(INADDR_ANY);
    if ((setsockopt(httpd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))) < 0)
        error_die("setsockopt - SO_REUSEADDR");
    if (bind(httpd, (struct sockaddr *) &name, sizeof(name)) < 0)
        error_die("bind");
    if (*port == 0) {
        socklen_t namelen = sizeof(name);
        if (getsockname(httpd, (struct sockaddr *) &name, &namelen) == -1)
            error_die("getsockname");
        *port = ntohs(name.sin_port);
    }
    if (listen(httpd, 5) < 0)
        error_die("listen");
    return httpd;
}

/**********************************************************************/
/* Give a client a 404 not found status message. */
/**********************************************************************/
void not_found(int client)
{
    char buf[1024];

    sprintf(buf, "HTTP/1.0 404 NOT FOUND\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, SERVER_STRING);
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "Content-Type: text/html\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "<HTML>\n"
                 "<HEAD>\n"
                 "  <TITLE>Not Found</TITLE>\n"
                 "</HEAD>\n"
                 "<BODY>\n"
                 "  <P>The server could not fulfill your request because the resource specified is unavailable or nonexistent.</P>\n"
                 "</BODY>\n"
                 "</HTML>\r\n");
    send(client, buf, strlen(buf), 0);
}

/**********************************************************************/
/* Inform the client that the requested web method has not been
 * implemented.
 * Parameter: the client socket */
/**********************************************************************/
void unimplemented(int client)
{
    char buf[1024];

    sprintf(buf, "HTTP/1.0 501 Method Not Implemented\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, SERVER_STRING);
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "Content-Type: text/html\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "<HTML>\n"
                 "<HEAD>\n"
                 "  <TITLE>Method Not Implemented</TITLE>\n"
                 "</HEAD>\n"
                 "<BODY>\n"
                 "  <P>HTTP request method not supported.</P>\n"
                 "</BODY>\n"
                 "</HTML>\r\n");
    send(client, buf, strlen(buf), 0);
}

/**********************************************************************/

int main(void)
{
    int server_sock = -1;
    u_short port = 4000;
    int client_sock = -1;
    struct sockaddr_in client_name;
    socklen_t client_name_len = sizeof(client_name);

    server_sock = startup(&port);
    printf("httpd running on port %d\n", port);

    while (1) {
        client_sock = accept(server_sock,
                (struct sockaddr *) &client_name,
                &client_name_len);
        if (client_sock == -1)
            error_die("accept");
        accept_request((intptr_t *)(long) client_sock);
    }

    close(server_sock);

    return 0;
}
