/* func_020a7330 @ 0x020a7330, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f4320[];
extern void func_020a7738(const unsigned char *a, unsigned char *b, unsigned char *c, unsigned char *d);

int func_020a7330(int arg0)
{
    unsigned char buffer[3];
    if (arg0 < 4) {
        func_020a7738(data_021f4320 + 3 * arg0, &buffer[0], &buffer[1], &buffer[2]);
        return buffer[0];
    }
    return 0x3f;
}
