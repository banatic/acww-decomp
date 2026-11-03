/* text_draw_4: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02051648 @ 0x02051648, 0x24 bytes, Thumb
 * func_02051624 @ 0x02051624, 0x22 bytes, Thumb
 */

class UnkStruct_02051648 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual unsigned int v3();
    unsigned char pad_04[28];
    unsigned int unk_20;
    unsigned char pad_24[12];
    unsigned int unk_30;
};

class UnkStruct_02051624 {
  public:
    virtual unsigned int f0();
    virtual unsigned int f1();
    virtual unsigned int f2();
    virtual unsigned int f3();
    unsigned char pad_04[0x1c];
    unsigned int unk_20;
    unsigned char pad_24[0xc];
    unsigned int unk_30;
};

extern "C" void func_02051648(UnkStruct_02051648 *p)
{
    unsigned int ret = p->v3();
    unsigned int shifted = p->unk_20 << 3;
    if (shifted > ret) {
        p->unk_30 = (shifted - ret) >> 1;
    } else {
        p->unk_30 = 0;
    }
}

extern "C" void func_02051624(UnkStruct_02051624 *self)
{
    unsigned int res = self->f3();
    unsigned int tmp = self->unk_20 << 3;
    if (tmp > res) {
        self->unk_30 = tmp - res;
    } else {
        self->unk_30 = 0;
    }
}
