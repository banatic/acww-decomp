/* func_020046c4 @ 0x020046c4, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" int func_02035bec(int arg);
extern int data_021c526c;
extern unsigned char data_021fd21c[];
class UnkStruct_020046c4 {
  public:
    virtual void v0() = 0;
    virtual void v1() = 0;
    virtual void v2() = 0;
    virtual void v3() = 0;
    virtual void v4() = 0;
    virtual void v5() = 0;
    virtual void v6() = 0;
};
extern UnkStruct_020046c4 *data_0213fff0;

extern "C" void func_020046c4(void)
{
    if (!data_0213fff0) {
        return;
    }
    if (func_02035bec(data_021c526c + 0x2d0)) {
        data_021fd21c[2] = 1;
    }
    data_0213fff0->v6();
    if (data_0213fff0) {
        data_0213fff0->v1();
    }
    data_0213fff0 = 0;
}
