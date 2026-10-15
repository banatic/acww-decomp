/* func_ov120_0229ba68 @ 0x0229ba68, 0xb0 bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_ov120_0229c700[];
extern unsigned char data_ov120_0229c718[];
extern unsigned char data_ov120_0229c730[];
extern unsigned char data_ov120_0229c748[];
extern unsigned char data_ov120_0229c760[];

extern void *data_021fbe94;

extern int func_02002d14(const unsigned char *a, void *b, int c, int d, int e, int f);
extern int func_02002c6c(const unsigned char *a, void *b, int c, int d, int e, int f);
extern int func_02064af4(const unsigned char *a, unsigned char *b, int c);
extern int func_02002b40(unsigned char *a, int b, int c, int d);
extern void func_0206fdd4(unsigned char *a, int b, int c, int d, int e, int f);

void func_ov120_0229ba68(unsigned char *self)
{
    void *work = data_021fbe94;
    func_02002d14(data_ov120_0229c700, work, 4, 1, 1, 0xf);
    func_02002c6c(data_ov120_0229c718, work, 4, 0x11, 0x11, 0x5f);
    func_02002c6c(data_ov120_0229c730, work, 4, 0x230, 0x230, 0x25f);
    func_02064af4(data_ov120_0229c748, self + 0x720, 0x800);
    func_02002b40(self + 0x720, 4, 0x800, 0);
    func_02064af4(data_ov120_0229c760, self + 0x1f20, 0x800);
    func_0206fdd4(self + 0x1f20, 0x13, 0, 0x1c, 1, 4);
}
