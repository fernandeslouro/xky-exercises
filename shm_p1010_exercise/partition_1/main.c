/**
 * @file
 * @brief Partition 1 example code
 */

#include <xky.h>
#include <bare.h>
#include <xky_printf.h>

char memory_names[][32] = {
    "shm_mem",
    "mem_code",
    "mem_data"};

#define SIZE 3

xky_u32_t *shm_value;

void memory_permissions(xky_u32_t permissions)
{

    if (permissions == (XKY_MEMORY_PERMISSIONS_READ | XKY_MEMORY_PERMISSIONS_WRITE))
    {
        xky_printf("          memory permissions - read and write\n");
    }
    else if (permissions == XKY_MEMORY_PERMISSIONS_READ)
    {
        xky_printf("          memory permissions - read\n");
    }
    else if (permissions == XKY_MEMORY_PERMISSIONS_WRITE)
    {
        xky_printf("          memory permissions - write\n");
    }
    else
    {
        xky_printf("          memory permissions - executable\n");
    }
}

void memory_cache_attribute(xky_u32_t cache_attribute)
{

    if (cache_attribute == XKY_CACHE_ATTRIBUTE_INHIBIT)
    {
        xky_printf("      memory cache attribute - inhibit\n");
    }
    else if (cache_attribute == XKY_CACHE_ATTRIBUTE_DEVICE)
    {
        xky_printf("      memory cache attribute - device\n");
    }
    else if (cache_attribute == XKY_CACHE_ATTRIBUTE_COPY_BACK)
    {
        xky_printf("      memory cache attribute - copy back\n");
    }
    else
    {
        xky_printf("      memory cache attribute - write through\n");
    }
}

void test_entry(void)
{

    xky_u32_t i;
    xky_id_t my_id;
    xky_id_t mem_id[SIZE];
    xky_uptr_t address;
    xky_memory_status_t mem_status;

    my_id = xky_syscall_get_partition_id(NULL);
    xky_printf("  Partition_%i:\n", my_id);

    /* get all memory status */
    for (i = 0; i < SIZE; ++i)
    {
        mem_id[i] = xky_syscall_get_memory_id(memory_names[i]);
        xky_syscall_get_memory_status(mem_id[i], &mem_status);

        /* present results */
        xky_printf("            %s id: %i\n", memory_names[i], mem_id[i]);
        xky_printf(
            "        memory block address - 0x%p\n"
            "           memory block size - 0x%p\n",
            mem_status.address,
            mem_status.size);

        memory_permissions(mem_status.permissions);
        memory_cache_attribute(mem_status.cache_attr);
        xky_printf("\n");

        if (i == 0)
        {
            address = mem_status.address;
        }
    }

    bare_wake_in_next_mtf();

    /* read from shared memory */
    for (i = 0; i < 10; ++i)
    {

        // Read from shared memory and save value to shm_value
        // Add code here

        xky_printf("  Partition_%i: read from %s: %d\n", my_id, memory_names[0], *shm_value);
        bare_wake_in_next_mtf();
    }

    /* write to shared memory */
    for (i = 10; i < 20; ++i)
    {

        // Write i value to shared memory
        // Add code here

        xky_printf("  Partition_%i: write to %s: %d\n", my_id, memory_names[0], *shm_value);
        bare_wake_in_next_mtf();
    }

    while (1)
    {
    }

    /* this code will never execute */
    xky_printf("  Partition %i: I shouldn't be running\n", my_id);
}
