/* func_ov103_0229daf4 @ 0x0229daf4, 0x88 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov103_0229cce8(unsigned char *, unsigned char);
extern void func_020664a8(int);
extern void func_0206e230(unsigned char *, int, int, int, int);
extern void func_ov002_02207f20(unsigned char *, int, int, int, int);
extern void func_02002708(int);
extern void func_ov002_02207e80(unsigned char *, int, int, int);
extern void func_ov002_02208090(unsigned char *, int);
extern void func_ov002_0220b53c(unsigned char *, int);
extern void func_ov103_0229c2e4(unsigned char *, int);

void func_ov103_0229daf4(unsigned char *self)
{
    int ret;

    ret = func_ov103_0229cce8(self, self[0x2da5]);
    func_020664a8(ret);
    func_0206e230(self + 0x27e8, ret, 3, 4, 1);
    func_ov002_02207f20(self, 3, 0, 0, 0x30);
    func_02002708(3);
    func_ov002_02207e80(self, 3, 0, 0);
    func_02002708(4);
    func_ov002_02207e80(self, 4, 0, 0);
    func_ov002_02208090(self, 6);
    func_ov002_0220b53c(self + 0x2b10, 0x88);
    func_ov103_0229c2e4(self, 0x80);
}
