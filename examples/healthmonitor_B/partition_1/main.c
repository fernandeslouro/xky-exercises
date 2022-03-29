/* TEST ERROR HANDLING AT PARTITION LEVEL*/

#include <xky.h>
#include <xky_printf.h>

void test_entry(void) {

    xky_partition_status_t p_status;

    xky_syscall_get_partition_status(-1, &p_status);

    if (p_status.restarts == 0) {
    
        xky_printf("Hello! I am partition_1\n");
        xky_printf("system state %d\n", xky_syscall_get_system_state());

        // System state 3 - PARTITION INITIALIZATION
        // xky_printf("Raising an error.....\n");
        // xky_syscall_raise_health_monitor_event(1);

        // System state 4 -  PARTITION EXECUTION
        // xky_syscall_set_partition_mode(-1, XKY_MODE_NORMAL);
        // xky_printf("system state %d\n", xky_syscall_get_system_state());
        // xky_printf("Raising an error.....\n");
        // xky_syscall_raise_health_monitor_event(1);

        // System state 5 - PARTITION HEALTHMONITOR
        // xky_syscall_raise_health_monitor_event(0); //default IGNORE
        // xky_printf("system state %d\n", xky_syscall_get_system_state());
        // xky_syscall_raise_health_monitor_event(1);
    
    }
    else {
        xky_printf("Hi, hello again! I am partition_1\n");
        xky_printf("Mode %d\n", p_status.mode);
    }

    
}
