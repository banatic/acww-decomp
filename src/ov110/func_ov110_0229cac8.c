/* func_ov110_0229cac8 @ 0x0229cac8, 0x60 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_022090e4(void *, int);
extern int func_ov002_02208ae4(void *);
extern int func_ov002_02208ad8(void *, unsigned char);
extern void func_ov002_0220a0b4(void *, int, int);
extern void func_0208e4c0(void *, int);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov110_0229cac8(void *p)
{
    unsigned char *base = (unsigned char *) p;
    int v1;
    int v2;
    base[0xf9] = 1;
    base[0xfa] = func_ov002_022090e4(base + 0x2344, 1);
    v1 = func_ov002_02208ae4(base + 0x2344);
    v2 = func_ov002_02208ad8(base + 0x2344, base[0xfa]);
    func_ov002_0220a0b4(base + 0x22e0, v1, v2);
    func_0208e4c0(base + 0x22e0, 8);
    func_ov002_02208098((void *) (p), 0x12);
}
