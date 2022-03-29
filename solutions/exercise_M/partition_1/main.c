/**
 * @file
 * @brief Partition 1 example code
 */

#include <xky.h>
#include <bare.h>
#include <xky_printf.h>

xky_id_t my_id;

void timer_handler(void *isf, xky_i32_t irq) {

    switch (irq) {

        case XKY_IRQ_TIMER_0:
            xky_printf("  Partition %i: timer 0 expired (%lli)!\n", my_id, xky_syscall_get_elapsed_time(XKY_TIME_TYPE_GLOBAL));
            break;
        case XKY_IRQ_TIMER_1:
            xky_printf("  Partition %i: timer 1 expired (%lli)!\n", my_id, xky_syscall_get_elapsed_time(XKY_TIME_TYPE_GLOBAL));
            break;
        case XKY_IRQ_TIMER_2:
            xky_printf("  expired\n");
            break;
        case XKY_IRQ_TIMER_3:
            xky_printf("  expired\n");
            break;
    }
}


void entry_point(void) {

    /* get my partition identifier */
    my_id = xky_syscall_get_partition_id(NULL);

    xky_printf("  Partition_%i:\n", my_id);
    xky_printf("    set timer 0 to expire in 2 seconds\n");
    xky_printf("    set timer 1 to expire in 4 seconds\n");
    xky_printf("    NOTE: these timers only count during partition execution time\n");

    /* start timer0 and timer1 */
    xky_syscall_start_timer(0, xky_syscall_get_timer_tps(0) * 2);
    xky_syscall_start_timer(1, xky_syscall_get_timer_tps(1) * 4);

    /* enable timer0, timer1, timer2 and timer3 handler */
    bare_isr_install_handler(XKY_IRQ_TIMER_0, timer_handler);
    bare_isr_install_handler(XKY_IRQ_TIMER_1, timer_handler);
    bare_isr_install_handler(XKY_IRQ_TIMER_2, timer_handler);
    bare_isr_install_handler(XKY_IRQ_TIMER_3, timer_handler);

    /* note that event with handlers set, timer 2 & 3 will not expired in this partition */

    while (1) {

        /*
         * loop could be doing some other work, the behavior of module_1 is now
         * happening on new window event handler
         */
    }

    /* this code will never execute */
    xky_printf("  Partition %i: I shouldn't be running\n", my_id);
}
