    /***********************************************************************
     * Name: Renn Jervis                                                   *
     * Box: 3762                                                           *
     * Assignment name: Supplemental Problem Number 3                      *
     * Assignment for Monday, November 3rd                                 *
     ***********************************************************************/

    /* *********************************************************************
     * Academic honesty certification:                                     *
     *   Written/online sources used:                                      *
     *     [referenced project 101 and program darts.c for example of a    *
     *      random number generator.                                       *
     *      max-array.c from 1D array lab for help finding max # in array  *
     *     referenced program from problem description family-size-stub.c  *
     *     referenced program lab2-2.c for advisement on passing pointers  *
     *     and or declaring pointers.                                      *
     *     ->from laboratory exercise on arrays, Array Parameter reading   *
     *     -> was advised by pfof walkers emails about the problem         *
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
*   chidren until they have at least one girl and one boy.( please note     *
*   family size refers to number of children, not number of chilren + 2     *
*   to include the parents.                                                 *
*   This program will take the results of the simulation and print a table  *
*   as well as a histogram of the results. The height of the histogram ought*
*   to be scaled. The vertical axis of this histogram is number of couples  *
*   and the horozontal axis is the family size */ 

//compile this program  with gcc -o 1 supProb3.c

#include <stdio.h>
#include <stdlib.h>  //for use with random number generator
#include <time.h>
#include <math.h>

//Pre-conditions: size given is size of array(inclusive)
//Post-conditions:function prints element(inidices)= and corresponding 
//array element.        note: for testing
void printArray(int ar[], int size);

//Pre-conditions:array contains some positive integers
//Post-conditions:funtion returns max number in array and stores
// average of arrray elements in average
int max_average(int ar[], int numCouples, double *average);

//Pre-conditions:none
//Post-conditions:function fills in second array with the count of elements
//  in the first array (for example 
void count(int ar[], int ar2[], int couples, int maxSize);

//Pre-conditions:none
//Post-conditions: prints correctly spaces and labeled axes
void printXaxis(int);

//Pre-conditions:none
//Post-conditions:function prints appropriatly spaced numeric labels
//0 -spaces- inc -spaces- 2*inc -spaces2- maxRecordedsize
void printAxisLabels(int, int inc);

int main()
{
  /* the number of couples in the simulation */
  const int numberOfCouples = 60;

  /* number of children is recorded for sizes 1 .. maxRecordedSize */
  const int maxRecordedSize = 30;

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

  printf("\taverage number of children: %.1lf\n", ave); //round to nearest .1
  printf("\tmax family size: %d\n\n", max_size);
  //printArray(sizes, numberOfCouples-1); 
  //note as above couples ranges from 0 to numberOfCouples-1

  int tally[maxRecordedSize];
  //count will tabulate resuls of the simulation into the tally array and print
  // a table with Family size (# Children): tally[famSize] count of how many
  // famlies
  //have the corresponding family size
  count(sizes, tally, numberOfCouples, maxRecordedSize);
  //printArray(tally, maxRecordedSize);
  

  //find max of tabulated results, value stored in discard here is average
  //count, which does not apply
  double discard;
  int max_count;
  max_count=max_average(tally, maxRecordedSize, &discard);
  //printf("max count=%d\n", max_count);
  //printf("height of histogram: %d\n", heightOfHistogram);

  int posx,rowNum;
  int aCount=0;
  double dscale;
  int scale;
  if(max_count>heightOfHistogram)
    {
      dscale= max_count / (double) heightOfHistogram;
      scale =(dscale+1); 
    }
  else if(max_count>2*heightOfHistogram)
    {
      dscale= max_count / (double) 2*heightOfHistogram;
      scale =(dscale+1);
    }
  else if (max_count>heightOfHistogram)
    {
      dscale= max_count / (double)heightOfHistogram;
      scale =(dscale+1);
    }
  else 
    { scale=1;
    }
  printf("scale =%d\n", scale);
  printf("# couples\n"); //axis title
  //only print heightOfHistogram number labels
 
  //for loop condition 1 steps through all rows and codition 2 prints 
  //no more rows than heightOfHistogram. notice aCount<heightOfHistogram
  //because
      for(rowNum=max_count; aCount<heightOfHistogram && rowNum>0 ; rowNum--)
	{
	  if(rowNum==max_count || rowNum==1) //max or unit label 
	    { printf("%6d:", rowNum);
	      aCount+=1; //variable to count print statements
	    }
	  else if(rowNum>(max_count-(3*scale))) //extra elements
	    { continue;
	    }
	  else if (tally[rowNum] !=0) //if necessary to show star steps
	   {
	     printf("%6d:", rowNum);
	     aCount+=1; //variable to count print statements
	   }
	  //ignore some row values, dont print or increment aCount
	  else if(rowNum==max_count-scale || rowNum==max_count-1 )
	    {
	      continue; 
	    }
	  else 
	    {
	      if (rowNum%2==1)
		{ continue;
	        }
	      else{
		printf("%6d:", rowNum);
		aCount+=1;
	      }
	    
	    }
	  
	  //print stars
	  //consider printing series of characters on each line, 
	  //to be displayed above an axes, based on the tally array 
	  for(posx=0; posx<=maxRecordedSize; posx++)
	    {
	      if (tally[posx]==0) //if there are no families of size posx
		{
		  printf(" ");
		}
	      else if (tally[posx]>=rowNum) 
		//if tally[i] is > the value for the line, then print *
		printf("*");
	      else printf(" "); //fill in rest of spaces
	    } 
	  printf("\n");
	}

      //printf("number lines printed = %d\n", aCount);  

      //print horozontal axes and labels
  printXaxis(maxRecordedSize);

  return 0;
}

void count(int arSizes[], int count[], int numberOfCouples, int maxRecordedSize)
{ 
  int size, i;

 //loop to set all elements second array to zero
  for(i=0; i<=maxRecordedSize; i++) count[i]=0;
 
  //check each array element and tally sizes 
  for(size=0; size<=maxRecordedSize; size++)
    {
      for(i=0; i<numberOfCouples; i++)
        {
          if(arSizes[i]==size)
            {
            count[size]+=1;
            }
        }
    }
 
  //print table
  printf("Family size  counts\n");
  printf("# children:  count\n");
  for(size=0; size<=maxRecordedSize; size++)
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
 //note: if there are no positive elements in array 0 will be returned as max
  int i;
  for (i=0; i<size; i++)
    {
      sum+=ar[i];   //total array elements for average
      if(ar[i]>max)
        max=ar[i];       
    }
  *average= sum / (double) size;
  return max;
}

void printXaxis(int max_Size)
{
  int increment;
  if (((max_Size % 3)==0))
    increment=max_Size/ 3;
  else if ((max_Size %3 !=0))
    {int rem=(max_Size%3);
      increment=((max_Size-rem)/3);
    }
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
 // printf("increment %d\n", increment);
}

void printAxisLabels(int maxRecordedSize, int inc)
{
  int i=0;
  printf("       0");
  for(i=1; i<=maxRecordedSize; i++)
    {
      if (i== inc)
	{ if(inc>=10) i+=1;  /*account for spacing of '10' ei digits of lables*/
	  printf("%d", inc);
	}
      else if(i== 2*inc) 
	{ if (inc*2>=10) i+=1;    /*if accounts for single digit increments*/
	  printf("%d", 2*inc);
	}
      else if(i== maxRecordedSize)
	printf("%d", maxRecordedSize);
      else
	printf(" ");
    }
  printf("\n");
  printf("\tfamily sizes\n");

}






