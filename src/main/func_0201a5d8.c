/* func_0201a5d8 @ 0x0201a5d8, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020044b0(void *param1, int param2, int param3, int param4);

void func_0201a5d8(void *param0)
{
    unsigned char *ptr;
    unsigned char val;
    void *base;

    ptr = (unsigned char *) param0;
    if (ptr[0x24] == 1) {
        if (ptr[0x26] == 0) {
            base = *(void **) (ptr + 0x18);
            val = ptr[0x25];
            func_020044b0(base, val + 0x84, 0x7f, 0);
        }
    }
}
