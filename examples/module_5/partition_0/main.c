/**
 * @file
 * @brief Partition 0 example code
 */

#include <xky.h>
#include <bare.h>
#include <string.h>
#include <xky_printf.h>

void entry_point(void) {

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

    while (1) {

        /* send more messages than the allowed by the port */
        for (i = 0; i < port_status.configuration.max_nb_message + 1; ++i) {

            char buffer[16] = { 0 };
            xky_snprintf(buffer, sizeof(buffer), "Message %i", i);
            xky_printf("  Partition %i: sending '%s' (%i)\n",
                    my_id, buffer,
                    xky_syscall_write_port(port_id, buffer, strlen(buffer)));
        }

        bare_wake_in_next_mtf();

        /* send a message that will overflow the message buffer on the other side */
        char message[] = "Lorem ipsum dolor sit amet amet.";
        xky_printf("  Partition %i: sending '%s' (%i)\n",
                my_id, message,
                xky_syscall_write_port(port_id, message, strlen(message)));


        bare_wake_in_next_mtf();

        /* flush all messages in channel */
        xky_syscall_flush_port(port_id);
    }

    /* this code will never execute */
    xky_printf("  Partition %i: I shouldn't be running\n", my_id);
}
