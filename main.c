#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "keys.h"
#include "play.h"

int main (int argc, char **argv)
{
   int iflag = 0;
   int oflag = 0;
   int pflag = 0;
   char *ivalue = NULL;
   char *ovalue = NULL;
   char *pvalue = NULL;
   int index;
   int c;

   opterr = 0;

   while ((c = getopt (argc, argv, "i:o:p:")) != -1) {
      switch (c)
      {
      case 'i':
         iflag = 1;
         ivalue = optarg;
         break;
      case 'o':
         oflag = 1;
         ovalue = optarg;
         break;
      case 'p':
         pflag = 1;
         pvalue = optarg;
         break;
      }
   }

   printf ("iflag = %d, oflag = %d pflag = %d value = %s ivalue = %s pvalue = %s\n",
          iflag, oflag, pflag, ovalue, ivalue, pvalue);

   for (index = optind; index < argc; index++)
      printf ("Non-option argument %s\n", argv[index]);
   if (iflag && !oflag) {
      // play file
   } else if (iflag && oflag) {
      // export input file
   } else if (pflag) {
      // interactive play notes
      int x = playNote(pvalue);
      printf("%d", x);
   }
   return 0;
}
