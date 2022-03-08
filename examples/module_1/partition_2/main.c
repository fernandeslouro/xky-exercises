/**
 * @file
 * @brief Partition 2 example code
 */

#include <xky.h>
#include <bare.h>
#include <xky_printf.h>

void entry_point(void) {

    xky_id_t my_id;
    xky_id_t schedule_id;

    /* get my partition identifier */
    my_id = xky_syscall_get_partition_id(NULL);

    while (1) {

        /* get current schedule identifier */
        schedule_id = xky_syscall_get_schedule_id(NULL);
        xky_printf("  Partition %i: running on schedule %i\n", my_id, schedule_id);

        /* code could behave differently depending on the schedule id */

        /* wake in the next MTF */
        bare_wake_in_next_mtf();
    }

    /* this code will never execute */
    xky_printf("  Partition %i: I shouldn't be running\n", my_id);
}
