/* func_ov084_02278a54 @ 0x02278a54, 0x44 bytes, Thumb, module ov084
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02278a54 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};

struct UnkStruct_02278a54_2 {
    char pad_00[0x658];
    UnkStruct_02278a54 sub;
};

extern "C" {
int func_0201c2a4(void *self, int param);
void func_02016108(void *obj, int data);
void func_ov084_02279080(void *self, int param);
}

extern "C" void func_ov084_02278a54(UnkStruct_02278a54_2 *self, int cmd)
{
    switch (cmd) {
        case 0:
            self->sub.v2();
            {
                int ret = func_0201c2a4(self, 4);
                func_02016108(&self->sub, ret);
            }
            func_ov084_02279080(self, 1);
            break;
        case 8:
            func_ov084_02279080(self, 0);
            break;
    }
}
