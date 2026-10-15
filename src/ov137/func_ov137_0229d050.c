/* func_ov137_0229d050 @ 0x0229d050, 0x5a bytes, Thumb, module ov137
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov137_0229ceb0(void);
extern void func_ov137_0229ce90(void *self);
extern void func_ov137_0229ce70(void *self);
extern void func_02002708(int);
extern void func_ov137_0229cfa0(void *self);
extern void func_ov137_0229c564(void *self, int);
extern int func_ov002_0220ab84(void *self, int);
extern void func_ov002_02208090(void *self, int);
extern void func_ov002_02207f20(void *self, int, int, int, int);

void func_ov137_0229d050(void *self)
{
    func_ov137_0229ceb0();
    func_ov137_0229ce90(self);
    func_ov137_0229ce70(self);
    func_ov002_02207f20(self, 0xa, 4, 0, 0x30);
    func_02002708(6);
    func_02002708(4);
    func_ov137_0229cfa0(self);
    func_ov137_0229c564(self, 1);
    func_ov002_0220ab84((char *) self + 0xf8, 0x21);
    func_ov002_02208090(self, 1);
}
