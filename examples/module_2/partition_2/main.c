/**
 * @file
 * @brief Partition 2 example code
 */

#include <xky.h>
#include <bare.h>
#include <xky_printf.h>

xky_id_t my_id;

void new_window_event_handler(void *isf, xky_i32_t irq_n) {

    xky_id_t schedule_id = xky_syscall_get_schedule_id(NULL);
    xky_printf("  Partition %i: running on schedule %i\n", my_id, schedule_id);
}

void entry_point(void) {

    /* get my partition identifier */
    my_id = xky_syscall_get_partition_id(NULL);

    /* enable new window IRQ */
    bare_isr_install_handler(XKY_IRQ_NEW_WINDOW, new_window_event_handler);

    while (1) {

        /*
         * loop could be doing some other work, the behavior of module_1 is now
         * happening on new window event handler
         */
    }

    /* this code will never execute */
    xky_printf("  Partition %i: I shouldn't be running\n", my_id);
}
