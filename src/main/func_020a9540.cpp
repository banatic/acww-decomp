/* func_020a9540 @ 0x020a9540, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct SomeGlobal {
    int pad_00;
    char *ptr;
} data_021f4458;

extern "C" void func_02064658(char *arg1, int arg2, unsigned int arg3, char *arg4);

class UnkStruct_020a9540 {
  public:
    virtual void method0() = 0;
    virtual void method1() = 0;
    virtual int method2() = 0;
    virtual unsigned int method3() = 0;
    char pad_04[0x98];
    int unk_9C;
    unsigned int unk_A0;
};

extern "C" int func_020a9540(UnkStruct_020a9540 *obj)
{
    int a = obj->method2();
    unsigned int b = obj->method3();
    int off = obj->unk_9C + 8;
    unsigned int c = obj->unk_A0;
    unsigned int d = (b < c) ? b : c;
    char *base = (char *) data_021f4458.ptr + 0x20;
    func_02064658((char *) obj + 0x44, a, d, base + off);
    return 1;
}
