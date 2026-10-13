/* func_ov004_022110e4 @ 0x022110e4, 0x108 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203f130(void *);
extern void func_02054e54(void *);
extern void func_02066a30(void *);
extern void func_0209d34c(void *);
extern void func_020b82ec(void *);
extern void func_02138d6c(void *, int, int, void *, void *);
extern void func_ov004_0220d02c(void *);
extern void func_ov004_0220d268(void *);
extern void func_ov004_0220d38c(void *);
extern void func_ov004_0220d3b8(void *);
extern void func_ov004_0220d4dc(void *);
extern void func_ov004_0220d840(void *);
extern void func_ov004_0220e008(void *);
extern void func_ov004_0220e474(void *);
extern void func_ov004_0223b250(void *);
extern void func_ov004_0223cfbc(void *);
extern void func_020b7ed8();
extern void func_020b7ee8();
extern void func_ov004_0220e4d4();
extern void func_ov004_0220e4ec();
extern void *data_ov004_0224fe6c;
extern void *data_ov004_0224ff18;

void *func_ov004_022110e4(char *self)
{
    // DECLS
    // ENDDECLS
    func_0203f130(self);
    func_02066a30(self + 0xec);
    *(void **) (self) = &data_ov004_0224fe6c;
    *(void **) (self + 0xec) = &data_ov004_0224ff18;
    func_0209d34c(self + 0x132);
    func_ov004_0220d4dc(self + 0x17c);
    func_ov004_0220d840(self + 0x18c);
    func_02138d6c(self + 0x1d0, 0x4, 0x20, (void *) func_020b7ee8, (void *) func_020b7ed8);
    func_ov004_0223b250(self + 0x250);
    func_020b82ec(self + 0x28c);
    func_02054e54(self + 0x538);
    func_ov004_0220e008(self + 0x62c);
    func_ov004_0220e474(self + 0x6cc);
    func_ov004_0220d38c(self + 0x740);
    func_ov004_0220d3b8(self + 0x742);
    func_ov004_0220d268(self + 0x748);
    func_ov004_0220d02c(self + 0x764);
    func_ov004_0223cfbc(self + 0x798);
    func_02138d6c(self + 0x7c4, 0x4, 0x20, (void *) func_ov004_0220e4ec, (void *) func_ov004_0220e4d4);
    return self;
}
