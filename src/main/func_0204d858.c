/* func_0204d858 @ 0x0204d858, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short *func_020e9968(int, unsigned int, int);

unsigned short *func_0204d858(int heapID, int align)
{
    unsigned short *buf;
    int i;

    buf = func_020e9968(heapID, 0x200, align);
    if (buf) {
        for (i = 0; i < 0x100; i++) {
            buf[i] = 0xfff1;
        }
    }
    return buf;
}
