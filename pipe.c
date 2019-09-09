void pipe_handle(char* args[])
{
	int end=0;
	int i=0,j=0,k=0,l=0;
	int dest1[2];
	int dest2[2];
	char* command[100];
	pid_t pid;
int no_of_cmds=0;
while(args[l]!=NULL)
{
	if(strcmp(args[l],"|")==0)
	{
		++no_of_cmds;
	}
	++l;
}
++no_of_cmds;

while(args[j]!=NULL&& end!=1)
{
	while(strcmp(args[j],"|")!=0)
	{
		command[k]=args[j];
		++j;
		if(args[j]==NULL){
			++k;
			end=1;
			break;
		}
		++k; }
		command[k]=NULL;
		++j;
		int m=i%2;
		if(m!=0){
			pipe(dest1);
		}
		else{
pipe(dest2);
		}
		pid=fork();
		if(pid==-1){
			if(i!=no_of_cmds-1)
			{
				if(m%2!=0)
				{
					close(dest1[1]);
				}
				else{
					close(dest2[1]);
				}

			}
			printf("child not created\n");
			return;
		}
		if(pid==0)
		{
			if(i==0)
			{
			dup2(dest2[1],STDOUT_FILENO);	
			}
			else if(i==no_of_cmds-1)
			{
				if(no_of_cmds%2!=0)
				{
					dup2(dest1[0],STDIN_FILENO);
				}
				else
				{
					dup2(dest2[0],STDIN_FILENO);
				}
			}
			else
			{
			if(i%2!=0)
			{
				dup2(dest2[0],STDIN_FILENO);
				dup2(dest1[1],STDOUT_FILENO);

			}	
			else
			{
				dup2(dest1[0],STDIN_FILENO);
				dup2(dest2[0],STDOUT_FILENO);
			}

			}
			if(execvp(command[0],command)==-1)
			{
				kill(getpid(),SIGTERM);
			}
			}
			if(i==0)
			{
				close(dest2[1]);
			}
else if (i == no_of_cmds- 1)
{
			if (no_of_cmds % 2 != 0){					
				close(dest1[0]);
			}else
			{					
				close(dest2[0]);
			}
		}else
		{
			if (i % 2 != 0){					
				close(dest2[0]);
				close(dest1[1]);
			}
			else{					
				close(dest1[0]);
				close(dest2[1]);
			}
		}
waitpid(pid,NULL,0);
++i;
}
}
