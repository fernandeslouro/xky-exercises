#include <xky_printf.h>
#include <xky.h>
#include <bare.h>

void entry_point(void)
{
    xky_printf("Partition 0!\n");
    bare_wake_in_next_mtf();
}
