#include <xky_printf.h>
#include <xky.h>
#include <bare.h>

void entry_point(void)
{
    xky_id_t my_id;

    while (1)
    {
        my_id = xky_syscall_get_partition_id(NULL);
        xky_printf("\nPartition_%i\n", my_id);
    }
}
