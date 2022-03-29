/**
 * @file
 * @brief Partition 0 example code
 */

#include <xky.h>
#include <bare.h>
#include <xky_printf.h>

void entry_point(void)
{

    xky_i32_t rc = -1;
    xky_id_t my_id, other_id;
    xky_partition_status_t my_status, other_status;

    /* get my current identifier and status */
    my_id = xky_syscall_get_partition_id(NULL);
    xky_syscall_get_partition_status(-1, &my_status);

    /* present results */
    xky_printf("  Partition_%i:\n", my_id);
    xky_printf("          My partition id: %i\n", my_id);
    xky_printf(
        "      My partition status:\n"
        "         number of ports - %i\n"
        "          memory regions - %i\n"
        "      number of restarts - %i\n"
        "          operation mode - %i\n"
        "         start condition - %i\n",
        my_status.ports,
        my_status.memory_regions,
        my_status.restarts,
        my_status.mode,
        my_status.start_condition);

    bare_wake_in_next_mtf();

    /* get other partition identifier and status */
    other_id = xky_syscall_get_partition_id("partition_1");

    if (other_id < 0)
    {
        xky_printf("  Partition_%i: insufficient permissions to access other partition data\n", my_id);
    }
    else
    {
        xky_syscall_get_partition_status(other_id, &other_status);

        xky_printf("  Partition_%i:\n", my_id);
        xky_printf("       Other partition id: %i\n", other_id);
        xky_printf(
            "   Other partition status:\n"
            "         number of ports - %i\n"
            "          memory regions - %i\n"
            "      number of restarts - %i\n"
            "          operation mode - %i\n"
            "         start condition - %i\n",
            other_status.ports,
            other_status.memory_regions,
            other_status.restarts,
            other_status.mode,
            other_status.start_condition);
    }

    bare_wake_in_next_mtf();

    /* set other partition mode mode */
    xky_printf("  Partition_%i: setting other partition (Partition_%i) mode to idle...\n", my_id, other_id);
    rc = xky_syscall_set_partition_mode(other_id, XKY_MODE_IDLE);
    if (rc != XKY_SUCCESS)
    {
        xky_printf("  Partition_%i: insufficient permissions to set other partition mode\n", my_id);
    }
    else
    {
        /* get other partition identifier and status */
        xky_syscall_get_partition_status(other_id, &other_status);
        xky_printf("  Partition_%i:\n", my_id);
        xky_printf("       Other partition id: %i\n", other_id);
        xky_printf(
            "   Other partition status:\n"
            "         number of ports - %i\n"
            "          memory regions - %i\n"
            "      number of restarts - %i\n"
            "          operation mode - %i\n"
            "         start condition - %i\n",
            other_status.ports,
            other_status.memory_regions,
            other_status.restarts,
            other_status.mode,
            other_status.start_condition);
    }

    /* set my mode */
    xky_printf("  Partition_%i: setting my partition mode to idle...\n", my_id);
    xky_syscall_set_partition_mode(-1, XKY_MODE_IDLE);

    /* this code will never execute */
    xky_printf("  Partition_%i: I shouldn't be running\n", my_id);
}
