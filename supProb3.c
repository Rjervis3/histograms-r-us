    /***********************************************************************
     * Name: Renn Jervis                                                   *
     * Box: 3762                                                           *
     * Assignment name: Supplemental Problem Number 3                      *
     * Assignment for Monday, November 3rd                                 *
     ***********************************************************************/

    /* *********************************************************************
     * Academic honesty certification:                                     *
     *   Written/online sources used:                                      *
     *     [referenced project 101                             *
     *      max-array.c from 1D array lab for help finding max # in array  *
     *      -> was advised by pfof walkers emails about the problem        *
     *     referenced program from problem description family-size-stub.c  *
     *     referenced program lab2-2.c for advisement on passing pointers  *
     *     and or declaring pointers
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
*   to be scaled. The vertical axis of this histogram is number of couples  *
*   and the horozontal axis is the family size */ 

//compile with gcc -o 1 supProb3.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void printArray(int ar[], int size);
//Pre-conditions:
//Post-conditions:
int max_average(int ar[], int numCouples, double *average);

//Pre-conditions:
//Post-conditions:
void count(int ar[], int ar2[], int couples, int maxSize);

//Pre-conditions:
//Post-conditions:
void printXaxis(int);

void printAxisLabels(int, int inc);

void printHistogram(int height, int, int);

void printYaxis(int max_count, int height, int);

int main()
{
  /* the number of couples in the simulation */
  const int numberOfCouples = 30;

  /* number of children is recorded for sizes 1 .. maxRecordedSize */
  const int maxRecordedSize = 30;

  int famSize [maxRecordedSize + 1];

  /* the highest point of the histogram will have heightOfHistogram *'s */
  const int heightOfHistogram = 20;

  //portion of function to generate random number
  const int MaxRandInt = RAND_MAX; 
  srand (time ((time_t *) 0) ); //initialize seed based on time and machine

  //initial printing steps
  printf("\nSimulation of family size for %d couples\n", numberOfCouples);
  printf("\tfamily sizes truncated to %d\n", maxRecordedSize);
  printf("\tmaximum height of histogram: %d\n", heightOfHistogram);

  int sizes[numberOfCouples];

  //simulation
  int couple=0, k;
  // for (couple=0; couple<numberOfCouples; couple++)//run simulation for each 
  while (couple<numberOfCouples)               //couple 0 to numberOfCouples-1
    {
      int boys=0, girls=0;
      // printf(" couple %2d:", couple);
      while ((boys ==0) || (girls ==0))     //while none of either gender
	{
	  if ((rand() / (double) MaxRandInt) < 0.5)
	      girls++;
	  else	 
	    boys++;   
	}
      sizes[couple]= boys + girls;
      
      //ensure more than maxRecordedSize is not recorded
      if (sizes[couple] > maxRecordedSize)
	sizes[couple]=maxRecordedSize;
      
      //printf(" family size %d\n", sizes[couple]);
      couple++;
     
    } //end simulation

  double ave;
  int max_size;  //ret maximum fam size, ave pointer updated

  max_size= max_average(sizes, numberOfCouples, &ave);
  printf("\tmax number of children: %d\n", max_size);
  printf("\taverage number of children: %.2lf\n", ave);
  
  //take largest number from count and print histogram with that many 
  //stars as height

  int tally[numberOfCouples];
  count(sizes, tally, numberOfCouples, maxRecordedSize);
  //printf("print tally after calling count function (main)");
  // printArray(tally, maxRecordedSize);
  double discard;
  int max_count;
  max_count=max_average(tally,numberOfCouples , &discard);
   printf("max count=%d\n", max_count);
   // printf("print just before here (main)\n");
   //printArray(tally, maxRecordedSize);
  int posx,rowNum, i,j,z;
  char stars[maxRecordedSize];
  
  printf("# couples\n");
  //only print heightOfHistogram number lablels
  for(rowNum=max_count; rowNum>0; rowNum--)
    { printf("%6d:", rowNum);
    for(posx=0; posx<maxRecordedSize; posx++)
      {
	if (tally[posx]==0)
	  {
	    //printf("tally[%d]==0\n", posx);
	  printf(" ");
	  }
	else if (tally[posx]>=rowNum)
	  printf("*");
      }printf("\n");
    }
  
  /*
  for(posy=heightOfHistogram; posy>0; posy--)
    { 
      tally[0]=0;
      //printf("tally[0]=%d\n", tally[0]);
      printf("%6d: ", posy);
      for(z=0; z<=maxRecordedSize; z++) //loop to clear out array
	{stars[z]=' ';
	}
      tally[0]=0;
      //printf("ztally[0]=%d\n", tally[0]);
      for(i=0; i<=maxRecordedSize; i++) 
	{//stars[0]=' ';
	  if (tally[i]>posy)
	    { //printf("atally[0]=%d\n", tally[0]);
	      stars[i]='*';
	    }
	  else if (tally[i]==0)
	    {//printf("tally[0]=%d\n", tally[0]);
	      stars[i]=' ';
	    }
	  else stars[i]= ' ';
	  
	}
      printf ("\n");
      // printf("here\n");
      //printf("tally[0]=%d\n", tally[0]);

      printArray(tally, maxRecordedSize);
    }
  */
  printHistogram(heightOfHistogram, maxRecordedSize, max_count);
  return 0;
}

