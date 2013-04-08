/*
 * udpserver.c
 *
 *  Created on: 03-Apr-2013
 *      Author: aswin
 */

#include "main_declarations.h"
#include "uea2.h"
#include "pdcp.h"
#include "rlc.h"

#define TRACEPOINT_DEFINE
#include "lte_component_provider.h"

/*
void *threadFunc(void *arg)
{
	char *str;
	int i = 0;
void *threadFunc(void *arg)
{
	char *str;
	int i = 0;

	str=(char*)arg;

	while(i < 110 )
	{
		usleep(1);
		printf("threadFunc says: %s\n",str);
		++i;
	}

	return NULL;/*

	str=(char*)arg;

	while(i < 110 )
	{
		usleep(1);
		printf("threadFunc says: %s\n",str);
		++i;
	}

	return NULL;
}

*/

/*
 * Initialization function that is used to select a seed for
 * randomization
 */

void InitProcess()
{
	srand(time(NULL)); // Choose a randomization seed from the time
}

/*
 * Function that selects the number of users randomly
 * Returns the number of users
 */

int InitUsers()
{
	return (rand () % MAX_USER + 1);
}

/*
 * This function assigns a random number of packets to each of the
 * users and this information is stored in the
 * appropriate array
 */

AssignPackets(int **NoOfPackets,int NoOfUsers,int *TotalPackets)
{
	int i;

	for(i=0;i<NoOfUsers;i++)
    {
		  (*NoOfPackets)[i] = rand () % MAX_PACKET + 1;
		  (*TotalPackets) += (*NoOfPackets)[i];
    }

}

/*
 * This function is invoked every time a packet is
 * received. Once the packet is received, its contents
 * are read to determine the type and size of packet
 * and this information is then entered into the
 * appropriate packet structure.
 */

void ReceivePackets(int **NoOfPackets,char * buff,int i,int *j,int k, struct packet_format *packets)
{
	(*NoOfPackets)[i]--;
	(*j)++;
	char charrep[3];
        packets[k-1].userid = i+1;
	packets[k-1].payload = (char*) malloc (PACKET_SIZE);
	if(strcmp(buff,"payload")==0)
		{
		packets[k-1].type_of_data= 0;
	    	sprintf(charrep,"%d",i+1);
	    	strcat(buff,charrep);
		}
	else
		packets[k-1].type_of_data= 1;

	//packets[k-1].type_of_data= rand () % MAX_PACKET_TYPES;

	strcpy(packets[k-1].payload,buff);
	gettimeofday(&tv, NULL);
	packets[k-1].tt=tv;
    packets[k-1].size = strlen(buff);
}


/*
void ExecThread()
{
	    pthread_t pth;	// this is our thread identifier
		int i = 0;

		pthread_create(&pth,NULL,threadFunc,"foo");

		while(i < 100)
		{
			usleep(1);
			printf("ExecThread is running...\n");
			++i;
		}

		printf("ExecThread waiting for thread to terminate...\n");
		pthread_join(pth,NULL);

}
*/

/*
 * The main function, which contains the declarations for
 * the socket descriptor. It is responsible for receiving
 * packets from iperf and calls appropriate functions
 * after receiving packets. It has the functionality
 * required for scheduling and later calls the pdcp and the
 * rlc functions. Printing of the data at various stages
 * is another part of the main function.
 */

int main(int argc,char **argv)
{
	int sockfd,n,len;
    int NoOfUsers,*NoOfPackets,TotalPackets=0,i,j,k = 1;

    struct sockaddr_in servaddr, cliaddr;

    char *buff = (char*)malloc (PACKET_SIZE);
    //void * buff;

    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=htons(INADDR_ANY);
    servaddr.sin_port=htons(7734);
    bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    len=sizeof(cliaddr);


    InitProcess();

    NoOfUsers = InitUsers();

    printf("No. of Users - %d", NoOfUsers);
    //cout<<endl<<NoOfUsers;

    NoOfPackets = (int *)malloc(sizeof(int)*NoOfUsers); // Array to hold the number of packets for each user

    AssignPackets(&NoOfPackets,NoOfUsers,&TotalPackets);

    printf("\nTotal No. of packets = %d", TotalPackets);
    //cout<<endl<<"Total No. of packets = "<<TotalPackets;

    struct packet_format packets[TotalPackets];

    printf("\nPacket allocation for each user:\n");

    for(i=0;i<NoOfUsers;i++)
	printf("\n%d - %d\n", i+1, NoOfPackets[i]);
	//cout<<endl<<i+1<<" - "<<NoOfPackets[i]<<endl;

    printf("\n---Listening for packets from iPerf---\n");

    for(i=0,j=0;j<TotalPackets;i=(i+1)%NoOfUsers)
    {


		recvfrom(sockfd,buff,sizeof(struct client_hdr),0,(struct sockaddr*)&cliaddr,&len);
		if(NoOfPackets[i]==0)
				continue;
		else
		{
			ReceivePackets(&NoOfPackets,buff,i,&j,k,packets);
			printf("\n%d. %s -- size = %d",k++,buff,strlen(buff));
			tracepoint(lte_component, udp_packet, "MAC Scheduler", k-1, buff, strlen(buff));
			//k++; //If you un-comment the previous line, comment this line out!
		}

		sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&cliaddr,len); // Acknowledgment to the packet generator
    }
	    //sleep(10);

	/*    printf("\n\n\n*************************************");
	    printf("\nPrinting contents of all the packets\n*************************************\n\n \tUser ID\tPayload\t      Type\t Time (microsecond)\t Size");

	 for(i=0;i<TotalPackets;i++)
	    printf("\n\t%d     \t%s   \t%d \t %ld \t%d ", packets[i].userid, packets[i].payload, packets[i].type_of_data, packets[i].tt.tv_usec,packets[i].size);

	*/

	//printf("\n %d packets received. Now going into PDCP", TotalPackets);

    struct packet_arg packet_a;
    packet_a.packets = packets;
    packet_a.TotalPackets = TotalPackets;
    pthread_t pth;	// this is our thread identifier
    //pdcp(&packet_a);

    pthread_create(&pth,NULL,pdcp,&packet_a);

    //sleep(5);

    pthread_join(pth,NULL);

    printf("\n\n*************************************");
    printf("\nPrinting contents of all the packets\n*************************************\n\n \tUser ID\tPayload\t      Type\t Encrypted Data");
    for(i=0;i<TotalPackets;i++)
	printf("\n\t%d     \t%s   \t%d \t %s ", packets[i].userid, packets[i].payload, packets[i].type_of_data, packets[i].encrypted_data);

    //rlc(&packet_a);

    pthread_create(&pth,NULL,rlc,&packet_a);

    //sleep(5);

    pthread_join(pth,NULL);

    close(sockfd);

    //ExecThread();

    printf("\n");
    return 0;
}


