/**
 * @file
 * @brief Partition 1 example code
 */

#include <xky.h>
#include <bare.h>
#include <xky_printf.h>

void entry_point(void)
{

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
        "                  Port id: %i\n"
        "              Port status:\n"
        "                    Type - %i\n"
        "               Direction - %i\n"
        "       Max. Message size - %i\n"
        "          Refresh Period - %lli\n"
        "       Messages in queue - %i\n\n",
        port_id,
        port_status.type,
        port_status.configuration.direction,
        port_status.configuration.max_message_size,
        port_status.configuration.refresh_period,
        port_status.nb_message);

    char buffer[32] = {0};

    // Recieve several messages
    for (i = 0; i < 8; ++i)
    {
        // Recieve message and save size as m_size
        // Add code here

        if (m_size > 0)
        {
            xky_printf("  Partition %i: received '%s' (%i) (%lli)\n", my_id, buffer, m_size, m_time);
        }
        else
        {
            xky_printf("  Partition %i: port is empty\n", my_id);
        }
    }

    bare_wake_in_next_mtf();
    bare_wake_in_next_mtf();
    bare_wake_in_next_mtf();

    // Recieve message that was stalled and save size as m_size
    // Add code here

    if (m_size > 0)
    {
        xky_printf("  Partition %i: received '%s'", my_id, buffer);
        if ((m_status & XKY_MESSAGE_STATUS_INVALID) != 0)
        {
            xky_printf(" (invalid message)");
        }
        xky_printf("\n");
    }

    bare_wake_in_next_mtf();
}
