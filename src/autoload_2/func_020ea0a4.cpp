/* func_020ea0a4 @ 0x020ea0a4, 0x3c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

class UnkStruct_020ea0a4 {
  public:
    virtual void vf0(void);
    virtual void vf1(void);
    virtual void f2(void);
    unsigned int pad_04[3];
    unsigned int flag;
};

extern "C" unsigned int OS_GetProcMode(void);
extern "C" void OS_Terminate(void);

extern "C" void func_020ea0a4(UnkStruct_020ea0a4 *self)
{
    if (OS_GetProcMode() != 0x1f && (self->flag & 0x2000) == 0) {
        OS_Terminate();
    }
    self->f2();
}
