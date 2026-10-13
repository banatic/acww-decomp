/* func_020b4f3c @ 0x020b4f3c, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" int func_020a7c98(int, int);
extern "C" int func_02050bdc_unk(int);
extern "C" int func_020b4d70(int);
extern "C" void func_020b512c(void *);

class VBase {
  public:
    virtual int vfunc0();
    virtual int vfunc1();
    virtual int vfunc2();
    virtual int vfunc3();
};

struct Middle {
    char pad_00[0x18f0];
    VBase *obj;
};

struct UnkStruct_020b4f3c {
    char pad_00[0x24];
    Middle *mid;
    char pad_28[0x14];
    void *unk_3C;
    char pad_40[0x4];
    unsigned char unk_44;
    unsigned char unk_45;
    unsigned char pad_46;
    unsigned char unk_47;
    unsigned char unk_48;
};

extern "C" void func_020b4f3c(UnkStruct_020b4f3c *param0)
{
    if (param0->unk_47 != 0) {
        int ret = func_020a7c98(param0->mid->obj->vfunc3(), 2);
        if (param0->unk_48 != 0) {
            ret = func_02050bdc_unk(ret);
            param0->unk_48 = 0;
        }
        if (func_020b4d70(ret) != 0) {
            param0->unk_3C = (void *) ret;
            func_020b512c(param0);
            param0->unk_44 = 1;
        } else {
            param0->unk_45 = 0;
        }
    }
}
