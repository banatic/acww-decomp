/* func_ov093_0229976c @ 0x0229976c, 0x48 bytes, Thumb, module ov093
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229976c {
    unsigned short unk_00;
    unsigned short unk_02;
    unsigned char unk_04;
    unsigned char unk_05;
};

void func_0200277c(int);
void func_020028bc(int, int, int, int);
void func_ov093_0229957c(struct UnkStruct_0229976c *);

void func_ov093_0229976c(struct UnkStruct_0229976c *p)
{
    p->unk_00 = 0;
    p->unk_04 = 0;
    func_0200277c(4);
    func_0200277c(0);
    func_020028bc(4, 0, 0, 0);
    *(volatile unsigned short *) 0x0400000a = ((*(volatile unsigned short *) 0x0400000a & 0x43) | 0x0700);
    p->unk_05 = 0;
    func_ov093_0229957c(p);
}
