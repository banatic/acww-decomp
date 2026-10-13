/* func_020b9b6c @ 0x020b9b6c, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_020b9b6c {
  public:
    virtual void f0();
    virtual void f1();
    char pad_04[8];
    unsigned char c;
    char pad_0D;
    unsigned char e;
    unsigned char unk_0F;
    char sub;
};

extern "C" {
void func_020b9c68(UnkStruct_020b9b6c *p1, int p2, int p3, int p4);
void func_020ba09c(char *sub, int p2, int p3, int p4);
int func_020ba078(char *sub);
int func_020b98c4(UnkStruct_020b9b6c *p1);
}

extern "C" int func_020b9b6c(UnkStruct_020b9b6c *p1, int p2, int p3, int p4)
{
    func_020b9c68(p1, p2, p3, p4);
    p1->e = 6;
    func_020ba09c(&p1->sub, p2, p3, p4);
    p1->unk_0F = func_020ba078(&p1->sub);
    p1->c = 4;
    if (func_020b98c4(p1)) {
        return 1;
    } else {
        p1->f1();
        return 0;
    }
}
