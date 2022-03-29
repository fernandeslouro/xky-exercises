/**
 * @file
 * @brief Partition 0 example code
 */

#include <xky.h>
#include <bare.h>
#include <xky_printf.h>

char schedule_names[][32] = {
    "schedule_0",
    "schedule_1"};

#define SIZE (sizeof(schedule_names) / sizeof(schedule_names[0]))

void entry_point(void)
{

    xky_i32_t rc = -1;
    xky_u32_t i;
    xky_u32_t current_idx = 0;
    xky_id_t my_id;
    xky_id_t schedules_id[SIZE];
    xky_id_t schedule_id;
    xky_schedule_status_t schedule_status;

    /* get my partition identifier */
    my_id = xky_syscall_get_partition_id(NULL);

    xky_printf("  Partition_%i:\n", my_id);

    /* get schedules identifiers */
    for (i = 0; i < SIZE; ++i)
    {
        schedules_id[i] = xky_syscall_get_schedule_id(schedule_names[i]);
        xky_printf("       %s identifier is %i", schedule_names[i], schedules_id[i]);

        /* get the current schedule */
        if (schedules_id[i] == xky_syscall_get_schedule_id(NULL))
        {
            xky_printf(" (current schedule)");
            current_idx = i;
        }
        xky_printf("\n");
    }

    while (1)
    {

        /* get current schedule identifier */
        schedule_id = xky_syscall_get_schedule_id(NULL);
        xky_printf("  Partition %i: running on schedule %i\n", my_id, schedule_id);

        /* get schedule status */
        xky_syscall_get_schedule_status(&schedule_status);

        current_idx = (current_idx + 1) % SIZE;
        /* xky_printf("  Partition %i: changing to schedule %i in %lli s\n",
                my_id, schedules_id[current_idx], 2 * (schedule_status.partition_period / 1000000000));*/

        /* wake in the next MTF */
        bare_wake_in_next_mtf();

        /* get current schedule identifier */
        schedule_id = xky_syscall_get_schedule_id(NULL);
        xky_printf("  Partition %i: running on schedule %i\n", my_id, schedule_id);

        /* change schedule */
        rc = xky_syscall_set_schedule(schedules_id[current_idx]);
        if (rc != XKY_SUCCESS)
        {
            xky_printf("  Partition %i: insufficient permissions to change the schedule\n", my_id);
        }

        /* note: change occurs only at the end of the current MTF */
        bare_wake_in_next_mtf();
    }

    /* this code will never execute */
    xky_printf("  Partition %i: I shouldn't be running\n", my_id);
}
