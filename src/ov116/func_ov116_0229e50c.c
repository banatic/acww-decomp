/* func_ov116_0229e50c @ 0x0229e50c, 0x98 bytes, Thumb, module ov116
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206f58c(void);
extern int func_0206f56c(void);
extern int func_0206fe60(void);
extern int func_ov090_022990e0(void);
extern int func_ov116_0229e4cc(void *p, int x);
extern unsigned short data_021fbe40[];

int func_ov116_0229e50c(void *p)
{
    func_0206f58c();
    if (func_0206f56c() != 0) {
        return func_ov116_0229e4cc(p, 7);
    }
    {
        unsigned char b = *(unsigned char *) ((char *) p + 0x8d);
        if (b != 0 && b != 2) {
            return 0;
        }
    }
    {
        int r4 = -1;
        int c = func_0206fe60();
        if (c != 0) {
            r4 = func_ov090_022990e0();
        } else {
            unsigned short flags = data_021fbe40[1];
            if (flags & 2) {
                r4 = 7;
            } else if (flags & 0x800) {
                r4 = 0;
            } else if (flags & 0x400) {
                r4 = 5;
            } else if (flags & 4) {
                r4 = 4;
            }
        }
        return func_ov116_0229e4cc(p, r4);
    }
}
