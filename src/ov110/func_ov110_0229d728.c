/* func_ov110_0229d728 @ 0x0229d728, 0x48 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207d24(void *, int);
extern void func_ov110_0229cd14(void *, int);
extern void func_ov110_0229cdb4(void *);
extern void func_ov094_022999c0(void);

void func_ov110_0229d728(void *p, char val)
{
    unsigned char *base = (unsigned char *) p;
    base[0xf4] = val;
    func_ov002_02207d24(base + 0x21f8, 1);
    func_ov110_0229cd14(p, val);
    if (base[0xf1] == 1) {
        base[0xf8] = 5;
    }
    func_ov110_0229cdb4(p);
    func_ov094_022999c0();
}
