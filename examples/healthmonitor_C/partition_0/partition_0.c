#include <xky.h>
#include <xky_printf.h>

typedef void (*funct_ptr)(void);

void test_entry(void) {

    xky_i32_t rc = -1;
    xky_uptr_t address;
    xky_u32_t *data_mem_ptr;
    xky_partition_status_t p_status;

    xky_syscall_get_partition_status(-1, &p_status);

    switch (p_status.restarts) {

        case 0:

            xky_printf("Hello, how are you?\n");

            /* attempt to directly execute a memory region outside the accessible memory space */
            address = 0x6000000;
            funct_ptr func = (funct_ptr)&address;
            func();

        case 1:

            xky_printf("Hi, hello again!\n");         
            xky_printf("Mode %d - number of restarts %d\n", p_status.mode, p_status.restarts);

            /* attempt to directly access a memory address outside the accessible memoy space */
            data_mem_ptr = (xky_u32_t *)(0x5000000);
            rc = *data_mem_ptr;

        case 2:

            xky_printf("It is me again!\n");             
            xky_printf("Mode %d - number of restarts %d\n", p_status.mode, p_status.restarts);
            break;

        default:
            break;
    }
}