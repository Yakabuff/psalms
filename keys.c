#include "keys.h"
int getKeyNumFromNotation(char* notation) {
   if (strcmp(notation, "A0") == 0) {
      return A0;
   } else if (strcmp(notation, "ASharp0") == 0) {
      return ASharp0;
   } else if (strcmp(notation, "C4") == 0) {
      return C4;
   }
}
