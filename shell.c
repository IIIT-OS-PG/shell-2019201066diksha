#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<termios.h>
#include<sys/wait.h>
#include<signal.h>
#include "util.h"
#include "init.c"
#include "env.c"
//#include "remove.c"
#include "pipe.c"

#define max 1000
#define lim 100


void process(char **args,int bg)
{
	
	pid=fork();
	if(pid==-1)
	{
		printf("child process cant be created\n");
		return;
	}
	if(pid==0)
	{
		signal(SIGINT ,SIG_IGN);

	}
	setenv("parent",getcwd(currentDirectory,1000),1);
	if(execvp(args[0],args)==-1)
	{
		printf("cmd not found");
		kill(getpid(),SIGTERM);
	}
	if(bg==0)
	{
		waitpid(pid,NULL,0);
	}
	else
	{
		printf("process created with pid %d",pid);
	}

}

void directorychange(char* args[])
{

if(args[1] == "~")
{
    chdir(getenv("./"));
  }
  else 
{
    if(chdir(args[1])==-1){
      printf("This doesn't even exist \n");
    }
  }
}


void fileIO(char * args[], char* inputfile, char* outputfile, int n)
{
	 pid=fork();
	
	
	int fileDescriptor; 
	
	if(pid==-1)
	{
		printf("Child process could not be created\n");
		return;
	}
	if(pid==0){
		
		if (n == 0){

			fileDescriptor = open(outputfile, O_CREAT | O_TRUNC | O_WRONLY, 0600); 
			
			dup2(fileDescriptor, STDOUT_FILENO); 
			close(fileDescriptor);
		
		}
		else if (n == 1)
		{
			
			fileDescriptor = open(inputfile, O_RDONLY, 0600);  
		
			dup2(fileDescriptor, STDIN_FILENO);
			close(fileDescriptor);

			fileDescriptor = open(outputfile, O_CREAT | O_TRUNC | O_WRONLY, 0600);
			dup2(fileDescriptor, STDOUT_FILENO);
			close(fileDescriptor);		 
		}
		 
		setenv("parent",getcwd(currentDirectory, 1024),1);
		
		if (execvp(args[0],args)==-1){
			
			printf("error");
			kill(getpid(),SIGTERM);
		}		 
	}
	waitpid(pid,NULL,0);
}


int input_command(char* args[])
{
	char* args_a[200];
	int k=0,l=0;
	int fileDescriptor;
	int a;
	int bg=0;
	int standardOut;
	while(args[k]!=NULL)
	{
		if((strcmp(args[k],">")==0) || (strcmp(args[k],"<")==0) || (strcmp(args[k],"&")==0))
{
	break;
	}
	args_a[k]=args[k];
	++k;
}
if(strcmp(args[0],"cd")==0)
	directorychange(args);
else if(strcmp(args[0],"exit")==0)
	exit(0);
else if(strcmp(args[0],"pwd")==0)
{
	if(args[k]!=NULL){
		if((strcmp(args[k],">")==0)&&(args[k+1]!=NULL))
		{
			fileDescriptor= open(args[k+1],O_CREAT|O_TRUNC|O_WRONLY,0600);
			standardOut=dup(STDOUT_FILENO);
		dup2(fileDescriptor,STDOUT_FILENO);
		close(fileDescriptor);
		printf("%s\n",getcwd(currentDirectory,1000));
		dup2(standardOut,STDOUT_FILENO);
	}
	}
	else
	{
		printf("%s\n",getcwd(currentDirectory,1000));
	}
}
else if(strcmp(args[0],"clear")==0)
system("clear");

else
{
	while(args[l]!=NULL && bg== 0)
{
	if(strcmp(args[l],"&")==0)
{
	bg=1;
}
else if(strcmp(args[l],"|")==0)
{
	pipe_handle(args);
	return 1;
}
else if(strcmp(args[l],"<")==0)
{
a=l+1;
if(args[a]==NULL|| args[a+1]==NULL|| args[a+2]==NULL)
{
	printf("not sufficient arg\n");
	return -1;
}	
else
{
	if(strcmp(args[a+1],">")!=0)
	{
		printf("expected '>' and find %s\n",args[a+1]);
		return -2;
	}
}
fileIO(args_a,args[l+1],args[l+3],1);
return 1;
}
else if(strcmp(args[l],">")==0)
{
	if(args[l+1]==NULL)
	{
		printf("not enough ip args\n");
		return -1;
	}
fileIO(args_a,NULL,args[l+1],0);
return 1;
}
++l;

}

args_a[l]=NULL;	
process(args_a,bg);
}
return 1;
}

void shellPrompt()
{
	
	char hostn[1000] = "";
	gethostname(hostn, sizeof(hostn));
	printf("%s@%s %s >$ ", getenv("LOGNAME"), hostn, getcwd(currentDirectory, 1000));
}




void main(int argc,char* args[])
{
	float noprint=0;
char line[max];
int tokensnum=0;
char *tok[lim];
pid=-20;
init();

printf("---------------------\n");
printf("-----SHELL-------------\n");
printf("------------------------\n");


while(1)
{
	if(noprint==0)
		shellPrompt();
	
noprint=0;
	
memset(line,'\0',max);
	fgets(line,max,stdin);
	if((tok[0]=strtok(line,"\n\t"))==NULL)
		continue;
	tokensnum=1;
while((tok[tokensnum]=strtok(NULL,"\n\t"))!=NULL)
	tokensnum++;
input_command(tok);
}
exit(0);
}
