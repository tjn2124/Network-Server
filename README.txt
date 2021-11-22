
Network Server 

mdb-lookup-server-nc-2.c promps the user for a valid port number 
and fork/execls into script mdb-lookup-server-nc.sh. It displays a 
message that an instance of the mdb-lookup-server has started as 
a network server with the child process' id and port number that 
the process was started on. If a process is terminated the program
displays a prompt with which program has terminated. 

mdb-lookup-server-nc.sh is a shell script that creates a named pipe
and then the netcat (nc) program turns the c program mdb-lookup-cs3157
into a network server using nc from CLAC. The named pipe is removed 
at the end of the script and when ever a process is terminated from 
the client. 

mdb-lookup-server-nc-1.c executs the shell script as a new process 
and exits when the program is done. 




