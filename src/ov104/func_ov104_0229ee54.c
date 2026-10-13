/* func_ov104_0229ee54 @ 0x0229ee54, 0x74 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov104_0229e8f8(void *);
extern void func_02002708(int);
extern void func_ov104_0229d830(void *);
extern void func_ov104_0229c354(void *, int);
extern void func_ov104_0229eb68(void *);
extern void func_ov094_0229ad20(void *);
extern void func_ov094_0229b2b0(void *);
extern void func_ov094_0229b29c(void *, void *);
extern void func_ov002_02207f20(void *, int, int, int, int);
extern void func_ov002_02208090(void *, int);

void func_ov104_0229ee54(void *self)
{
    func_ov104_0229e8f8(self);
    func_ov094_0229ad20((char *) self + 0x2f8);
    func_ov094_0229b2b0((char *) self + 0xd58);
    func_ov094_0229b29c((char *) self + 0xd58, (char *) self + 0x2db4);
    func_ov104_0229d830(self);
    func_ov002_02207f20(self, 8, 0, 0, 0x30);
    func_02002708(6);
    func_ov002_02208090(self, 2);
    func_ov104_0229c354(self, 1);
    func_ov104_0229c354(self, 2);
    func_ov104_0229eb68(self);
}
