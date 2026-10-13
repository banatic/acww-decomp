/* func_ov111_0229f92c @ 0x0229f92c, 0x68 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov111_0229f4dc(void *);
extern void func_02051bf8(void *, int);
extern void func_02051c08(void *, const void *, int);
extern void func_ov111_0229efc8(void *, int);
extern void func_ov095_022999f4(void *);
extern void func_ov111_0229efec(void *);

void func_ov111_0229f92c(char *p)
{
    if (func_ov111_0229f4dc(p)) {
        unsigned char b = p[0xa0];
        unsigned char a = p[0x9f];
        int x, y;
        if (a > b) {
            x = b;
            y = a - b;
        } else {
            x = a;
            y = b - a;
        }
        func_02051bf8(p + 0x3eb8, 0x10);
        func_02051c08(p + 0x3d16 + 2 * x, p + 0x3eb8, y);
        func_ov111_0229efc8(p, 8);
        func_ov095_022999f4(p + 0xac);
        func_ov111_0229efec(p);
    }
}
