/* func_020b0fc8 @ 0x020b0fc8, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b0ffc(int a, unsigned short b, int c);

void func_020b0fc8(int param0, char *param1, int param2)
{
    int i;
    unsigned short value;

    for (i = 0; i < 16; i++) {
        value = *(unsigned short *) (param1 + (i << 1) + 0x2a);
        if (value != 0xFFFF) {
            func_020b0ffc(param0, value, param2);
        }
    }
}
