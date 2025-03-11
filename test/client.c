#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>

#define BUFFER_SIZE 4096
struct rule{
	char action[10];
	char protocol[10];
	char opt[5];
	char sip[20];
	char dip[20];
	//char dport[10];
	//char sport[10];
};
void none(){printf("15 none");}
/*
void none(int x,int y,int *fweb,char *xs,char *xd,char *ys,char *yd,char *xp,char *yp)
{	
	printf("15\nR%d & R%d anomaly : none\n",x,y);	
	//char a[1000];						//need re
	//int s=sprintf(a,"R%d & R%d anomaly : none<br>\n",x,y);	
	//fputs(a,fweb);
} */
void shadowed(int x,int y,int *fweb,char *xs,char *xd,char *ys,char *yd,char *xp,char *yp)
{
	printf("11\nR%d & R%d , : Shadowed\n",x,y);
	,,,,
	char a[150];
	int s=sprintf(a,"A_R%d,B_R%d,1,#a6cee3,Shadowed,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",x,y,xs,xd,xd,xs,xd,xd,ys,yd,yd,ys,yd,yd,xp,yp);
	fputs(a,fweb);

}
void redundant(int x,int y,int *fweb,char *xs,char *xd,char *ys,char *yd,char *xp,char *yp)
{
	printf("12\nR%d & R%d anomaly : Redundant\n",x,y);
	char a[150];
	int s=sprintf(a,"A_R%d,B_R%d,1,#b2df8a,Redundant,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",x,y,xs,xd,xd,xs,xd,xd,ys,yd,yd,ys,yd,yd,xp,yp);
	fputs(a,fweb);
	
}
void general(int x,int y,int *fweb,char *xs,char *xd,char *ys,char *yd,char *xp,char *yp)
{
	printf("13\nR%d & R%d anomaly : General\n",x,y);
	printf("\n\n%s%s%s%s%s%s\n\n",xs,xd,ys,yd,xp,yp);
	char a[150];
	int s=sprintf(a,"A_R%d,B_R%d,1,#f4c934,General,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",x,y,xs,xd,xd,xs,xd,xd,ys,yd,yd,ys,yd,yd,xp,yp);
	printf("%s",a);		
	fputs(a,fweb);
	
}
void correlated(int x,int y,int *fweb,char *xs,char *xd,char *ys,char *yd,char *xp,char *yp)
{
	printf("14\nR%d & R%d anomaly : Correlated\n",x,y);
	char a[150];
	int s=sprintf(a,"A_R%d,B_R%d,1,#fb9a99,Correlated,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",x,y,xs,xd,xd,xs,xd,xd,ys,yd,yd,ys,yd,yd,xp,yp);	
	fputs(a,fweb);
	
}




int c_protocol(char *str1,char *str2) //compare protocol
{
//printf("%s %s",str1,str2);
if(strcmp(str1,str2)==0) return 1;
else if(strcmp(str1,"all")==0) return 2;
else if(strcmp(str2,"all")==0) return 3;
else return 0;
}

int c_action(char *str1,char *str2) //compare action
{
printf("%s %s",str1,str2);
if(strcmp(str1,str2)==0) return 1;
else return 0;
}

