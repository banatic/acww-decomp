/* func_ov096_0229f4ac @ 0x0229f4ac, 0x4c bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_0229f150(void *object, void *value);
extern int func_ov096_0229f054(int, int);
extern int func_02066830(int, int);
extern void func_ov096_0229f47c(int, int, int);
extern void func_ov096_0229e898(int, int, int);

int func_ov096_0229f4ac(int a, int b)
{
    int r5 = a;
    int r4 = b;
    if (func_ov096_0229f150((void *) a, (void *) b) == 0) {
        int r0 = func_ov096_0229f054(r5, r4);
        func_02066830(r5 + 0x2f28, r0);
        func_ov096_0229f47c(r5, *(unsigned char *) (r5 + 0xb4), r5 + 0x2f28);
    }
    func_ov096_0229e898(r5, r4, 1);
    return 1;
}
