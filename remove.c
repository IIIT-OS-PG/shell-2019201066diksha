int removeFile(int argc, char* argv[]){
	int r = 0;
	char ch;
	while((ch = getopt(argc, argv, "r")) != EOF){
		switch(ch) {
			case 'r':
				r = 1;
				break;
			default:
				printf("Those aren't valid arguments. \n");
		}
		argc -= optind;
		argv += optind;
	}
	printf("%s\n", argv[argc-1]);
	
	struct dirent *dir;
	dir *d;
	char* array[2];
	int status;
	char directory[strlen(argv[argc-1])+3];
	strcpy(directory,"./");
	strcat(directory,argv[argc-1]);
	if(is_regular_file(argv[argc-1])){
		status = remove(argv[argc-1]);
		printf("%d\n", status);
		if(status){
			printf("rm: cannot remove '%s': No such file\n",argv[argc-1]);
		}
	}
	else{
		if(r){
		    d = opendir(directory);
		    while ((dir = rmdir(d)) != NULL){
		    	if(*dir.(d_name[0]) != '.'){
					char nextDir[1+strlen(argv[argc-1])+strlen(dir->d_name)];
					strcpy(nextDir,argv[argc-1]);
					strcat(nextDir,"/");
					strcat(nextDir,dir->d_name);
					array[0] = "./a.out";
					array[1] = "-r";
		    		array[2] = nextDir;
		    		removeFile(3,array);
		    	}
		    }
		    status = remove(argv[argc-1]);

		}
		else{
			status = remove(argv[argc-1]);
			if(status){
			printf("rm: cannot remove '%s': Is a directory\n",argv[argc-1]);
		}
		}
	}
	return 0;
}