int c_ip(char *str1,char *str2,int size) //compare ip address
{
	struct in_addr net, subnetmask;
	printf("%s %s\n\n",str1,str2);

	int x=0,y=0,m1=0,m2=0,a,b,c,d;
	char *ip1,*ip2,*mask1,*mask2;
	char szIP1[20]={},szIP2[20]={};
	char *delim = "/";
	ip1 = strtok(str1, delim);
	mask1 = strtok(NULL, "/");
	ip2 = strtok(str2, delim);
        mask2 = strtok(NULL, "/");
	printf("Ip1 : %s\tIp2 : %s\n",ip1,ip2);
	printf("mask1 : %s\tmask2 : %s\n",mask1,mask2);
	
	if(mask1==NULL&&mask2==NULL){
	for(int i=0;i<size;i++){
	if(str1[i]==str2[i]) {
	//printf("%c\n",str1[i]);
	if(str1[i]=='\0') 
	return 1;
	}
	//printf("%c %c\n",str1[i],str2[i]);
	else if(str1[i]=='*') return 2;	//r1 contain r2
	else if(str2[i]=='*') return 3; //r2 contain r1
	else return 0;	//none
	}	
	return 1; //r1 == r2
	}//str *

	else if(mask1==NULL){	
	x=atoi(mask2);
	y=3;}	//Maybe r2 contain r1
	//printf("min mask1 = %d\n",x);
	else if(mask2==NULL){
	x=atoi(mask1);
	y=2;}   //Maybe r1 contain r2     
	//printf("min mask2 = %d\n",x);
        else{
	m1=atoi(mask1);
	m2=atoi(mask2);
	if(m1<m2){
	x=m1;
	y=2;}
	else if(m1>m2){
	x=m2;
	y=3;}
	else{	//m1=m2
	x=m1;
	y=1;}
	}
	char *delim2 = ".";
	char *pch;
	pch = strtok(str1,delim2);
	a = atoi(pch);
	pch = strtok (NULL, delim2);
	b = atoi(pch);
	pch = strtok (NULL, delim2);
	c = atoi(pch);
	pch = strtok (NULL, delim2);
	d = atoi(pch);
		
	net.s_addr = a << 24 | b << 16 | c << 8 | d;
	subnetmask.s_addr = 0xffffffff;
	subnetmask.s_addr <<= (32-x);
	net.s_addr &= subnetmask.s_addr;
	net.s_addr = htonl(net.s_addr);
	strcpy(szIP1,inet_ntoa(net));
	//printf("R1 Network address: %s\n", szIP1);

        pch = strtok(str2,delim2);
        a = atoi(pch);
        pch = strtok (NULL, delim2);
        b = atoi(pch);
        pch = strtok (NULL, delim2);
        c = atoi(pch);
        pch = strtok (NULL, delim2);
        d = atoi(pch);

        net.s_addr = a << 24 | b << 16 | c << 8 | d;
        subnetmask.s_addr = 0xffffffff;
        subnetmask.s_addr <<= (32-x);
        net.s_addr &= subnetmask.s_addr;
        net.s_addr = htonl(net.s_addr);
        strcpy(szIP2,inet_ntoa(net));
        //printf("R2 Network address: %s\n", szIP2);
	
	//printf("%s %s\n",szIP1,szIP2);
	if(strcmp(szIP1,szIP2)==0)	return y; //y=retval
	else	return 0;	
}//end c_ip()

