#include <xky_printf.h>
#include <xky.h>

void entry_point(void)
{
    xky_id_t my_id, other_id;
    xky_i32_t ret_code;

    my_id = xky_syscall_get_partition_id(NULL);
    other_id = "partition_1";

    /* Try to access data of other partition, get XKY_UNAUTHORIZED return code*/
    ret_code = xky_syscall_get_partition_id(other_id);
    xky_printf("\nPartition_%i: Tried to access other partition (name: %s). Return code was %i\n", my_id, other_id, ret_code);
}
