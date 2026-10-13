/* func_ov101_0229c720 @ 0x0229c720, 0x60 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_022090e4(void *);
extern int func_ov002_02208ae4(void *);
extern int func_ov002_02208ad8(void *, unsigned char);
extern void func_ov002_0220a0b4(void *, int, int);
extern void func_0208e4c0(void *, int);
extern void func_ov002_02208098(void *, int);

void func_ov101_0229c720(void *p)
{
    unsigned char *base = (unsigned char *) p;
    int v1;
    int v2;
    base[0xb7] = 1;
    base[0xb8] = func_ov002_022090e4(base + 0x2300);
    v1 = func_ov002_02208ae4(base + 0x2300);
    v2 = func_ov002_02208ad8(base + 0x2300, base[0xb8]);
    func_ov002_0220a0b4(base + 0x229c, v1, v2);
    func_0208e4c0(base + 0x229c, 8);
    func_ov002_02208098(p, 0x14);
}
