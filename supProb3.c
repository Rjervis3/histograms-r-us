    /***********************************************************************
     * Name: Renn Jervis*                                                   *
     * Box: 3762                                                           *
     * Assignment name: Supplemental Problem Number 3                      *
     * Assignment for Monday, November 3rd                                 *
     ***********************************************************************/

    /* *********************************************************************
     * Academic honesty certification:                                     *
     *   Written/online sources used:                                      *
     *     [referenced project 101                             *
     *      max-array.c from 1D array lab for help finding max # in array  *
     *                                    *
     *   Help obtained: [none]                                             *
     *                                                                     *
     *   My/our signature(s) below confirms that the above list of sources *
     *   is complete AND that I/we have not talked to anyone else          *
     *   (e.g., CSC 161 students) about the solution to this problem       *
     *                                                                     *
     *   Signature:                                                        *
     ***********************************************************************/




/* This is a program to tabulate the result of a simulation. The simulation *
*   is to determine the family size of a family that will keep having       * 
*   chidren until they have at least one girl and one boy.                  *
*   This program will take the results of the simulation and print a table  *
*   as well as a histogram of the results. The height of the histogram ought*
*   to be scaled. */ 

//compile with gcc -o 1 supProb3.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void average_and_max(int ar[], int numCouples);
void count(int ar[], int couples, int maxSize);

int main()
{
  /* the number of couples in the simulation */
  const int numberOfCouples = 10;

  /* number of children is recorded for sizes 1 .. maxRecordedSize */
  const int maxRecordedSize = 9;

  int famSize [maxRecordedSize + 1];

  /* the highest point of the histogram will have heightOfHistogram *'s */
  const int heightOfHistogram = 20;

  const int MaxRandInt = RAND_MAX; 
  srand (time ((time_t *) 0) );

  int sizes[numberOfCouples];

  //simulation
  int couple, k;
  for (couple=0; couple<numberOfCouples; couple++)
    {
      int boys=0;
      int girls=0;
      while ((boys ==0) || (girls ==0))     //while none of either gender
	{
	  if ((rand() / (double) MaxRandInt) < 0.5)
	    girls++;
	  else boys++;
	}
      sizes[couple]= boys + girls;
      printf(" couple %2d: family size %d\n", couple, sizes[couple]);
     
     
    }
  average_and_max(sizes, numberOfCouples);
  count(sizes, numberOfCouples, maxRecordedSize);
  return 0;
}

void average_and_max(int ar[], int numCouples)
{ int j=0, max=ar[0], i;
 
  for (i=0; i<numCouples; i++)
    {
      j+=ar[i];
      if(ar[i]>max)
        max=ar[i];
        
    }
  printf("total kids: %d\n", j);
  printf("maximum: %d\n", max);
  printf("average number of children: %lf\n",j/ (double)numCouples);

}

void count(int arraySizes[], int couples, int maxSize)
{ 
  int size, i;
  int tally[maxSize];
  for(i=0; i<=maxSize; i++)
    {tally[i]=0;
      //  printf("tally: %d\n", tally[i]);
    }
  for(size=0; size<=maxSize; size++)
    {// printf("family size %d, compare to %d\n", size, arraySizes[size]);
      for(i=0; i<couples; i++)
        { //printf("size = %d, compare to %d\n", size, arraySizes[i]);
         
          if(arraySizes[i]==size)
            {//printf("yes\n");
            tally[size]+=1;
            }
          // else tally[size]=0;
        }
    }
  //check each array element and tally sizes

  for(size=0; size<=maxSize; size++)
    printf("fam size %d, count %d\n", size, tally[size]);
}
