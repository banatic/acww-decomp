/* func_ov099_0229c688 @ 0x0229c688, 0x54 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

// placeholder for r5 base

extern int func_ov002_02208ae4(void *);
extern int func_ov002_02208ad8(void *, unsigned char);
extern void func_ov002_0220a08c(void *, int, int, int);
extern void func_ov002_02208098(void *, int);

void func_ov099_0229c688(char *base)
{
    int r4;
    int r2;
    unsigned char b;

    r4 = func_ov002_02208ae4(base + 0x22d8);
    r2 = func_ov002_02208ad8(base + 0x22d8, *(unsigned char *) (base + 0x290c));
    func_ov002_0220a08c(base + 0x2274, r4, r2, 2);
    b = *(unsigned char *) (base + 0x8d);
    *(unsigned char *) (base + 0x290a) = b;
    func_ov002_02208098(base, 8);
}
