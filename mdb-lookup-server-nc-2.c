
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
static void die(const char *s)
{
    perror(s);
    exit(1);
}
int main(int argc, char **argv)
{
    if (argc > 1) {
        exit(1);
    }
    char buff[6];
    printf("port number: ");

    //continue reading in port numbers from user until user exits with Ctrl^c
    while((fgets(buff, sizeof(buff), stdin))!= NULL){

	    //wait for any child process and return if no child has 
	    //exited
	    pid_t pid = waitpid( (pid_t) -1, NULL, WNOHANG);
	    if (pid > 0 ){
		    fprintf(stderr, "[pid=%d] ", (int)pid);
		    fprintf(stderr, "mdb-lookup-server terminated\n");
		    }

	    //if the user didn't enter valid port number 
	    //prompt them again
	    if(strlen(buff)<3 ){
		    printf("port number: ");
	    }

	    //remove newline from port number
	    size_t last = strlen(buff) - 1;
	    if (buff[last] == '\n'){
		    buff[last] = '\0';
	    }
	    
	    //fork and alert user of port number the process started with
	    //execl into another instance of the mdb-lookup shell script
	    else{
		    pid = fork();

		    if (pid < 0) {
		   	 die("fork failed");
		    }
		    else if (pid == 0){
		    //child process
		   	fprintf(stderr, "[pid=%d] ",(int)getpid());
		    	fprintf(stderr, "mdb-lookup-server started on port %s\n", buff);
		    	execl("./mdb-lookup-server-nc.sh", "mdb-lookup-server-nc.sh",buff, (char *)0);
			die("execl failed");
		    } 
		    //parent process
	    	     else if (pid < 0){
			     die("waitpid failed");
			    
			}
	    }
    
    }
    return 0;
}