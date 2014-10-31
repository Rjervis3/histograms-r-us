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
     *                                    *
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

int average(int arr[][2]);

int main()
{
  /* the number of couples in the simulation */
  const int numberOfCouples = 10;

  /* number of children is recorded for sizes 1 .. maxRecordedSize */
  const int maxRecordedSize = 30;

  int famSize [maxRecordedSize + 1];

  /* the highest point of the histogram will have heightOfHistogram *'s */
  const int heightOfHistogram = 20;

  int dataArray[numberOfCouples][2]; //will store couple number and # kids

  const int MaxRandInt = RAND_MAX; 
  srand (time ((time_t *) 0) );


  //simulation
  int n, k;
  for (n=1; n<=numberOfCouples; n++)
    {
      dataArray[n][0]=n;
      
    

      int boys=0;
      int girls=0;
      while ((boys ==0) || (girls ==0))     //while none of either gender
	{
	  if ((rand() / (double) MaxRandInt) < 0.5)
	    girls++;
	  else boys++;
	}
       dataArray[n][1] = boys + girls;
       printf(" couple %d: %d\n", dataArray[n][0], dataArray[n][1]);
       average(dataArray);

    }
  return 0;
}
