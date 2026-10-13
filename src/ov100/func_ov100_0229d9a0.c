/* func_ov100_0229d9a0 @ 0x0229d9a0, 0x20 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208e18(void *ptr);
extern void func_ov100_0229c970(void *ptr);

void func_ov100_0229d9a0(void *ptr)
{
    if (func_ov002_02208e18((char *) ptr + 0x22d8)) {
        func_ov100_0229c970(ptr);
    }
}
