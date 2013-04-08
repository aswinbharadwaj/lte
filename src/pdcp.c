/*
 * pdcp.c
 *
 *  Created on: 03-Apr-2013
 *      Author: aswin
 */
#include "main_declarations.h"
#include "uea2.h"
#include "pdcp.h"

#include "lte_component_provider.h"

/*
 * This is the pdcp function which receives as input a packet
 * and the total number of packets together
 * in a structure. It decomposes them and uses them
 * individually to apply the encryption algorithm
 * for each packet that was received in the program.
 * The encryption used is Snow3g algorithm.
 */

void *pdcp(struct packet_arg *packet_a)
{


	//printf("\n\n********** PDCP **********\n\n");

	/*
	int i;
	for(i=0;i<TotalPackets;i++)
	    printf("\n\t%d     \t%s   \t%d \t %ld \t%d ", packets[i].userid, packets[i].payload, packets[i].type_of_data, packets[i].tt.tv_usec,packets[i].size);
	*/
	struct packet_format *packets = (*packet_a).packets;
	int TotalPackets = (*packet_a).TotalPackets;

	bearer_type bearer = t1;
	direction dir = downlink;
	u8 key[16] = {0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,0x70};

	int i, content_size, ind, content_index, kk=0, first, second, third, fourth;
	char content[PDCP_SIZE], ascii_content[2*PDCP_SIZE], pdcp_data[ENCRYPT_SIZE], some_var[2];
	char * final= (char)malloc(ENCRYPTED_SIZE);

	for(i=0;i<TotalPackets;i++)
	{
		strcpy(content, packets[i].payload);
		//printf("\nCONTENT - %s", content);

		content_size=strlen(content);
		//printf("\n size = %d", content_size);

		for(content_index=0; content_index < content_size;)
		{
			for(ind=0; ind < ENCRYPT_SIZE; ind++, content_index++)
				pdcp_data[ind] = content[content_index];
			pdcp_data[ind++]='\0';
			//printf("\nIn 4 - %s", pdcp_data);

			for(ind=0;ind < ENCRYPT_SIZE;ind++)
			{
				sprintf(some_var,"\0");
				sprintf(some_var, "%x", pdcp_data[ind]);

				if(ind==0)
				{
					first=atoi(some_var);
					//printf("\nfirst  = %d", first);
				}
				else if(ind==1)
				{
					second=atoi(some_var);
					//printf("\nsecond  = %d", second);
				}
				else if(ind==2)
				{
					third=atoi(some_var);
					//printf("\nthird  = %d", third);
				}
				else if(ind==3)
				{
					fourth=atoi(some_var);
					//printf("\nfourth  = %d", fourth);
				}
			}

			u8 data[4] = {first,second,third,fourth};
			final = uea2(key,10,1,1,data,32);
			//printf("\n final = %s", final);

			packets[i].encrypted_data = (char*) malloc (ENCRYPTED_SIZE);
			strcpy(packets[i].encrypted_data,final);
			tracepoint(lte_component, pdcp_packet, "PDCP", packets[i].userid, packets[i].payload, packets[i].type_of_data, packets[i].encrypted_data);
		}
	}

	printf("\n\n");

	//}
}
