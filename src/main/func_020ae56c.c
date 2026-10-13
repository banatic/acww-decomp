/* func_020ae56c @ 0x020ae56c, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209f128(void *param1, int param2);

extern unsigned char data_021dc7a8[];

void func_020ae56c(void *param0)
{
    signed char c;
    void *addr;

    c = *(signed char *) ((char *) param0 + 4);
    if (c != -1) {
        addr = (void *) data_021dc7a8;
        func_0209f128(addr, 8);
    }
}
