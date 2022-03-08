/**
 * @file
 * @brief Partition 0 example code
 */

#include <xky.h>
#include <bare.h>
#include <xky_printf.h>

xky_id_t my_id;

char schedule_names[][32] = {
        "schedule_0",
        "schedule_1"
};

#define SIZE                        (sizeof(schedule_names) / sizeof(schedule_names[0]))

xky_u32_t count = 0;
xky_u32_t current_idx = 0;
xky_id_t schedules_id[SIZE];

void new_mtf_handler(void *isf, xky_i32_t irq) {

    xky_i32_t rc = -1;
    xky_id_t schedule_id;
    xky_schedule_status_t schedule_status;

    /* get current schedule identifier */
        schedule_id = xky_syscall_get_schedule_id(NULL);
        xky_printf("  Partition %i: running on schedule %i\n", my_id, schedule_id);

    /* 1st MTF */
    if (count == 0) {
        /* get schedule status */
        xky_syscall_get_schedule_status(&schedule_status);

        current_idx = (current_idx + 1) % SIZE;
        xky_printf("  Partition %i: changing to schedule %i in %lli s\n",
                my_id, schedules_id[current_idx], 2 * (schedule_status.partition_period / 1000000000));

        ++count;

    /* 2nd MTF */
    } else {
        /* change schedule */
        rc = xky_syscall_set_schedule(schedules_id[current_idx]);
        if (rc != XKY_SUCCESS) {
            xky_printf("  Partition %i: insufficient permissions to change the schedule\n", my_id);
        }

        /* note: change occurs only at the end of the current MTF */
        count = 0;
    }
}


void entry_point(void) {

    /* get my partition identifier */
    my_id = xky_syscall_get_partition_id(NULL);

    xky_printf("  Partition_%i:\n", my_id);

    /* get schedules identifiers */
    xky_u32_t i;
    current_idx = 0;
    for (i = 0; i < SIZE; ++i) {
        schedules_id[i] = xky_syscall_get_schedule_id(schedule_names[i]);
        xky_printf("       %s identifier is %i", schedule_names[i], schedules_id[i]);

        /* get the current schedule */
        if (schedules_id[i] == xky_syscall_get_schedule_id(NULL)) {
            xky_printf(" (current schedule)");
            current_idx = i;
        }
        xky_printf("\n");
    }

    /* enable major time frame IRQ */
    bare_isr_install_handler(XKY_IRQ_NEW_MTF, new_mtf_handler);

    while (1) {

        /*
         * loop could be doing some other work, the behavior of module_1 is now
         * happening on new window event handler
         */
    }

    /* this code will never execute */
    xky_printf("  Partition %i: I shouldn't be running\n", my_id);
}
