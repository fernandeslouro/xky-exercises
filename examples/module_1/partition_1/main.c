/**
 * @file
 * @brief Partition 1 example code
 */

#include <xky.h>
#include <bare.h>
#include <xky_printf.h>

void entry_point(void) {

    xky_i32_t rc = -1;
    xky_id_t my_id;
    xky_id_t schedule_id;

    /* get my partition identifier */
    my_id = xky_syscall_get_partition_id(NULL);

    /* get current schedule identifier */
    schedule_id = xky_syscall_get_schedule_id(NULL);
    xky_printf("  Partition %i: running on schedule %i\n", my_id, schedule_id);

    /* attempt to change schedule to schedule_1*/
    schedule_id =  xky_syscall_get_schedule_id("schedule_1");
    rc = xky_syscall_set_schedule(schedule_id);
    if (rc != XKY_SUCCESS) {
        xky_printf("  Partition %i: insufficient permissions to change the schedule\n", my_id);
    }

    /* wake in the next MTF */
    bare_wake_in_next_mtf();

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
