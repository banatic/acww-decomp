/* func_ov080_02278a54 @ 0x02278a54, 0x44 bytes, Thumb, module ov080
 * mwccarm 1.2/base -O4,s
 */

struct VSub {
    virtual void vf0();
    virtual void vf1();
    virtual void vf2();
};

struct UnkStruct_02278a54 {
    char pad_00[0x658];
    VSub sub;
};

extern "C" void func_ov080_02278f00(UnkStruct_02278a54 *self, int kind);
extern "C" void *func_0201c2a4(UnkStruct_02278a54 *self, int a);
extern "C" void func_02016108(void *a, void *b);

extern "C" void func_ov080_02278a54(UnkStruct_02278a54 *self, int kind)
{
    switch (kind) {
        case 0: {
            void *tmp;
            self->sub.vf2();
            tmp = func_0201c2a4(self, 4);
            func_02016108(&self->sub, tmp);
            func_ov080_02278f00(self, 1);
            break;
        }
        case 8:
            func_ov080_02278f00(self, 0);
            break;
    }
}
