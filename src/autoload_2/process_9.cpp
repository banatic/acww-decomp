/* process_9: 2 functions, module autoload_2
 * mwccarm 1.2/base -O4,p
 * func_020eebb4 @ 0x020eebb4, 0x94 bytes, ARM
 * func_020eeb04 @ 0x020eeb04, 0xb0 bytes, ARM
 */

#include "types.h"

class UnkStruct_020eebb4 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void call(int x);
    short unk_04;
    short count;
    int *arr;
};

class UnkStruct_020eeb04 {
  public:
    virtual void vfunc_00();
    virtual void vfunc_04();
    virtual short vfunc_08(int);
    short unk_04;
    short unk_06;
    volatile int *arr;
    u8 pad_0C[0x12 - 0xc];
    short unk_12;
};

extern "C" void func_020eebb4(UnkStruct_020eebb4 *self)
{
    if (self->arr == 0) {
        return;
    }
    if (self->unk_04 == 0) {
        return;
    }
    short *p = &self->count;
    self->count--;
    if (self->count < 0) {
        return;
    }
    do {
        self->call(self->arr[self->count]);
        (*p)--;
    } while (self->count >= 0);
}

extern "C" short func_020eeb04(UnkStruct_020eeb04 *self, int flag)
{
    short i;

    if (self->arr != 0) {
        if (self->unk_04 != 2) {
            goto body;
        }
    }
    return 2;
body:
    i = self->unk_06;
    if (self->arr[i] == 0) {
        goto end;
    }
    do {
        self->unk_04 = self->vfunc_08(self->arr[i]);
        if (self->unk_04 != 2) {
            goto end;
        }
        self->unk_06++;
        self->unk_12 = 0;
        if (flag == 0) {
            goto end;
        }
        i = self->unk_06;
    } while (self->arr[i] != 0);
end:
    return self->unk_04;
}
