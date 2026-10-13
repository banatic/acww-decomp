/* func_020b488c @ 0x020b488c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b4950_unk(unsigned char *buf, int a, int count);

void func_020b488c(unsigned char *buf, int a, int count)
{
    int i;
    i = func_020b4950_unk(buf, a, count);
    count = count << 1;
    while (i < count) {
        buf[i] = 0;
        buf[i + 1] = 32;
        i += 2;
    }
}
