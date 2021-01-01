// Author : Muhammad Arose Niazi FA18_BSE_010

/*
  Includes
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

/*
  Working
*/

int main(int argc, char *argv[]) 
{
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char c;
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    if (argc < 2) {
        fprintf(stderr, "ERROR, no port provided\n");
        return 1;
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("ERROR opening socket");
        return 0;
    }  
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = portno; // htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("ERROR on binding");
        return 0;
    }
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
    int pid;
    while (1) 
    {
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0)
        {
            perror("ERROR on accept");
            exit(0);
        }
               
        pid = fork();
        if (pid < 0) {
            perror("ERROR in new process creation");
            exit(0);
        }
        if (pid == 0) 
	    {  
            /*
                Child Process
            */
            close(sockfd);


            FILE *myFile;
            char fileName[20];
            snprintf(fileName,20, "%d", getpid());
            strcat(fileName, ".txt");
            myFile = fopen (fileName, "w+");
            do
            {
                
                n = read(newsockfd, &c, 1);
                if (n < 0)
                {
                    perror("ERROR reading from socket");
                    exit(0);
                }
                printf("I got: %c from client\n", c);
                fprintf(myFile, "%c ", c);
                ++c;
                n = write(newsockfd, &c, 1);
                if (n < 0)
                {
                    perror("ERROR writing to socket");
                    exit(0);
                }

            } while (--c != 'Q');
            close(newsockfd);
            fclose (myFile);
	        return 0;
        } 
	    else       //parent process
            close(newsockfd);
    }
    return 0;
}

