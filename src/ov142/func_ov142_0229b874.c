/* func_ov142_0229b874 @ 0x0229b874, 0xb4 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021fbe94;
extern const unsigned char data_ov142_0229c520[];
extern const unsigned char data_ov142_0229c538[];
extern const unsigned char data_ov142_0229c550[];
extern const unsigned char data_ov142_0229c564[];
extern const unsigned char data_ov142_0229c57c[];
extern const unsigned char data_ov142_0229c594[];
extern const unsigned char data_ov142_0229c5ac[];

int func_02002c6c(const void *src, void *dst, int size, int a, int b, int c);
int func_02002d14(const void *src, void *dst, int size, int a, int b, int c);
int func_02064af4(const void *src, void *dst, unsigned int size);

void func_ov142_0229b874(unsigned char *self)
{
    void *base = data_021fbe94;
    func_02002c6c(data_ov142_0229c520, base, 6, 0x11, 0x11, 0x51);
    func_02002c6c(data_ov142_0229c538, base, 6, 0x156, 0x156, 0x174);
    func_02002d14(data_ov142_0229c550, base, 6, 1, 1, 5);
    func_02064af4(data_ov142_0229c564, self + 0x3060, 0x20);
    func_02064af4(data_ov142_0229c57c, self + 0x30a0, 0x20);
    func_02064af4(data_ov142_0229c594, self + 0x1860, 0x800);
    func_02064af4(data_ov142_0229c5ac, self + 0x2860, 0x800);
}
