/* func_020f7d4c @ 0x020f7d4c, 0x50 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
void func_0210b7e0(void *p);
void NNS_SndPlayerSetVolume(void *p, int v);
}

class UnkStruct_020f7d4c {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    int unk_04;
    int unk_08;
    unsigned char unk_0C;
};

extern "C" void func_020f7d4c(UnkStruct_020f7d4c *obj)
{
    func_0210b7e0(&obj->unk_04);
    func_0210b7e0(&obj->unk_08);
    obj->unk_0C = 0;
    obj->v5();
    NNS_SndPlayerSetVolume(&obj->unk_04, 0);
    NNS_SndPlayerSetVolume(&obj->unk_08, 0);
}
