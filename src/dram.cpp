#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "dram.h"


///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

void dram_print_stats(DRAM* dram){
	double rddelay_avg=0, wrdelay_avg=0;
	char header[256];
	sprintf(header, "DRAM");

	if (dram->stat_read_access) {
		rddelay_avg = (double)(dram->stat_read_delay) / (double)(dram->stat_read_access);
	}

	if (dram->stat_write_access) {
		wrdelay_avg = (double)(dram->stat_write_delay) / (double)(dram->stat_write_access);
	}

	printf("\n%s_READ_ACCESS\t\t : %10llu", header, dram->stat_read_access);
	printf("\n%s_WRITE_ACCESS\t\t : %10llu", header, dram->stat_write_access);
	printf("\n%s_READ_DELAY_AVG\t\t : %10.3f", header, rddelay_avg);
	printf("\n%s_WRITE_DELAY_AVG\t\t : %10.3f", header, wrdelay_avg);

}

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

DRAM* dram_new(){

    DRAM* dram_mem = (DRAM*) calloc (1, sizeof(DRAM));
    return dram_mem;
}

uint64_t dram_access_mode_CDE(DRAM* dram, Addr lineaddr, bool is_dram_write) {

    uint64_t delay = 10;
    uint32_t bank_index = (lineaddr) & 0xF; 
    uint32_t row_index = (lineaddr >> 8);

    if(!dram->row_bufs[bank_index].valid)
    {
        dram->row_bufs[bank_index].rowID = row_index;
        dram->row_bufs[bank_index].valid = true;        
        delay += 45 + 45;
    }
    else if (dram->row_bufs[bank_index].rowID != row_index)
    {
        dram->row_bufs[bank_index].rowID = row_index;
        dram->row_bufs[bank_index].valid = true;
        delay += DRAM_PAGE_POLICY ? (45 + 45) : (45 + 45 + 45);
    }
    else
    {
        delay += DRAM_PAGE_POLICY ? (45 + 45) : 45;
    }
            
    if (is_dram_write)
    {
        dram->stat_write_access++;
        dram->stat_write_delay += delay;
    }
    else
    {
        dram->stat_read_access++;
        dram->stat_read_delay += delay;
    }
    return delay;

}

///////////////////////////////////////////////////////////////////
// Modify the function below only for Parts C,D,E
///////////////////////////////////////////////////////////////////

uint64_t dram_access(DRAM* dram, Addr lineaddr, bool is_dram_write) {

    uint64_t delay;
    uint8_t bank_index = (lineaddr) & 0xF; 
    uint32_t row_index = (lineaddr >> 8) & 0x3FFFF;


    if (dram->row_bufs[bank_index].rowID == row_index && dram->row_bufs[bank_index].valid)
    {
        delay = 100;
    }
    else
    {
        dram->row_bufs[bank_index].rowID = row_index;
        dram->row_bufs[bank_index].valid = true;
        delay = 100;
    }

    if (is_dram_write)
    {
        dram->stat_write_access++;
        dram->stat_write_delay += delay;
    }
    else
    {
        dram->stat_read_access++;
        dram->stat_read_delay += delay;
    }
    return delay;

}

