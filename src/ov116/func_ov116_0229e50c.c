/* func_ov116_0229e50c @ 0x0229e50c, 0x98 bytes, Thumb, module ov116
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206f58c(void *p);
extern int func_0206f56c(int x);
extern int func_0206fe60(int x);
extern int func_ov090_022990e0(int x);
extern int func_ov116_0229e4cc(void *p, int x);
extern unsigned short data_021fbe40[];

int func_ov116_0229e50c(void *p)
{
    if (func_0206f56c(func_0206f58c(p)) != 0) {
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
        int c = func_0206fe60(0);
        if (c != 0) {
            r4 = func_ov090_022990e0(c);
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
