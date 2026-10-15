/* func_ov103_0229cd4c @ 0x0229cd4c, 0x4c bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov103_0229cc08(void *arg0, void *arg1);
extern int func_ov103_0229cce8(int a, int b);
extern int func_02066830(int a, int b);
extern void func_ov103_0229cd1c(int a, int b, int c);
extern void func_ov103_0229c8e8(int a, int b);

int func_ov103_0229cd4c(int a, int b)
{
    int r5 = a;
    int r4 = b;
    if (func_ov103_0229cc08((void *) a, (void *) b) == 0) {
        int r1 = func_ov103_0229cce8(r5, r4);
        func_02066830(r5 + 0x2ca0, r1);
        func_ov103_0229cd1c(r5, *(unsigned char *) (r5 + 0x2da3), r5 + 0x2ca0);
    }
    func_ov103_0229c8e8(r5, r4);
    return 1;
}
