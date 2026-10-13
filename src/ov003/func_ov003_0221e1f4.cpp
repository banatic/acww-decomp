/* func_ov003_0221e1f4 @ 0x0221e1f4, 0x60 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0221e1f4 {
  public:
    virtual void vf0();
    virtual void vf1();
    virtual void vf2();
    virtual void vf3();
    virtual void vf4();
    virtual void vf5();
    virtual void vf6();
    virtual void vf7();
    virtual void vf8();
    virtual void vf9();
    virtual void vf10();
    virtual void vf11();
    virtual void vf12();
    virtual void vf13();
    virtual void vf14();
    virtual void vf15();
    virtual void vf16();
    virtual void vf17();
    virtual void vf18();
    virtual void vf19();
    virtual void vf20();
    virtual void vf21();
    virtual void vf22();
    virtual void vf23();
    virtual void vf24();
    virtual int vf25();
};

extern "C" {
void func_02055060(void *p, int a, int b, int c, int d, int e);
int func_02055e00(void *p);
int func_ov009_02264cf8(void *p, int a);
void func_02056440(void *p, int a, int b, int c, int d, int e);
}

extern "C" int func_ov003_0221e1f4(UnkStruct_0221e1f4 *obj)
{
    int ret1;
    int ret2;
    int ret3;

    ret1 = obj->vf25();
    func_02055060((char *) obj + 0x13c, ret1, 1, 0x1000, 0, 0);
    ret2 = func_02055e00((char *) obj + 0x13c);
    ret3 = func_ov009_02264cf8(obj, 0);
    func_02056440((char *) obj + 0x2b8, ret2, ret3, 1, 0x1000, 0);
    return 1;
}
