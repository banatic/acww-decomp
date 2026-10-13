/* func_ov096_0229db30 @ 0x0229db30, 0x48 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207d24(void *p, int a);
extern void func_ov002_0220a374(void *p, int a);
extern void func_ov002_02208098(void *p, int a);

void func_ov096_0229db30(void *self, unsigned char v)
{
    func_ov002_02207d24((char *) self + 0x2418, 1);
    ((unsigned char *) self)[0xba] = ((unsigned char *) self)[0x8d];
    ((unsigned char *) self)[0xb7] = v;
    func_ov002_0220a374((char *) self + 0x2500, 6);
    func_ov002_02208098(self, 0x15);
}
