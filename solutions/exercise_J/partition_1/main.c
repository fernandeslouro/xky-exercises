/**
 * @file
 * @brief Partition 1 example code
 */

#include <xky.h>
#include <bare.h>
#include <xky_printf.h>

void entry_point(void)
{

    xky_i32_t rc = -1;
    xky_id_t my_id;
    xky_id_t schedule_id;

    while (1)
    {
        /* get my partition identifier */
        my_id = xky_syscall_get_partition_id(NULL);

        /* get current schedule identifier */
        schedule_id = xky_syscall_get_schedule_id(NULL);
        xky_printf("  Partition %i: running on schedule %i\n", my_id, schedule_id);

        /* wake in the next MTF */
        bare_wake_in_next_mtf();
    }

    /* this code will never execute */
    xky_printf("  Partition %i: I shouldn't be running\n", my_id);
}
