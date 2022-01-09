#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#define size 100
int w=0;
void indx(int a,char* b)
{
    b[0] = a+'0';
    b[1]= ' ';
}
void append_to_index(int idx,int i,char* t,char *c)
{
    indx(i,t);
    write(idx,t,2);
    write(idx,c,5);
    write(idx,"\n",1);
}
void read_file(int fd_idx,int n)
{
    char buff[size];
    int reader = open("input.txt",O_RDONLY);
    char *c[n];
    for(int i=0;i<n;i++)
    {
        char t[3];
        c[i] = (char *) malloc(sizeof(char)*10); 
        c[i][0]='p';
        c[i][1]='a';
        c[i][2]='r';
        c[i][3]='t';
        c[i][4]='0'+i+1;
        c[i][5]='.';
        c[i][6]='t';
        c[i][7]='x';
        c[i][8]='t';
        c[i][9]='\0';
        int n_fd = open(c[i], O_CREAT| O_WRONLY | O_APPEND);
        chmod(c[i],0744);
        int j=0;
        while(j<size)
        {
            char l[1];
            read(reader,l,1);
            if(l[0]=='-')
            {
                buff[j]='\0';
                write(n_fd,buff,j);
                j=0;
                close(n_fd);
                break;
            }
            buff[j++]=l[0];
        }
        append_to_index(fd_idx,i,t,c[i]);
        w++;
    }
    close(reader);
}
void deletefile(char *a)
{
    FILE *v=fopen(a,"r");
    if(v!=NULL)
    {
        fclose(v);
        remove(a);
    }
    
}
void delete_part(int n)
{
    int i=0,idx=open("index.txt",O_RDONLY);
    while(i<n-1)
    {
        char c[1];
        read(idx,c,1);
        if(c[0]=='\n')
            i++;
    }
    char buff[9];
    read(idx,buff,2);
    read(idx,buff,5);
    buff[5]='.';
    buff[6]='t';
    buff[7]='x';
    buff[8]='t';
    buff[9]='\0';
    close(idx);
    deletefile(buff);
    int temp = open("temp.txt",O_CREAT| O_WRONLY | O_APPEND);
    chmod("temp.txt",0744);
    int rd = open("index.txt",O_RDONLY);
    char b[1];i=1;int k=1;
    while(i<=w)
    {
        read(rd,b,1);
        if(i!=n)
        write(temp,b,1);
        if(b[0]=='\n')
            i++;
    }
    close(temp);
    close(rd);
    remove("index.txt");
    rename("temp.txt","index.txt");
}
int main()
{
    
    while(1)
    {
    	printf("Enter your choice\n1.Store a file using indexed allocation\n2.Delete a segment\n3.Exit\n");
    	int x;
    	scanf("%d",&x);
    	if(x==1)
    	{
    		int idx=open("index.txt", O_CREAT| O_WRONLY | O_APPEND|O_TRUNC);
    		chmod("index.txt",0744);
    		printf("Enter the number of segments in the file\n");
    		int t;
    		scanf("%d",&t);
    		read_file(idx,t);
    		close(idx);
    	}
    	else if(x==2)
    	{
    		printf("Enter the segment number which has to be deleted!\n");
    		int a;
    		scanf("%d",&a);
    		delete_part(a);
    		printf("Segment deleted!\n");
    	}
    	else
    		break;
    }
}
