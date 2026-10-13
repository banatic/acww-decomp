/* func_ov106_0229ec0c @ 0x0229ec0c, 0x80 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov106_0229d20c(unsigned char *a, unsigned char b);
extern void func_ov106_0229d1b8(unsigned char *a, int b);
extern void func_020664a8(int a);
extern void func_0206e230(unsigned char *a, int b, int c, int d, int e);
extern void func_ov002_02207f20(unsigned char *a, int b, int c, int d, int e);
extern void func_02002708(int a);
extern void func_ov106_0229eb28(unsigned char *a);
extern void func_ov002_02208090(unsigned char *a, int b);
extern void func_ov002_0220b53c(unsigned char *a, int b);
extern void func_ov106_0229c354(unsigned char *a, int b);

void func_ov106_0229ec0c(unsigned char *p)
{
    int t;

    t = func_ov106_0229d20c(p, p[0xb9]);
    func_ov106_0229d1b8(p, t);
    func_020664a8(t);
    func_0206e230(p + 0x2814, t, 3, 4, 1);
    func_ov002_02207f20(p, 3, 0, 0, 0x30);
    func_02002708(3);
    func_02002708(4);
    func_ov106_0229eb28(p);
    func_ov002_02208090(p, 8);
    func_ov002_0220b53c(p + 0x2b3c, 0x88);
    func_ov106_0229c354(p, 0x80);
}
