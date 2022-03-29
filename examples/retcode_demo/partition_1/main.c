#include <xky_printf.h>
#include <xky.h>

void entry_point(void)
{
    xky_id_t my_id, other_id, invalid_id;
    xky_i32_t ret_code;

    my_id = xky_syscall_get_partition_id(NULL);
    other_id = "partition_0";
    invalid_id = "partition_123";

    /* Try to access data of other partition, get the partition identifier
        (0) as return code*/
    ret_code = xky_syscall_get_partition_id(other_id);
    xky_printf("Partition_%i: Tried to access other partition (name: %s). Return code was %i\n",
               my_id, other_id, ret_code);

    /* Try to invalid partition name, get XKY_INVALID return code*/
    ret_code = xky_syscall_get_partition_id(invalid_id);
    xky_printf("Partition_%i: Tried to access an invalid partition (name: %s). Return code was %i\n",
               my_id, invalid_id, ret_code);
}
