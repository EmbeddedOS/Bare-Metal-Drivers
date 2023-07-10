# simply scheduler project

- Install OpenOCD:

```bash
sudo apt-get -y install openocd
sudo apt-get install gdb-arm-none-eabi
```

- When we run the OpenOCD server. Now u can connect to this server over various client programs such as telnet client, GDB clients, etc.

- Run gdb:

```bash
gdb-multiarch # in window u need to run: arm-none-eabi-gdb instead.
target remote localhost:3333
```

- On OpenOCD log look like:

```text
Info : accepting 'gdb' connection on tcp/3333
```

- Reset monitor (this is OpenOCD general commands):

```gdb
monitor reset init
```

- And finally flash to board (this is OpenOCD general commands):

```gdb
monitor flash write_image erase final.elf
```

- Reset board and pause:

```gdb
monitor reset halt
```

- Resume the program:

```gdb
monitor resume
```

- Stop the program:

```gdb
monitor halt
```

- Reset board:

```gdb
monitor reset
```

- verify some memory location:
  - Via the memory map file, we can get store address of some variable, for example:

  ```text
   *(.data)
  .data          0x0000000020000000       0x54 main.o
                  0x0000000020000000                current_task
  ```

  - from that, u can get memory address value with `mdw`:

    ```gdb
    monitor mdw  0x20000000 4
    ```

    - Output look like:

    ```text
    monitor mdw  0x20000000 4
    0x20000000: 8000f8d0 0f00f1b8 6847d01b d0f74547
    ```

- Set break point, for example, we need to trace function `task_2_handler` is called, first u need to check address of it in memory map file:

  ```text
                  0x000000000800045a                task_1_handler
  ```

  - Set break point at address:

  ```gdb
  monitor bp 0x0800045a 2 hw
  ```

- Instead GDB client, u also can use the telnet client to connect to OpenOCD server:

```bash
telnet localhost 6666
```
