/* func_ov109_0229c4f4 @ 0x0229c4f4, 0x40 bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206fc80(unsigned char);
extern void func_0206fc4c(int);
extern unsigned char *func_ov002_022080a0(void *, unsigned char value);
extern int func_ov002_02207d24(void *, int);
extern void func_ov109_0229c828(void *);

void func_ov109_0229c4f4(void *self)
{
    func_0206fc80(((unsigned char *) self)[0x29d4]);
    func_0206fc4c(1);
    ((unsigned char *) self)[0x8c] = 3;
    func_ov002_022080a0(self, 1);
    func_ov002_02207d24((char *) self + 0x218c, 1);
    func_ov109_0229c828(self);
}
