/* func_0204141c @ 0x0204141c, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0204141c {
    int unk_00;
    int unk_04;
};
extern struct UnkStruct_0204141c *func_020682e0(int);
extern void func_02068320(struct UnkStruct_0204141c *);
extern int func_020b5e10(void);
extern int func_020b6098(int, int);
extern void func_02035c1c(int, int, unsigned char);
extern int data_021c526c;
extern int data_021c758c;
extern unsigned char data_021c75a0[];

void func_0204141c(void)
{
    struct UnkStruct_0204141c *p = func_020682e0(0);
    if (p->unk_04 != 0) {
        return;
    }
    func_02068320(p);
    func_020b6098(func_020b5e10(), 0x14);
    func_02035c1c(data_021c526c + 0x2d0, data_021c758c, data_021c75a0[4]);
    data_021c758c = 0;
    data_021c75a0[0] = 0;
    data_021c75a0[2] = 0;
}
