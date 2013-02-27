
#include "fivebyfive.h"
#include "fivebyfive_textscrolling.h"

int main()
{
    fivebyfive_init();
    char text[]  = "THIS IS SOME TEXT";
    fivebyfivetext_scrolltext(text, 35, 1);
}