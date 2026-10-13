/* func_ov102_0229dfa4 @ 0x0229dfa4, 0x4c bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern void func_02064328(void *, const void *, unsigned int);
extern void func_02002d14(void *, void *, int, int, int, int);
extern int func_ov102_0229d258(void *);
extern void func_ov094_0229ace4(void *, int);
extern const unsigned char data_ov102_0229eb50[];
extern void *data_021fbe94;

void func_ov102_0229dfa4(unsigned char *self)
{
    void *ptr = data_021fbe94;
    unsigned char buf[0x24];

    func_02064328(buf, data_ov102_0229eb50, self[0x25aa]);
    func_02002d14(buf, ptr, 4, 3, 3, 5);
    func_ov094_0229ace4(self + 0xcc, func_ov102_0229d258(self));
}
