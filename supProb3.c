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
     *     from laboratory exercise on arrays, Array Parameter reading
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

//Pre-conditions:size given is size of array
//Post-conditions:function prints inidices and corresponding array element
void printArray(int ar[], int size);

//Pre-conditions:array contains some positive integers
//Post-conditions:funtion returns max number in array and stores
// average of arrray elements in average
int max_average(int ar[], int numCouples, double *average);

//Pre-conditions:
//Post-conditions:]function fills in second array with the count of elements
//  in the first array
void count(int ar[], int ar2[], int couples, int maxSize);

//Pre-conditions:
//Post-conditions:
void printXaxis(int);

//Pre-conditions:
//Post-conditions:
void printAxisLabels(int, int inc);

//Pre-conditions:
//Post-conditions:
void printHistogram(int height, int, int);

//Pre-conditions:
//Post-conditions:function prints
void printYaxis(int max_count, int height, int);

int main()
{
  /* the number of couples in the simulation */
  const int numberOfCouples = 50;

  /* number of children is recorded for sizes 1 .. maxRecordedSize */
  const int maxRecordedSize = 40;

  //int famSize [maxRecordedSize + 1];

  /* the highest point of the histogram will have heightOfHistogram *'s */
  const int heightOfHistogram = 20;

  //portion of function to generate random number
  const int MaxRandInt = RAND_MAX; 
  srand (time ((time_t *) 0) ); //initialize seed based on time and machine

  //initial printing steps
  printf("\nSimulation of family size for %d couples\n", numberOfCouples);
  printf("\tfamily sizes truncated to %d\n", maxRecordedSize);
  printf("\tmaximum height of histogram: %d\n", heightOfHistogram);

  //array to hold the various family sizes
  int sizes[numberOfCouples];

  //simulation
  int couple=0, k;
  while (couple<numberOfCouples)               //couple 0 to numberOfCouples-1
    {
      int boys=0, girls=0;
      while ((boys ==0) || (girls ==0))     //while no kids of either gender
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
      
      couple++; 
    } //end simulation

  double ave;
  int max_size; 
  max_size= max_average(sizes, numberOfCouples, &ave);
  //returns maximum fam size, ave pointer updated to average

  printf("\taverage number of children: %.2lf\n", ave);
  printf("\tmax family size: %d\n", max_size);
  
  int tally[numberOfCouples];
  //count will tabulate resuls and print a table: # kids, count
  count(sizes, tally, numberOfCouples, maxRecordedSize);
  printArray(tally, maxRecordedSize);

  //find max of tabulated results, value stored in discard here is average
  //count, which does not apple
  double discard;
  int max_count;

  max_count=max_average(tally, maxRecordedSize, &discard);
  printf("max count=%d\n", max_count);


  int posx,rowNum;
  int aCount=0;
  printf("# couples\n"); //axis title
  //only print heightOfHistogram number lablels
 

  //now to print only heightOfHistogram rows
  do{
    //start with all rows, only print certain #
    for(rowNum=max_count;rowNum>0;rowNum=rowNum-1)
      {
        if(rowNum== max_count)
          { aCount+=1;
            printf("%6d:", rowNum);
          }
        else if (rowNum ==heightOfHistogram)
          { //always print first row ie max count
            continue;
          }
        else if(rowNum ==heightOfHistogram/2)
          {//middle
            aCount+=1;
            printf("%6d:", rowNum);
            //rowNum--;
          }
        else if(rowNum ==max_count/4)
          {//bottom fourth
            aCount+=1;
            printf("%6d:", rowNum);
            //rowNum--;
          } 
        else if(rowNum>heightOfHistogram)
          { //printf("%6d:", rowNum);
            continue; //dont print rows above height       
          }
        else if(rowNum>0 && (aCount))
          {printf("%6d:", rowNum);
            aCount+=1;
          }
        for(posx=0; posx<=maxRecordedSize; posx++)
          {
            if (tally[posx]==0)
              {
                printf(" ");
              }
            else if (tally[posx]>=rowNum)
              printf("*");
            else printf(" ");
          } 
        
        printf("\n");
      }  
      
    //printf("aCount=%d\n", aCount);
  }while(aCount<heightOfHistogram);

  printXaxis(maxRecordedSize);

  return 0;
}

void count(int arraySizes[], int count[], int couples, int maxSize)
{ 
  int size, i;

 //loop to clear out array
  for(i=0; i<=maxSize; i++) count[i]=0;
  
  //check each array element and tally sizes 
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
 
  //print table
  printf("Family size  counts\n");
  printf("# children:  count\n");
  for(size=0; size<=maxSize; size++)
    printf("%10d: %6d\n", size, count[size]);

}

void printArray(int ar[], int size)
{int i;
  for(i=0; i<=size; i++)
    printf("element %d=%d \n", i, ar[i]);
}
int max_average(int ar[], int size, double *average)
{ 
  double sum=0;
  int max=0; 
  int i;
  for (i=0; i<size; i++)
    {
      sum+=ar[i];
      if(ar[i]>max)
        max=ar[i]; 
        
    }
  *average= sum / (double) size;
  //printf("-printing ar again in m_a\n\n");
  //printArray(ar, size);
  return max;
}
void printXaxis(int max_Size)
{
  int increment;
  //printf("max size%3 = %d\n", max_Size%3);
  if (((max_Size % 3)==0))
    increment=max_Size/ 3;
  else if ((max_Size %3 !=0))
    {int rem=(max_Size%3);
      //printf("rem=%d\n", rem);
      increment=((max_Size-rem)/3);
    }
  // printf("increment=%d\n", increment);
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
	{ if (inc*2>=10) i+=1;    /*if accounts for single digit increments*/
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






