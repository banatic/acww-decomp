/* func_ov078_02278a54 @ 0x02278a54, 0x8c bytes, Thumb, module ov078
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
extern int func_0201c2a4(void *self, int n);
extern void func_02016108(void *thisPtr, int arg);
extern void func_ov078_02279670(void *self, int flag);
}

class UnkStruct_02278a54 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void Call();
};

extern "C" void func_ov078_02278a54(void *selfRaw, unsigned int idx)
{
    char *self = (char *) selfRaw;
    UnkStruct_02278a54 *obj;

    switch (idx) {
        case 1:
            obj = (UnkStruct_02278a54 *) (self + 0x658);
            obj->Call();
            func_02016108(self + 0x658, func_0201c2a4(self, 4));
            func_ov078_02279670(self, 0);
            break;
        case 3:
            obj = (UnkStruct_02278a54 *) (self + 0x658);
            obj->Call();
            func_02016108(self + 0x658, func_0201c2a4(self, 4));
            func_ov078_02279670(self, 4);
            break;
        case 0:
            func_ov078_02279670(self, 0);
            break;
        case 8:
            func_ov078_02279670(self, 2);
            break;
    }
}
