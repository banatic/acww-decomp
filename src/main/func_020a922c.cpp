/* func_020a922c @ 0x020a922c, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_020a922c {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
    int unk_04;
    int pad_08[8];
    unsigned char unk_28;
};

extern "C" int func_020a9368(UnkStruct_020a922c *a, unsigned char c);

extern "C" int func_020a922c(UnkStruct_020a922c *a, int b)
{
    while (1) {
        if (a->unk_04 == b) {
            a->f3();
            break;
        }
        if (func_020a9368(a, a->unk_28) != 0) {
            continue;
        }
        break;
    }
    return 0;
}
