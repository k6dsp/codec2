/*---------------------------------------------------------------------------*\

  FILE........: dac_play.c
  AUTHOR......: David Rowe
  DATE CREATED: 1 June 2013

  Plays a 16 kHz sample rate raw file to the Discovery DAC.

\*---------------------------------------------------------------------------*/

/*
  Copyright (C) 2013 David Rowe

  All rights reserved.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License version 2.1, as
  published by the Free Software Foundation.  This program is
  distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
  License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with this program; if not, see <http://www.gnu.org/licenses/>.
*/

#include <stdlib.h>
#include "stm32f4_dac.h"
#include "gdb_stdio.h"

#define printf gdb_stdio_printf
#define fopen gdb_stdio_fopen
#define fclose gdb_stdio_fclose
#define fread gdb_stdio_fread
#define fwrite gdb_stdio_fwrite

#define N   2000

int main(void) {
    short  buf[N];
    FILE  *fin;

    dac_open();

    while(1) {
        fin = fopen("stm_in.raw", "rb");
        if (fin == NULL) {
            printf("Error opening input file: stm_in.raw\n\nTerminating....\n");
            exit(1);
        }
    
        printf("Starting!\n");

        while(fread(buf, sizeof(short), N, fin) == N) {
            while(dac_write(buf, N) == -1);
        }  

        printf("Finished!\n");
        fclose(fin);
    }

    /* let FIFO empty */

    while(1);
}

