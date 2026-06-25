/*******************************************************************************
*
* File utils.c
* 
* Collection of basic utility programs
*
*
* Author: Leonardo Giusti, Samuele Campaniello
*
*******************************************************************************/
#define UTILS_C

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Prints the V vector of length given in the "filename" file
void printer (double V[], int length, char* filename)
{
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("Error opening the file %s", filename);
        exit(1);
    }
    
    for (int i = 0; i < length; i++)
    { fprintf(fp, "%f\n", V[i]); }
    
    fclose(fp);
}

// Calculates the average of the V vector of length given
double Avg (double V[], int length)
{
    double avg=0.0;
    for(int i=0; i<length; i++)
    { avg+=V[i]; }
    return avg/(double)length;
}



















// Stuff made by prof. Giusti
struct addr_t
{
   char *addr;
   char *true_addr;
   struct addr_t *next;
};
static struct addr_t *first=NULL;

void error(int test,int no,char *name,char *text)
{
   if (test!=0)
   {
      printf("\n");
      printf("Error in %s\n%s\n",name,text);
      printf("Program aborted\n\n");
      exit(no);
   }
}
void *amalloc(size_t size,int p)
{
   int shift;
   char *true_addr,*addr;
   unsigned long mask;
   struct addr_t *new;

   if ((size<=0)||(p<0))
      return(NULL);

   shift=1<<p;
   mask=(unsigned long)(shift-1);

   true_addr=malloc(size+shift);
   new=malloc(sizeof(*first));
   
   if ((true_addr==NULL)||(new==NULL))
   {
      free(true_addr);
      free(new);
      return(NULL);
   }

   addr=(char*)(((unsigned long)(true_addr+shift))&(~mask));
   (*new).addr=addr;
   (*new).true_addr=true_addr;
   (*new).next=first;
   first=new;
                   
   return((void*)(addr));
}
void afree(void *addr)
{
   struct addr_t *p,*q;

   q=NULL;
   
   for (p=first;p!=NULL;p=(*p).next)
   {
      if ((*p).addr==addr)
      {
         if (q!=NULL)
            (*q).next=(*p).next;
         else
            first=(*p).next;
         
         free((*p).true_addr);
         free(p);
         return;
      }
      
      q=p;
   }
}


