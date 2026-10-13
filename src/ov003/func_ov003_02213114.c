/* func_ov003_02213114 @ 0x02213114, 0x54 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_022131a8(void *a, unsigned char b, unsigned char c, int d);
extern void func_020109a0(void *a, int b, int c, int d);
extern void func_0205eae0(void *a, int b, int c, int d);
extern void func_0200f328(void *a, int b);

void func_ov003_02213114(void *self, void *data)
{
    unsigned char *p = (unsigned char *) data + 0xc;
    unsigned char *dst = (unsigned char *) self + 0x7d4;
    unsigned char b0 = p[0];
    unsigned char b1 = p[1];

    dst[0] = b0;
    dst[1] = b1;

    func_ov003_022131a8((unsigned char *) self + 0x8f0, b0, b1, 0);
    func_020109a0(self, 0x5d, 3, 0);
    func_0205eae0((unsigned char *) self + 0x5a0, 6, 3, 1);
    func_0200f328(self, 0x4f);
}
