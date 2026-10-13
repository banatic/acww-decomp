/* func_0203d73c @ 0x0203d73c, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Cfg {
    int unk_00;
    int unk_04;
    int unk_08;
};
extern Cfg data_021c6cb4;

struct UnkStruct_0203d73c {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual char *v3();
};

extern "C" void func_0203d73c(UnkStruct_0203d73c *self)
{
    char *s;
    int i;
    int v;

    data_021c6cb4.unk_04 = 0;
    s = self->v3();
    for (i = 0; s[i] != 0 && s[i + 1] != 0; i += 2) {
        v = ((s[i + 1] << 8) & 0xff00) | (s[i] & 0xff);
        if (v >= 0xac00 && v <= 0xd7a3) {
            data_021c6cb4.unk_04 = v;
        }
    }
    data_021c6cb4.unk_08 = 0;
}
