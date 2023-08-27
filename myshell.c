#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <sys/stat.h>
#include<unistd.h>
#include<dirent.h>
#define ANSI_COLOR_BLUE "\x1b[1;34m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_GREEN "\x1b[1;32m"
void myCat(int argc,char* argv[]){
	FILE *f1;
	char* name;
	char ch;
	if(strcmp(argv[2],"-")==0){
		name=argv[3];
		f1=fopen(name,"w");
		if(f1==NULL){
			perror("error ");
			return ;
		}
		while((ch=getchar())!='.'){
			putc(ch,f1);
			}
		putc('\n',f1);
			fclose(f1);
	}
	else if(strcmp(argv[2],"--")==0){
		name=argv[3];
		f1=fopen(name,"a");
		if(f1==NULL){
			perror("error ");
			return;
			}
		while((ch=getchar())!='.'){
			putc(ch,f1);
		}
		putc('\n',f1);
		fclose(f1);
	}
	else if(strstr(argv[2],".txt")){
		struct stat st;
		name=argv[2];
		f1=fopen(name,"r");
		if(stat(argv[2],&st)!=0){
			perror("error");
			return;
		}
		while((ch=getc(f1))!=EOF)
		{
			printf("%c",ch);
		}
		fclose(f1);
	}
	else{
		printf("Incorrect syntax, Usage: <command> [args]");
	}

}

void myEcho(int argc,char* argv[]){
	if(argc<3){
		printf("Usage: %s <text to echo>\n",argv[1]);
		return;
	}
	for(int i=2;i<argc;i++){
		printf("%s ",argv[i]);
	}
	printf("\n");

}

void myLs(){
	DIR *dir;
	struct dirent *entry;

	dir=opendir(".");
	if(dir==NULL){
		perror("opendir error");
		return;
	}

	while((entry=readdir(dir))!=NULL){
	 if(entry->d_name[0]=='.')
		continue;
	 if(entry->d_type == DT_DIR){
	    printf(ANSI_COLOR_BLUE "%s" ANSI_COLOR_RESET "\n",entry->d_name);
	}
	 else{
	    struct stat fileStat;
	  if(stat(entry->d_name,&fileStat)==0 && fileStat.st_mode & S_IXUSR)
	  {
	    printf(ANSI_COLOR_GREEN "%s" ANSI_COLOR_RESET "\n",entry->d_name);
	  }
	  else{
	    printf("%s\n",entry->d_name);
	  }
	}
}
	printf("\n");
	closedir(dir);

}

void myPwd(){
	char cwd[1024];
	if(getcwd(cwd,sizeof(cwd))!=NULL){
		printf("Current working directory: %s\n",cwd);
	}
	else{
		perror("getcwd error");
	}
}

void print_tail(int num_lines,const char *filename){
	FILE *file=fopen(filename,"r");
	if(file==NULL){
		perror("fopen error");
		return;
	}

	char lines[num_lines][256];
	int line_count=0;
	int curr_line=0;
	while(fgets(lines[curr_line],sizeof(lines[curr_line]),file)){
		curr_line=(curr_line+1) % num_lines;
		line_count++;
	}

	int i;
	for(i=0;i<num_lines;i++){
		printf("%s",lines[curr_line]);
		curr_line=(curr_line+1) % num_lines;
	}
	fclose(file);
}

void print_head(int num_lines,const char *filename){
	FILE *file=fopen(filename,"r");
	if(file==NULL){
		perror("fopen error");
		return;
	}
	char line[256];
	int line_count=0;

	while(fgets(line,sizeof(line),file) && line_count < num_lines){
		printf("%s", line);
		line_count++;
	}
	fclose(file);
}


int main(int argc,char* argv[]){
	if(strcmp(argv[1],"cat")==0){
		myCat(argc,argv);
	}
	else if(strcmp(argv[1],"echo")==0){
		myEcho(argc,argv);
	}
	else if(strcmp(argv[1],"ls")==0){
		myLs();
	}
	else if(strcmp(argv[1],"pwd")==0){
		myPwd();
	}
	else if(strcmp(argv[1],"head")==0){
		if(argc<4){
			print_head(10,argv[2]);
		}
		else{
			print_head(atoi(argv[2]),argv[3]);
		}
	}
	else if(strcmp(argv[1],"tail")==0){
		if(argc<4){
			print_tail(10,argv[2]);
		}
		else{
			print_tail(atoi(argv[2]),argv[3]);
		}
	}
	return 0;
}
