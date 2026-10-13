/* func_020877ac @ 0x020877ac, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char func_020877dc(void *base, int key, int param);

void func_020877ac(unsigned char *base, int start, int end)
{
    int key = 0xca4;
    int i;
    for (i = start; i < end; i++) {
        *(base + i + 0xa) = func_020877dc(base, key, 0x29);
        key -= 0x66;
    }
}
