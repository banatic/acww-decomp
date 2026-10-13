/* func_ov108_0229cdb8 @ 0x0229cdb8, 0x48 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206fc80(unsigned char);
extern void func_0206fc4c(int);
extern void func_ov108_0229c794(void *);
extern void func_ov002_022080a0(void *, int);
extern void func_ov002_02207d24(void *, int);

void func_ov108_0229cdb8(void *self)
{
    unsigned char val;
    val = ((unsigned char *) self)[0x2b1];
    func_0206fc80((unsigned char) (val - 0xb));
    func_0206fc4c(1);
    ((unsigned char *) self)[0x8c] = 3;
    func_ov002_022080a0(self, 1);
    func_ov002_02207d24((char *) self + 0x23b0, 1);
    func_ov108_0229c794(self);
}
