/*
 * uea2.h
 *
 *  Created on: 03-Apr-2013
 *      Author: aswin
 */


#ifndef UEA2_H_
#define UEA2_H_
/*---------------------------------------------------------
*
snow 3G algorithm implementation
*---------------------------------------------------------*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef enum { downlink, uplink } direction;
typedef enum { t1, t2, t3, t4, t5} bearer_type;

#define ENCRYPTED_SIZE 1000
#define BUF_SIZE 50

/* Initialization.
* Input k[4]: Four 32-bit words making up 128-bit key.
* Input IV[4]: Four 32-bit words making 128-bit initialization variable.
* Output: All the LFSRs and FSM are initialized for key generation.
*/
void Initialize(u32 k[4], u32 IV[4]);
/* Generation of Keystream.
* input n: number of 32-bit words of keystream.
* input z: space for the generated keystream, assumes
*
memory is allocated already.
* output: generated keystream which is filled in z
*/
void GenerateKeystream(u32 n, u32 *z);

/* uea2.
* Input key: 128 bit Confidentiality Key.
* Input count:32-bit Count, Frame dependent input.
* Input bearer: 5-bit Bearer identity (in the LSB side).
* Input dir:1 bit, direction of transmission.
* Input data: length number of bits, input bit stream.
* Input length: 32 bit Length, i.e., the number of bits to be encrypted or
*
decrypted.
* Output data: Output bit stream. Assumes data is suitably memory
* allocated.
* Encrypts/decrypts blocks of data between 1 and 2^32 bits in length as
*/

char * uea2( u8 *key, u32 count, u32 bearer, u32 dir, u8 *data, u32 length );

#endif
