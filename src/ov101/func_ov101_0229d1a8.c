/* func_ov101_0229d1a8 @ 0x0229d1a8, 0x48 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov101_0229c90c(int, unsigned char);
extern void func_ov101_0229c29c(int, int);
extern void func_ov101_0229ca58(int);
extern void func_ov002_02208098(int, int);
extern int func_ov002_02209f70(int);

void func_ov101_0229d1a8(int r0)
{
    if (func_ov002_02209f70(r0 + 0x229c) == 0) {
        func_ov101_0229c90c(r0, *(unsigned char *) (r0 + 0xb5));
        func_ov101_0229c29c(r0, 0x20);
        func_ov002_02208098(r0, 0x11);
        func_ov101_0229ca58(r0);
    } else {
        func_ov002_02208098(r0, 6);
    }
}
