/* include libraries */
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

int main (int argc, char *argv[])
{
   puts("TCP Client program by Bennett Moore");
   
   // Check number of arguments
   if (argc != 3)
   {
      printf("Usage: %s <server> <port>\n", argv[0]);
      exit(1);
   }

   char *servername = argv[1];
   char *port = argv[2];
   
   // Validate input
   if (strnlen(servername, 254) > 253 || strnlen(port, 6) > 5)
   {
   	puts("Servername or port is too long. Please try again.");
   	exit(-1);
   }
   
   // Print out given server/port info
   printf("Servername= %s, port= %s\n", servername, port);
   
   // Create socket
   int sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd < 0)
   {
   	perror("ERROR: could not open socket");
   	exit(sockfd);
   }
   puts("A socket is opened!");
   
   // Get address info
   struct addrinfo hints, *serveraddr;
   memset(&hints, 0, sizeof(hints));
   hints.ai_family = AF_INET;
   hints.ai_socktype = SOCK_STREAM;
   int addr_lookup = getaddrinfo(servername, port, &hints, &serveraddr);
   if (addr_lookup != 0)
   {
      fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(addr_lookup));
      exit(addr_lookup);
   }

   // Connect to server
   int connected = connect(sockfd, serveraddr->ai_addr, serveraddr->ai_addrlen);
   if (connected < 0)
   {
      perror("ERROR: cannot connect to server");
      exit(connected);
   }
   else
   {
      printf("Connected to server %s at port %s\n", servername, port);
   }
   freeaddrinfo(serveraddr);

   const int BUFFERSIZE = 1024;
   char buffer[BUFFERSIZE];
   bzero(buffer, BUFFERSIZE);
   printf("Enter your message to send: ");
   fgets(buffer, BUFFERSIZE, stdin);
   int bytes_sent = send(sockfd, buffer, strlen(buffer), 0);
   bzero(buffer, BUFFERSIZE);
   int bytes_received = recv(sockfd, buffer, BUFFERSIZE, 0);
   if (bytes_received < 0)
   {
      perror("Error reading from server");
      exit(bytes_received);
   }
   printf("Received from server: %s", buffer);
   close(sockfd);
   return 0;
}
