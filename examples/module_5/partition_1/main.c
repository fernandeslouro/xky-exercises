/**
 * @file
 * @brief Partition 1 example code
 */

#include <xky.h>
#include <bare.h>
#include <xky_printf.h>

void entry_point(void) {

    xky_sz_t m_size;
    xky_time_t m_time;
    xky_u32_t i, m_status;
    xky_id_t my_id, port_id;
    xky_port_status_t port_status;

    my_id = xky_syscall_get_partition_id(NULL);
    xky_printf("\n  Partition_%i:\n", my_id);
    port_id = xky_syscall_get_port_id("port_0");
    xky_syscall_get_port_status(port_id, &port_status);

    xky_printf(
            "                   Port id: %i\n"
            "               Port status:\n"
            "                     Type - %i\n"
            "                Direction - %i\n"
            "  Max. Number of Messages - %i\n"
            "        Max. Message size - %i\n"
            "           Refresh Period - %lli\n"
            "        Messages in queue - %i\n\n",
            port_id,
            port_status.type,
            port_status.configuration.direction,
            port_status.configuration.max_nb_message,
            port_status.configuration.max_message_size,
            port_status.configuration.refresh_period,
            port_status.nb_message);


    while (1) {

        char buffer[32] = { 0 };

        /* send more messages than the allowed by the port */
        for (i = 0; i < port_status.configuration.max_nb_message + 1; ++i) {

            m_size = xky_syscall_read_port(port_id, buffer, &m_time, &m_status);
            if (m_size > 0) {
                xky_printf("  Partition %i: received '%s' (%i) (%lli)", my_id, buffer, m_size, m_time);
                if ((m_status & XKY_MESSAGE_STATUS_QUEUE_OVERFLOW) != 0) {
                    xky_printf(" (queue was overflowed)");
                }
                xky_printf("\n");

            } else {

                xky_printf("  Partition %i: port is empty\n", my_id);
            }
        }

        bare_wake_in_next_mtf();

        /* receive message that overflowed the maximum message size */
        m_size = xky_syscall_read_port(port_id, buffer, &m_time, &m_status);
        if (m_size > 0) {
            xky_printf("  Partition %i: received '%s' (%i) (%lli)", my_id, buffer, m_size, m_time);
            if ((m_status & XKY_MESSAGE_STATUS_SIZE_OVERFLOW) != 0) {
                xky_printf(" (message size overflowed)");
            }
            xky_printf("\n");
        }

        bare_wake_in_next_mtf();
    }

    /* this code will never execute */
    xky_printf("  Partition %i: I shouldn't be running\n", my_id);
}
