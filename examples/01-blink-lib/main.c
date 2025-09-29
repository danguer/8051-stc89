#include "../../lib/stc89.h"
#include "../../lib/utils.h"

void main(void)
{
    while(1)
    {
         P3 = 0x00; // LED on
         delay(1000);
         P3 = 0xFF; // LED off
         delay(1000);
    }
}