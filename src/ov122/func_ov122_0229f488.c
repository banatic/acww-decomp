/* func_ov122_0229f488 @ 0x0229f488, 0x58 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40;
extern void func_ov002_0220a4c8(void *receiver);
extern void func_ov122_0229f468(unsigned char *self, int value);

void func_ov122_0229f488(unsigned char *self)
{
    int value;
    unsigned char *p = self;
    unsigned char b = p[0xb2];

    value = b;
    if (data_021fbe40 & 0x40) {
        value = b - 4;
    } else if (data_021fbe40 & 0x80) {
        value = b + 4;
    }
    if (value < 0) {
        value = 0;
    }
    if (value > 0x58) {
        value = 0x58;
    }
    if (value != b) {
        func_ov002_0220a4c8((void *) (p + 0x4010));
    }
    func_ov122_0229f468(p, value);
}
