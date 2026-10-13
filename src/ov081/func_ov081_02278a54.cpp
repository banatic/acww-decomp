/* func_ov081_02278a54 @ 0x02278a54, 0x44 bytes, Thumb, module ov081
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
int func_0201c2a4(void *, int);
void func_02016108(void *, int);
void func_ov081_022792e0(void *, int);
}

class UnkStruct_02278a54 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
};

extern "C" void func_ov081_02278a54(void *self, int mode)
{
    switch (mode) {
        case 0:
            ((UnkStruct_02278a54 *) ((char *) self + 0x658))->f2();
            {
                int r = func_0201c2a4(self, 4);
                func_02016108((UnkStruct_02278a54 *) ((char *) self + 0x658), r);
            }
            func_ov081_022792e0(self, 1);
            break;
        case 8:
            func_ov081_022792e0(self, 0);
            break;
    }
}