void printArray(int ar[], int size)
{int i;
  for(i=0; i<=size; i++)
    printf("element %d=%d \n", i, ar[i]);
}
void printHistogram(int height, int rBound, int max_count)
{
  // printf("\n\nHistogram of family sizes:\n\n");
  // printYaxis(max_count, height, rBound);
  printXaxis(rBound);
}
void printYaxis(int max_count, int height, int maxFamSize)
{
  printf("top bound = %d\n\n", max_count);
  int i;
}
void printXaxis(int max_Size)
{
  int increment;
  if (((max_Size % 2)==0))
    increment= max_Size/4;
  if (((max_Size % 3)==0))
    increment=max_Size/3;

  int i;
  printf("       +");
  for(i=1; i<=max_Size; i++)
    {
      if (i== increment)
	printf("+");
      else if(i== 2*increment) 
	printf("+");
      else if(i== max_Size)
	printf("+");
      else 
        printf("-");	
    }
  printf("\n");
 printAxisLabels(max_Size, increment);
 printf("increment %d\n", increment);
}

void printAxisLabels(int max, int inc)
{
  int i=0;
 
  printf("       0");
  for(i=1; i<=max; i++)
    {
      if (i== inc)
	{ if(inc>=10) i+=1;  /*account for spacing of '10' ei digits of lables*/
	  printf("%d", inc);
	}
      else if(i== 2*inc) 
	{ if (inc*2>=10) i+=1;    /*if accounts dor single digit increments*/
	  printf("%d", 2*inc);
	}
      else if(i== max)
	printf("%d", max);
      else
	printf(" ");
    }
  printf("\n");
  printf("\tfamily sizes\n");

}


int max_average(int ar[], int size, double *average)
{ 
  double sum=0;
  int max=0; 
    int i;
    //  printf("printing ar in m_a\n\n");
    // printArray(ar, size);
  for (i=0; i<size; i++)
    {
      sum+=ar[i];
      if(ar[i]>max)
        max=ar[i]; //update value max points to
        
    }
  *average= sum / (double) size;
  //printf("-printing ar again in m_a\n\n");
  //printArray(ar, size);
  return max;
}


void count(int arraySizes[], int count[], int couples, int maxSize)
{ 
  int size, i;
  // int tally[maxSize];
  for(i=0; i<=maxSize; i++) //loop to clear out array
    {count[i]=0;
    }
  // printf("-printing in count\n\n");
  // printArray(count, maxSize);
  for(size=0; size<=maxSize; size++)
    {
      for(i=0; i<couples; i++)
        {
          if(arraySizes[i]==size)
            {
            count[size]+=1;
            }
        }
    }
  //check each array element and tally sizes
  printf("Family size  counts\n");
  printf("# children:  count\n");
  for(size=0; size<=maxSize; size++)
    printf("%10d: %6d\n", size, count[size]);

  //printf("-printing of count after count\n\n");
  //printArray(count, maxSize);

}