int main(int argc , char *argv[]){
    struct timeval timeout={4,0};

    int sockfd = 0;
    sockfd = socket(AF_INET , SOCK_STREAM , 0);
    if (sockfd == -1){
        printf("Fail to create a socket.");
    }
    if((setsockopt(sockfd,SOL_SOCKET,SO_RCVTIMEO,(char*)&timeout,sizeof(struct timeval)))==-1){
        printf("Fail to create a socket.");
    }
	
    struct sockaddr_in client_addr;
    bzero(&client_addr,sizeof(client_addr));
    client_addr.sin_family = PF_INET;
    
    FILE *fa;
	fa = fopen("getip.txt","r");
	char buffer1[100],*getip,*getport;
	fgets(buffer1,100,fa);
	getip=strtok(buffer1,":");
	getport=strtok(NULL,":");
	printf("%s\n\n%s\n\n",getip,getport);
    fclose(fa);
    int po;
    if(getport==NULL) po=111111;
    else po=atoi(getport);

    client_addr.sin_addr.s_addr =inet_addr(getip);
    client_addr.sin_port = htons(po);

    FILE *faa;
    faa = fopen("ifcon.txt","w");
    char ifconnum[1];
    int err = connect(sockfd,(struct sockaddr *)&client_addr,sizeof(client_addr));
    if(err==0){
	int s=sprintf(ifconnum,"0");
   	fputs(ifconnum,faa);
	}
    else{
        printf("Connection error\N");
	int s=sprintf(ifconnum,"1");
   	fputs(ifconnum,faa);
    	
	//printf("%s\n\n%s\n\n",getip,getport);
	//char* const arg1 = strdup("python");
        //char* const arg2 = strdup("err.py");
        //char* const arg[3] = {arg1,arg2,NULL};
        //execvp(arg[0],arg);
    }
	
    fclose(faa);

    char *buf;
    buf=(char *)malloc(BUFFER_SIZE);
    
	recv(sockfd,buf,BUFFER_SIZE,0);
	printf("Get from the router:\n%s\n\n",buf);
	
	FILE *fb;
	fb=fopen("rule.txt","w");
	//fwrite(buf,1,BUFFER_SIZE,fp);
	fprintf(fb,"%s",buf);
	fclose(fb);

    free(buf);
    close(sockfd);


	FILE *fr,*fp;
	fr = fopen("rule.txt","r");	
	char buffer[100],*str;
       	int z=0,c=0;	//z=how much rule
	while (fgets(buffer,100,fr)){z=z+1;} 
	printf("%d\n",z);
	fclose(fr);	
	
	struct rule r[z]; 

	fp = fopen("rule.txt","r");
        while (fgets(buffer,100,fp)){	//read one line
		//printf("%s",buffer);

		str=strtok(buffer," ");
            	strcpy(r[c].action,str);
		
            	str=strtok(NULL," ");
            	strcpy(r[c].protocol,str);

		str=strtok(NULL," ");
           	strcpy(r[c].opt,str);

            	str=strtok(NULL," ");
            	strcpy(r[c].sip,str);
                
            	str=strtok(NULL," ");
            	strcpy(r[c].dip,str);
         	      
          	c++;
		}
          
        fclose(fp);


	FILE *fweb;
	fweb = fopen("anomaly.txt","w");
	
	int x,y;
        for(x=0;x<z;x++){
	for(y=x+1;y<z;y++){
	//printf("%d %d %d\n\n",x,y,z);
	
	char rxs[20],rys[20],rxd[20],ryd[20],rxp[10],ryp[10];
	char rxsc[20],rysc[20],rxdc[20],rydc[20];
	strcpy(rxs,r[x].sip);
	strcpy(rys,r[y].sip);
	strcpy(rxd,r[x].dip);	
	strcpy(ryd,r[y].dip);

	strcpy(rxsc,rxs);
	strcpy(rysc,rys);
	strcpy(rxdc,rxd);	
	strcpy(rydc,ryd);

	strcpy(rxp,r[x].protocol);
	strcpy(ryp,r[y].protocol);
	//printf("\n\n\n\n\n%s%s%s%s%s%s\n\n\n",rxs,rxd,rys,ryd,rxp,ryp);
	int sip=c_ip(rxsc,rysc,sizeof(r[x].sip)); //sip retval 
	int dip=c_ip(rxdc,rydc,sizeof(r[x].dip)); //dip retval
	
	//printf("Compare rule[%d] and rule[%d]\nFSM path:0-",x,y);
	printf("FSM path:0-");
	switch(c_protocol(rxp,ryp)){
	case 0:
        none();
	break;

        case 1:	//0-1
        printf("1-");
		switch(sip){
		case 1: //1-4
                printf("4-");	
			switch(dip){

			case 1: //4-8
			case 2:
			printf("8-");
			if(c_action(r[x].action,r[y].action)==0)
			shadowed(x,y,fweb,rxs,rxd,rys,ryd,rxp,ryp);
			else if(c_action(r[x].action,r[y].action)==1)
			redundant(x,y,fweb,rxs,rxd,rys,ryd,rxp,ryp);
			else
			printf("Error p8\n");
			break;

			case 3: //4-6
			printf("6-");			
				switch(dip){
				
				case 1: //6-9
				case 3:
				printf("9-");
                        	if(c_action(r[x].action,r[y].action)==0)
                        	general(x,y,fweb,rxs,rxd,rys,ryd,rxp,ryp);
                      		else if(c_action(r[x].action,r[y].action)==1)
                        	redundant(x,y,fweb,rxs,rxd,rys,ryd,rxp,ryp);
                	        else
        	                printf("Error p9\n");
	                        break;

				case 2://6-7
				printf("7-");
					switch (dip){
					
					case 1:					
					case 2:
					case 3:
					printf("10-");
					if(c_action(r[x].action,r[y].action)==0)
					correlated(x,y,fweb,rxs,rxd,rys,ryd,rxp,ryp);
					else
					none();
					break;					
					
					case 0:
					none();
					break;

					default:
					printf("Error p7\n");
					break;}
				break;

				case 0://6-15
				none();
				break;

				default:
				printf("Error p6\n");
				break;
				}
			break;
			
			case 0: //4-15
			none();
			break;

			default:
                        printf("Error p4\n");
                        break;
			}
                break;
		case 2: //1-5
	        printf("5-");
			switch(dip){
			
                        case 1: //5-8
                        case 2:
			printf("8-");
                        if(c_action(r[x].action,r[y].action)==0)
                        shadowed(x,y,fweb,rxs,rxd,rys,ryd,rxp,ryp);
                        else if(c_action(r[x].action,r[y].action)==1)
                        redundant(x,y,fweb,rxs,rxd,rys,ryd,rxp,ryp);
                        else
                        printf("Error p8\n");
                        break;

                        case 3: //5-7
			printf("7-");
                        //printf("%s %s\n",r1.dip,r2.dip);
				switch(dip){
				
				case 1:					
				case 2:
				case 3:
                                printf("10-");
                                if(c_action(r[x].action,r[y].action)==0)
                                correlated(x,y,fweb,rxs,rxd,rys,ryd,rxp,ryp);
                                else
                                none();
                                break;
	 
                                case 0:   
				none();
                                break;
	
				default:
                                printf("Error p7\n");
				break;}
			break;

			case 0://5-15
			none();
			break;

			default:
			printf("Error p5\n");
			break;
			}
        	break;


        	case 3: //1-6
        	printf("6-");
			switch(dip){

                                case 1: //6-9
				case 3:                                
				printf("9-");
                                if(c_action(r[x].action,r[y].action)==0)
                                general(x,y,fweb,rxs,rxd,rys,ryd,rxp,ryp);
                                else if(c_action(r[x].action,r[y].action)==1)
                                redundant(x,y,fweb,rxs,rxd,rys,ryd,rxp,ryp);
                                else
                                printf("Error p9\n");
                                break;

                                case 2://6-7
                                printf("7-");
                                switch (dip){
					
					case 1:					
					case 2:
					case 3:
                                        printf("10-");
                                        if(c_action(r[x].action,r[y].action)==0)
                                        correlated(x,y,fweb,rxs,rxd,rys,ryd,rxp,ryp);
                                        else
                                        none();
					break;
                                        
                                        case 0:
                                        none();
					break;

                                        default:
                                        printf("Error p7\n");
					break;}
                                break;

                                case 0://6-15
                                none();
                                break;

				default:
				printf("Error p6\n");
        			break;
				}
		break;
		
		case 0://1-15
		none();
		break;

        	default:
        	printf("Error p1\n");
        	break;
		}
	break;
       	
	case 2: //0-2
	printf("2-");
		switch(sip){

                        case 1: //2-5
			case 2:                        
			printf("5-");
                        	switch(dip){

        	                case 1: //5-8
				case 2:	                        
				printf("8-");
                	        if(c_action(r[x].action,r[y].action)==0)
                	        shadowed(x,y,fweb,rxs,rxd,rys,ryd,rxp,ryp);
                        	else if(c_action(r[x].action,r[y].action)==1)
                        	redundant(x,y,fweb,rxs,rxd,rys,ryd,rxp,ryp);
                        	else
                        	printf("Error p8\n");
                       		break;

                        	case 3: //5-7
                        	printf("7-");
                        	switch (dip){
					
					case 1:					
					case 2:
					case 3:
                                        printf("10-");
                                        if(c_action(r[x].action,r[y].action)==0)
                                        correlated(x,y,fweb,rxs,rxd,rys,ryd,rxp,ryp);
                                        else
                                        none();
                                        break;
	
                                        case 0:
                                        none();
					break;

                                        default:
                                        printf("Error p7\n");
					break;}
				break;
	
        	                case 0://5-15
                	        none();
                        	break;
				
				default:
				printf("Error p5\n");
				break;
				}
                        break;

                        case 3: //2-7
                        printf("7-");
			switch (dip){
					case 1:					
					case 2:
					case 3:
                                        printf("10-");
                                        if(c_action(r[x].action,r[y].action)==0)
                                        correlated(x,y,fweb,rxs,rxd,rys,ryd,rxp,ryp);
                                        else
                                        none();
                                        break;
	
                                        case 0:
                                        none();
                                        break;

					default:
                                        printf("Error p7\n");
					break;}
                        break;

                        case 0: //2-15
                        none();
                        break;

                        default:
                        printf("Error p2\n");
			break;
		}
	break;

	case 3://0-3
	printf("3-");
		switch(sip){

                case 1: //3-6
		case 3:
		printf("6-");
			switch(dip){

                                case 1: //6-9
				case 3:                                
				printf("9-");
                                if(c_action(r[x].action,r[y].action)==0)
                                general(x,y,fweb,rxs,rxd,rys,ryd,rxp,ryp);
                                else if(c_action(r[x].action,r[y].action)==1)
                                redundant(x,y,fweb,rxs,rxd,rys,ryd,rxp,ryp);
                                else
                                printf("Error p9\n");
                                break;

                                case 2://6-7
                                printf("7-");
                                switch (dip){
					
					case 1:					
					case 2:
					case 3:
                                        printf("10-");
                                        if(c_action(r[x].action,r[y].action)==0)
                                        correlated(x,y,fweb,rxs,rxd,rys,ryd,rxp,ryp);
                                        else
                                        none();
                                        break;

                                        case 0:
                                        none();
					break;

                                        default:
                                        printf("Error p7\n");
					break;}
                                break;

                                case 0://6-15
                                none();
                                break;
				
				default:
				printf("Error p6\n");
				break;	
				}

		break;

		case 2://3-7
		printf("7-");
		switch (dip){
					
			case 1:					
			case 2:
			case 3:
                	printf("10-");
                        if(c_action(r[x].action,r[y].action)==0)
                        correlated(x,y,fweb,rxs,rxd,rys,ryd,rxp,ryp);
                        else
                        none();
                        break;

                        case 0:
                        none();
			break;

                        default:
                        printf("Error p7\n");
			break;}
		break;

		case 0://3-15
		none();
		break;

		default:
		printf("Error p3\n");
		break;
		}
	break;
	
	default:
       	printf("Error!\n");
	break;
	}
printf("\n");
}//end for(y)
}//end for(x)
fclose(fweb);

return 0;}//end main
