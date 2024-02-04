
## BadOS

This is a 32 bit OS that was created to render Bad Apple. It shouldn't be used as some kind of tutorial on how to build a OS.

To build the OS, I used some resources available at this [repository](https://github.com/cfenollosa/os-tutorial) and at [OSDev.org](https://wiki.osdev.org)

### Building and running

Requirements

- Python 3 or higher
- FFMPEG
- OpenCV (Only required for preview) 
- Numpy (Only required for preview)
- Make
- GCC
- LD
- QEMU

#### Generate the video binary

1. Download the Bad Apple video
2. Save it as `resources/private/source.mp4`
3. Run `$ make setup`

- To preview the generated video, run `$ make py-preview`

#### Running the OS

1. Run `$ make play`
2. If you see the message `--Type <RET> for more, q to quit, c to continue without paging--`, hit <kbd>C</kbd> and hit <kbd>ENTER</kbd>
3. GBD will show you the message `Restoring binary file resources/private/video.bin into memory (0xfff000 to 0x...)` after that, you will see `(gdb)` on the terminal
4. run `(gdb) continue`