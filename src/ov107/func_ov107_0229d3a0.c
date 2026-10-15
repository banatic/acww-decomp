/* func_ov107_0229d3a0 @ 0x0229d3a0, 0x58 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f43ec;
extern int func_ov002_0220b9b8(void *dst, const void *src, int a, int b);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_0208e5c4(void *self);

void func_ov107_0229d3a0(unsigned char *self, unsigned char byte1, unsigned char byte2)
{
    if (byte2 == 0xff) {
        self[0xbb] = self[0x8d];
    } else {
        self[0xbb] = byte2;
    }
    {
        unsigned char c;
        c = data_021f43ec;
        c = byte1;
        func_ov002_0220b9b8(self + 0x270c, &c, 1, 0);
    }
    func_ov002_02208098((void *) (self), 0xe);
    func_0208e5c4(self + 0x22b4);
}
