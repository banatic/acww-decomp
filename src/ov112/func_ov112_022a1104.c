/* func_ov112_022a1104 @ 0x022a1104, 0xf0 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern void func_02002d14(void *a, void *b, int c, int d, int e, int f);
extern void func_02064af4(void *a, void *b, unsigned int c);
extern void func_0206fdd4(void *a, int b, int c, int d, int e, int f);
extern void func_02002b40(void *a, int b, unsigned int c, int d);
extern void func_02002c6c(void *a, void *b, int c, int d, int e, int f);

extern void func_ov095_0229c000(void *a, void *b);
extern void func_ov112_0229f488(void *a);
extern void func_ov095_0229bfd8(void *a, int b);
extern void func_ov095_0229c01c(void *a, int b);
extern void func_ov095_0229b324(void *a);

extern void *data_021fbe94; // at 0x021fbe94
extern unsigned char data_ov112_022a2130[];
extern unsigned char data_ov112_022a2148[];
extern unsigned char data_ov112_022a2160[];
extern unsigned char data_ov112_022a2178[];
extern unsigned char data_ov112_022a2190[];
extern unsigned char data_ov112_022a21a8[];

void func_ov112_022a1104(char *self)
{
    void *work = data_021fbe94;

    func_02002d14(data_ov112_022a2130, work, 4, 8, 8, 14);
    func_02064af4(data_ov112_022a2148, self + 0x4650, 0x800);
    func_0206fdd4(self + 0x4650, 6, 5, 25, 6, 10);
    func_02002b40(self + 0x4650, 4, 0x800, 0);
    func_02002c6c(data_ov112_022a2160, work, 4, 317, 317, 489);
    func_02002c6c(data_ov112_022a2178, work, 4, 16, 16, 319);
    func_02002c6c(data_ov112_022a2190, work, 4, 257, 257, 272);
    func_ov095_0229c000(self + 0x384, data_ov112_022a21a8);
    func_ov112_0229f488(self);
    func_ov095_0229bfd8(self + 0x384, 6);
    func_ov095_0229c01c(self + 0x384, 6);
    func_ov095_0229b324(self + 0x384);
}
