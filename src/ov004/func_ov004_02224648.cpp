/* func_ov004_02224648 @ 0x02224648, 0x9c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

// Twin of func_ov048_022627e0; the two func_ov048_022635f4 calls pass 1 and 0 here instead of 2 and 1.

struct UnkStruct_02224648 {
    char pad_00[0x64];
    int unk_64;
};

struct UnkStruct_02224648_2 {
    virtual void f0();
    virtual void f1();
    virtual void f2();
};

struct UnkStruct_02224648_3 {
    char pad_00[0x658];
    UnkStruct_02224648_2 obj;
};

extern UnkStruct_02224648 *data_020ccf94;
extern "C" int func_0201c0e0(UnkStruct_02224648_3 *self);
extern "C" int func_0201c040(UnkStruct_02224648_3 *self, int *a, int *b);
extern "C" void func_0201c054(UnkStruct_02224648_3 *self, int p1, int p2, int p3);
extern "C" int func_0201c2a4(UnkStruct_02224648_3 *self, int p1);
extern "C" void func_02016108(UnkStruct_02224648_2 *obj, int val);
extern "C" void func_ov004_022249b4(UnkStruct_02224648_3 *self, int p1);
extern "C" int func_020a7278(void);

extern "C" int func_ov004_02224648(UnkStruct_02224648_3 *self)
{
    int a, b;

    if (func_0201c0e0(self) == 0) {
        goto done;
    }

    a = 4;
    b = 4;

    if (func_0201c040(self, &a, &b) != 0 && a == data_020ccf94->unk_64 && a == b) {
        func_0201c054(self, 1, data_020ccf94->unk_64, data_020ccf94->unk_64);
        self->obj.f2();
        func_02016108(&self->obj, func_0201c2a4(self, 4));
        func_ov004_022249b4(self, 1);
    } else {
        if (func_020a7278() != 0 && b == 4) {
            func_0201c054(self, 1, data_020ccf94->unk_64, 4);
            func_ov004_022249b4(self, 0);
        }
    }

done:
    return 1;
}
