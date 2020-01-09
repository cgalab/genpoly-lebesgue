/*****************************************************************************/
/*                                                                           */
/*                       2019-2020      Martin Held                          */
/*                                                                           */
/*                                                                           */
/* E-Mail:      held@cs.sbg.ac.at                                            */
/* Snail Mail:  Universitaet Salzburg, FB Computerwissenschaften,            */
/*              Jakob-Haringer Str. 2, A-5020 Salzburg, Austria (Europe).    */
/*                                                                           */
/*****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>


#ifdef BOOL_DEFINED
typedef bool boolean;
#else
#define false 0
#define true  (!false)
typedef unsigned char  boolean;
#endif

#define NIL -1

int counter = 0;


void drawCurve(FILE *output,   
               long int x_min, long int x_max,
               long int y_min, long int y_max,
               int level)                                     /* level       */
{
   long int x_m1, y_m1, x_m2, y_m2;

   if (level > 1) {
      /*                                                                     */
      /* four recursive calls                                                */
      /*                                                                     */
      level -= 1;

      x_m1 = x_min + (x_max - x_min) / 2;
      y_m1 = y_min + (y_max - y_min) / 2;
      x_m2 = x_m1 + 1;
      y_m2 = y_m1 + 1;
      drawCurve(output, x_min, x_m1, y_m2, y_max, level);  
      drawCurve(output, x_m2, x_max, y_m2, y_max, level);  
      drawCurve(output, x_min, x_m1, y_min, y_m1, level);  
      drawCurve(output, x_m2, x_max, y_min, y_m1, level);  
   }
   else {
      /* generate Z                                                          */
      fprintf(output, "%ld %ld\n", x_min, y_max);
      fprintf(output, "%ld %ld\n", x_max, y_max);
      fprintf(output, "%ld %ld\n", x_min, y_min);
      fprintf(output, "%ld %ld\n", x_max, y_min);
   }
    
   return;
}

void PrintHeader(void)
{
   printf("\n");
   printf("***********************************************************\n");
   printf("*                                                         *\n");
   printf("*                      make_lebesgue                      *\n");
   printf("*                                                         *\n");
   printf("* Generation of a (closed) Lebesgue curve.                *\n");
   printf("*                                                         *\n");
   printf("*      Martin Held 2019-2020        held@cs.sbg.ac.at     *\n");
   printf("*                                                         *\n");
   printf("***********************************************************\n");

   return;
}


void OpenFile(FILE  **output, const char *file_name)
{
   /* open file */
   if((*output = fopen(file_name, "w")) == NULL) {
      fprintf(stderr,"*** Output file not created! ***\n");
      exit(1);
   }
   
   return;
}   


int main(int argc, char **argv)
{
   int count = 1;
   boolean name_read = false, success = true;
   long int x_min, x_max, y_min, y_max;
   int level = -1;
   FILE *output;
   long int number;
   char    *file_name = "lebesgue.line";

   PrintHeader();

   /*                                                                        */
   /* parse command-line arguments                                           */
   /*                                                                        */
   while ((count < argc)  &&  success)    {

      if (strcmp(argv[count],"--number") == 0) {
         ++count;
         if ((success = (count < argc)))  level = atoi(argv[count]);
      }
      else if (strcmp(argv[count],"--output") == 0) {
         ++count;
         if ((success = (count < argc))) {
            file_name = argv[count];
            name_read = true;
         }
      }
      else {
         success = false;
      }
      ++count;
   }

   if (!success  ||  !name_read  ||  (level <= 0)) {
      if (!success) 
         printf("\nUnrecognized command-line option: %s\n", argv[count-1]); 
      printf("\nUsage: make_lebesgue --number N --output XYZ\n       where N is a positive integer.\n"); 
      exit(2);
   }

   /*                                                                        */
   /* initialization                                                         */
   /*                                                                        */
   OpenFile(&output, file_name);
   number = pow(4, level);
   x_min = y_min = 1;
   x_max = y_max = pow(2, level);

   fprintf(output, "%ld\n", number + 5);
   printf("... generating %ld vertices: ", number);
   fflush(stdout);

   drawCurve(output, x_min, x_max, y_min, y_max, level);

   fprintf(output, "%ld 0\n", x_max);
   fprintf(output, "1 0\n");
   fprintf(output, "0 0\n");
   fprintf(output, "0 %ld\n", y_max);
   fprintf(output, "1 %ld\n", y_max);

   fclose(output);
   printf("done\n");

   exit(0);
}
