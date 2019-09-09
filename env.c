int envmanage(char * args[], int n){
	char **env_a;
	
	switch(n)
	{
		
		case 0: 
			for(env_a = environ; *env_a != 0; env_a ++)
			{
				printf("%s\n", *env_a);
			}
			break;
		
		case 1: 
			if((args[1] == NULL) && args[2] == NULL)
			{
				printf("%s","Not enought input arguments\n");
				return -1;
			}
			
	
			if(getenv(args[1]) != NULL)
			{
				printf("%s", "The variable has been overwritten\n");
			}
			else
			{
				printf("%s", "The variable has been created\n");
			}
			
		
			if (args[2] == NULL)
			{
				setenv(args[1], "", 1);
			
			}
			else
			{
				setenv(args[1], args[2], 1);
			}
			break;
		
		case 2:
			if(args[1] == NULL)
			{
				printf("%s","Not enought input arguments\n");
				return -1;
			}
			if(getenv(args[1]) != NULL)
			{
				unsetenv(args[1]);
				printf("%s", "The variable has been erased\n");
			}
			else
			{
				printf("%s", "The variable does not exist\n");
			}
		break;
			
			
	}
	return 0;
}
