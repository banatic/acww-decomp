/* func_ov109_0229cff8 @ 0x0229cff8, 0x50 bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *ptr);
extern void func_ov002_02209114(void *ptr, unsigned char val, int flag);
extern void func_ov002_02208098(void *ptr, int val);

void func_ov109_0229cff8(void *p)
{
    unsigned char *base;
    unsigned char *q;
    if (func_0208e484((char *) p + 0x2274) == 0) {
        return;
    }
    base = (unsigned char *) p;
    func_ov002_02209114((char *) p + 0x22d8, base[0x29d8], 1);
    q = base + base[0x29d8];
    base[0x29d7] = q[0x26c5];
    func_ov002_02208098(p, 0xc);
}
