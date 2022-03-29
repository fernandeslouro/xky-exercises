This repo contains the exercises provided during the XKY course, with their respective solutions.

Short description of the exercises:
 * A - Run a precompiled application on a board
 * B - Compile an application, move to TFTP server, see board output
 * C - Run using the script
 * D - Create simple app from boilerplate code
 * E - Add a second partition, while loop
 * F - Partition id from code
 * G - Add another partition and change schedule 
 * H - Using bare functions (bare_wake_in_next_mtf)
 * I - Partition id and status (module_0)
 * J - Schedule id and status (module_1)
 * K - Changing previous example to use events (module_2)
 * L - Elapsed time (module_4)
 * M - Timers (module_3)
 * N - Queuing ports (module_5)
 * O - Sampling ports (module_6)
 * P - Shared memories (module_7)
 * Q - Events (module_8)

In the `examples` folder:
 * bare_c - simple application printing ASCII art
 * demo_kickoff - slightly more complex application printing ASCII art
 * healthmonitor_A - demo highlighting module level healthmonitor handling
 * healthmonitor_B - demo highlighting parition level healthmonitor handling
 * healthmonitor_C - healthmonitor handling example with a memory error (instead of a healthmonitor event called by libxky)
