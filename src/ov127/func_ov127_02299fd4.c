/* func_ov127_02299fd4 @ 0x02299fd4, 0x78 bytes, Thumb, module ov127
 * mwccarm 1.2/base -O4,s
 */

extern int data_021fbe94;
extern const int data_ov127_0229b664[];
extern const int data_ov127_0229b67c[];
extern const int data_ov127_0229b694[];
extern int func_02002d14(const int *data, int a, unsigned char b, int c, int d, int e);
extern int func_02002c6c(const int *data, int a, unsigned char b, int c, int d, int e);
extern int func_02064af4(const int *data, void *ptr, int size);
extern int func_02002b40(void *ptr, unsigned char b, int size, int zero);

void func_ov127_02299fd4(unsigned char *self, unsigned char val, int mode)
{
    int g = data_021fbe94;
    self[0x2833] = val;
    func_02002d14(data_ov127_0229b664, g, self[0x2833], 4, 8, 0xb);
    func_02002c6c(data_ov127_0229b67c, g, self[0x2833], 0x20, 0x20, 0xbf);
    func_02064af4(data_ov127_0229b694, self + 0x2024, 0x800);
    func_02002b40(self + 0x2024, self[0x2833], 0x800, 0);
}
