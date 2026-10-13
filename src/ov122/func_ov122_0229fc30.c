/* func_ov122_0229fc30 @ 0x0229fc30, 0x6c bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern void func_ov122_0229fae8(void *self, int a, int b, int c);
extern void func_ov122_0229efd8(void *self, int a);

int func_ov122_0229fc30(void *self)
{
    int a;
    int b;

    a = data_021f6c58;
    b = data_021f6c54;
    if (b < 0) {
        return 0;
    }
    if (b > 0x4f) {
        b = 0x4f;
    }
    b += ((unsigned char *) self)[0xb3];
    if (a < 0x20 || a >= 0xe0) {
        return 0;
    }
    if (a < 0x30) {
        a = 0x30;
    }
    func_ov122_0229fae8(self, a, b, 1);
    func_ov122_0229efd8(self, 8);
    ((unsigned char *) self)[0xad] = ((unsigned char *) self)[0xac];
    ((unsigned char *) self)[0xae] = ((unsigned char *) self)[0xac];
    return 1;
}
