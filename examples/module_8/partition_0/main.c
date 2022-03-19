/**
 * @file
 * @brief Partition 0 example code
 */

#include <xky.h>
#include <bare.h>
#include <xky_printf.h>

char buffer[256];

void test_entry(void)
{

    xky_u32_t j;
    xky_id_t my_id, port_id;
    xky_sz_t length;

    my_id = xky_syscall_get_partition_id(NULL);
    port_id = xky_syscall_get_port_id("port_0");

    while (1)
    {
        for (j = 0; j < 10; ++j)
        {
            /* write message "message j" */
            length = xky_snprintf(buffer, sizeof(buffer), "message %i", j);

            xky_printf("  Partition %i: sending '%s' (%i)\n",
                       my_id, buffer, xky_syscall_write_port(port_id, buffer, length));

            bare_wake_in_next_mtf();
        }
    }

    /* this code will never execute */
    xky_printf("  Partition %i: I shouldn't be running\n", my_id);
}
