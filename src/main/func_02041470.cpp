/* func_02041470 @ 0x02041470, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02041470 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
};

extern unsigned char data_021c75b8;
extern unsigned char data_021c75a0[5];
extern int data_020db6f0[];

extern "C" void *func_020682e0(int param);
extern "C" void func_020a8164(void *param1, int param2);
extern "C" void func_02068340(void *param1, void *param2);

extern "C" void func_02041470(void *self)
{
    int cond = (data_021c75b8 == 2) ? 1 : 0;
    if (cond != 0) {
        void *r4 = func_020682e0(0);
        UnkStruct_02041470 *sub = (UnkStruct_02041470 *) ((char *) self + 0x54);
        sub->f2();
        func_020a8164((char *) self + 0x54, data_020db6f0[data_021c75a0[1]]);
        ((unsigned char *) self)[0x72] = data_021c75a0[4];
        func_02068340(r4, (char *) self + 0x54);
        *(int *) ((char *) r4 + 8) = 1;
        data_021c75a0[0] = 6;
    }
}
