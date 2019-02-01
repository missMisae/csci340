// -----------------------------------
// CSCI 340 - Operating Systems
// Spring 2019
// cache.c file
//
// Homework 1
//
// -----------------------------------

#include "cache.h"
#include "memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int initializeCache(unsigned int number_of_lines)
{
  int line, retVal;

  retVal = OK;

  cache = malloc(sizeof(cache_line*) * number_of_lines);

  if (cache != NULL) {

    for (line=0; line<number_of_lines; line++) {

      cache[line] = (cache_line*) malloc(sizeof(cache_line));
      cache[line]->tag = UNK;
      cache[line]->hit_count = ZERO;

    }

  } else
    retVal = FAIL;

  return retVal;

} // end initializeCache function


int cread(unsigned int cmf, unsigned int* hex_addr, unsigned int* found,
	  unsigned int* replace)
{

  static unsigned int tag;

  int i;
  unsigned int offset;
  unsigned int line;


  unsigned int offsetAND;
  unsigned int lineAND;
  unsigned int tagAND;
  unsigned int value;

  int numSets;
  int byte;


  if(cmf ==1){
  //direct mapping
  //grab offset
        offsetAND = pow(2,NUM_BLOCK_OFFSET_BITS) -1;

        //offset = *hex_addr >> NUM_BLOCK_OFFSET_BITS;
        offset = *hex_addr & offsetAND;



        //grab line bits
        lineAND = pow(2, NUM_OF_LINE_BITS) -1;
        line = (*hex_addr >> NUM_BLOCK_OFFSET_BITS) & lineAND;


        //grab tag bits
        tagAND = pow(2, NUM_OF_TAG_BITS_DM)-1;
        tag = (*hex_addr >> 5) & tagAND;

        value = (phy_memory[(block_location[line] + offset)]);

          for (i=0; i <NUM_OF_LINES; i++) {

            if(cache[i]->tag == tag){

                *found = YES;
                cache[i]->hit_count = YES;
                *replace = NO;
                break;


            }//end if
            else{
              //cache[i]->hit_count= NO;
              *found = NO;
              *replace = YES;
              cache[i]->hit_count = NO;
              cache[0]-> tag = tag;
            }//end else
          }//end for
}//end if

else{
  
          offsetAND = pow(2,NUM_BLOCK_OFFSET_BITS) -1;

          //offset = *hex_addr >> NUM_BLOCK_OFFSET_BITS;
          offset = *hex_addr & offsetAND;



          //grab line bits
          lineAND = pow(2, NUM_OF_LINE_BITS) -1;
          line = (*hex_addr >> NUM_BLOCK_OFFSET_BITS) & lineAND;


          //grab tag bits
          tagAND = pow(2, NUM_OF_TAG_BITS_SA)-1;
          tag = (*hex_addr >> 5) & tagAND;

          value = (phy_memory[(block_location[line] + offset)]);

            for (i=0; i <NUM_OF_LINES; i++) {

              if(cache[i]->tag == tag){

                  *found = YES;
                  cache[i]->hit_count = YES;
                  *replace = NO;
                  break;


              }//end if
              else{
                //cache[i]->hit_count= NO;
                *found = NO;
                *replace = YES;
                cache[i]->hit_count = NO;
                cache[0]-> tag = tag;
              }//end else
            }//end for
}//end else

  return value;
}//end cread



void cprint()
{
  unsigned int line;

  printf("\n---------------------------------------------\n");
  printf("line\ttag\tnum of hits\n");
  printf("---------------------------------------------\n");

  for (line=0; line<NUM_OF_LINES; line++) {

    if (cache[line]->tag == UNK) {

      printf("%d\t%d\t%d\n", line, cache[line]->tag, cache[line]->hit_count);

    } else {

      printf("%d\t%02X\t%d\n", line, cache[line]->tag, cache[line]->hit_count);

    }

  }

} // end cprint function
