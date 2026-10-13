/* func_ov126_022a06d8 @ 0x022a06d8, 0x50 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov095_0229bbc0(void *ptr1, void *ptr2, int min, int max, int c);
extern void func_ov126_022a0924(void *p, unsigned char val);
extern void func_ov126_022a0728(void *p);

void func_ov126_022a06d8(void *p)
{
    unsigned char *base = (unsigned char *) p;
    unsigned char a, b, c, min, max, result;

    a = base[0xaa];
    b = base[0xa9];
    if (b > a) {
        min = a;
        max = b;
    } else {
        min = b;
        max = a;
    }
    c = base[0xa6];
    result = (unsigned char) func_ov095_0229bbc0((char *) p + 0x19c, (char *) p + 0x4248, min, max, c);
    func_ov126_022a0924(p, result);
    func_ov126_022a0728(p);
}
