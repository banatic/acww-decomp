/* func_0206a21c @ 0x0206a21c, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0206a21c_2 {
  public:
    virtual int method0();
    virtual int method1();
    virtual int method2();
    virtual int method3();
};

struct UnkStruct_0206a21c {
    char pad_00[0x24];
    void *unk_24;
};

extern "C" UnkStruct_0206a21c_2 *func_02067fa4(void *);
extern "C" void func_020a9334(UnkStruct_0206a21c *, int);
extern "C" void func_020a7994(void *, int);

extern "C" void func_0206a21c(UnkStruct_0206a21c *param)
{
    func_020a9334(param, func_02067fa4(param->unk_24)->method3());
    func_020a7994((char *) param->unk_24 + 0x1a58, func_02067fa4(param->unk_24)->method3());
    *((unsigned int *) ((char *) param->unk_24 + 0x1a60)) = 1;
}
