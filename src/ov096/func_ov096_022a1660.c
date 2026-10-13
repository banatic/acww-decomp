/* func_ov096_022a1660 @ 0x022a1660, 0x84 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov096_0229c4dc(char *);
extern void func_020664a8(void *);
extern void func_0206e230(char *, void *, int, int, int);
extern void func_ov002_02207f20(char *, int, int, int, int);
extern void func_02002708(int);
extern void func_ov002_02207e80(char *, int, int, int);
extern void func_ov002_02208090(char *, int);
extern void func_ov002_0220b53c(char *, int);
extern void func_ov096_0229c2ec(char *, int);

void func_ov096_022a1660(char *self)
{
    int zero = 0;
    void *r4;

    r4 = func_ov096_0229c4dc(self);
    func_020664a8(r4);
    func_0206e230(self + 0x2a74, r4, 3, 4, 1);
    func_ov002_02207f20(self, 3, zero, zero, 0x30);
    func_02002708(3);
    func_ov002_02207e80(self, 3, zero, zero);
    func_02002708(4);
    func_ov002_02207e80(self, 4, zero, zero);
    func_ov002_02208090(self, 8);
    func_ov002_0220b53c(self + 0x2d9c, 0x88);
    func_ov096_0229c2ec(self, 0x100);
}
