/* func_ov002_0220a448 @ 0x0220a448, 0x74 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_02064328();
extern void func_02002c6c();
extern void func_02002ca4();
extern void func_02002d14();
extern void *data_021fbe94;
extern const char data_ov002_0220bc9c[];
extern const char data_ov002_0220bcb4[];
extern const char data_ov002_0220bccc[];

void func_ov002_0220a448(void *arg, void *b)
{
    char tmp[0x20];
    void *g = data_021fbe94;

    func_02064328(tmp, data_ov002_0220bc9c, arg);
    func_02002c6c(tmp, g, b, 0x10, 0x10, 0x74);
    func_02064328(tmp, data_ov002_0220bcb4, arg);
    func_02002ca4(tmp, g, b);
    func_02064328(tmp, data_ov002_0220bccc, arg, arg);
    func_02002d14(tmp, g, b, 0xc, 0xc, 0xe);
}
