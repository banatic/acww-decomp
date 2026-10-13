/* func_ov141_0229a850 @ 0x0229a850, 0x80 bytes, Thumb, module ov141
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov139_022999f8(void *);
extern void func_ov139_022999c4(void *);
extern void func_02064af4(const void *, void *, int);
extern void func_0206fdd4(void *, int, int, int, int, int);
extern void func_ov141_02299f6c(void *, int);
extern void func_02002d14(const void *, int, int, int, int, int);

extern unsigned char data_ov141_0229afa8[];
extern unsigned char data_ov141_0229afbc[];
extern int data_021fbe94;

void func_ov141_0229a850(char *self)
{
    func_ov139_022999f8(self + 0x94);
    func_ov139_022999c4(self + 0x94);
    func_02064af4(data_ov141_0229afa8, self + 0x127c, 0x800);
    func_0206fdd4(self + 0x127c, 7, 8, 0x10, 0x13, 7);
    func_0206fdd4(self + 0x127c, 0x12, 8, 0x19, 0x13, 7);
    func_ov141_02299f6c(self, 4);
    func_02002d14(data_ov141_0229afbc, data_021fbe94, 6, 3, 3, 3);
}
