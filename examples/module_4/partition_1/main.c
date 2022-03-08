/**
 * @file
 * @brief Partition 1 example code
 */

#include <xky.h>
#include <bare.h>
#include <xky_printf.h>

void entry_point(void) {

    xky_id_t my_id = xky_syscall_get_partition_id(NULL);

    while (1)  {
        xky_printf(
                "  Partition %i: time (local: %lli; global: %lli)\n",  my_id,
                xky_syscall_get_elapsed_time(XKY_TIME_TYPE_LOCAL),
                xky_syscall_get_elapsed_time(XKY_TIME_TYPE_GLOBAL));
        bare_wake_in_next_mtf();
    }

    /* this code will never execute */
    xky_printf("  Partition %i: I shouldn't be running\n", my_id);
}
