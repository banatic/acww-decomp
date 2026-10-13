/* func_ov101_0229d088 @ 0x0229d088, 0x20 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208e18(void *addr);
extern void func_ov101_0229c5b8(void *addr);

void func_ov101_0229d088(void *obj)
{
    if (func_ov002_02208e18((char *) obj + 0x2300) != 0) {
        func_ov101_0229c5b8(obj);
    }
}
