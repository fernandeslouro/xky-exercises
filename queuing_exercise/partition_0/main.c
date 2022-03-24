/**
 * @file
 * @brief Partition 0 example code
 */

#include <xky.h>
#include <bare.h>
#include <string.h>
#include <xky_printf.h>

void entry_point(void)
{

    xky_u32_t i;
    xky_id_t my_id, port_id;
    xky_port_status_t port_status;

    my_id = xky_syscall_get_partition_id(NULL);
    xky_printf("  Partition_%i:\n", my_id);
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

    for (i = 0; i < port_status.configuration.max_nb_message - 1; ++i)
    {

        char buffer[16] = {0};
        xky_snprintf(buffer, sizeof(buffer), "Message %i", i);
        xky_printf("  Partition %i: sending '%s'\n", my_id, buffer);

        // Write buffer message to port_id port
        // Add code here
    }

    bare_wake_in_next_mtf();

    char message[] = "Small message";
    xky_printf("  Partition %i: sending '%s'\n", my_id, message);

    // Write buffer message to port_id port
    // Add code here

    bare_wake_in_next_mtf();

    // flush all messages in channel
    // Add code here
}
