/* func_02051648 @ 0x02051648, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
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
