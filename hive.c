/*-
 * Copyright 2009 Colin Percival, 2011 ArtForz, 2013 Neisklar,
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file was originally written by Colin Percival as part of the Tarsnap
 * online backup system.
 */

#include "hive.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "sha3/sph_blake.h"
#include "sha3/sph_keccak.h"
#include "sha3/sph_shabal.h"
#include "pomelo.h"


void hive_hash(const char* input, char* output)
{
    sph_blake256_context     ctx_blake;
    sph_shabal256_context       ctx_shabal;
    sph_keccak256_context    ctx_keccak;


    uint32_t hashA[16], hashB[16];



    sph_shabal256_init(&ctx_shabal);
    sph_shabal256 (&ctx_shabal, input, 80);
    sph_shabal256_close (&ctx_shabal, hashA);	 //0


    POMELO(hashB, 32, hashA, 32, hashA, 32, 2, 10);


    sph_blake256_init(&ctx_blake);
    sph_blake256 (&ctx_blake, hashA, 64);    //0
    sph_blake256_close(&ctx_blake, hashB);   //1


    sph_keccak256_init(&ctx_keccak);
    sph_keccak256 (&ctx_keccak, hashB, 64); //2
    sph_keccak256_close(&ctx_keccak, hashA); //3



	memcpy(output, hashA, 32);





}


