/**
 * @file
 * @brief Partition 2 example code
 */

#include <xky.h>
#include <bare.h>
#include <xky_printf.h>

xky_u32_t i = 0;
xky_id_t my_id;
char buffer[128];

void port_activity(void) {
    i = i+1;
    if (i > 0) {
        xky_printf("  Partition %i: port activity event occur: %i\n", my_id, i);
    }
}

void test_entry(void) {

    xky_u32_t j = 0;
    xky_id_t port_id;
    xky_sz_t length;
    xky_u32_t message_status;
    xky_time_t time_stamp;

    my_id = xky_syscall_get_partition_id(NULL);
    port_id = xky_syscall_get_port_id("port_0");

    /* enable port activity IRQ */
    bare_isr_install_handler(XKY_IRQ_PORT_ACTIVITY, (bare_isr_handler_f)port_activity);

    while (1) {
        for (j = 0; j < 10; ++j) {
            /* read message "message j" */
            length = xky_syscall_read_port(port_id, buffer, &time_stamp, &message_status);

            if (length > 0) {
                    xky_printf("  Partition %i: received '%s' (%i) (%lli)\n", my_id, buffer, length, time_stamp);

                } else {
                    xky_printf("  Partition %i: port is empty\n", my_id);
                }
            bare_wake_in_next_mtf();
        }
    }

    /* this code will never execute */
    xky_printf("  Partition %i: I shouldn't be running\n", my_id);
}
