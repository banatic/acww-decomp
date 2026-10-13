/* func_ov083_02278c60 @ 0x02278c60, 0xc0 bytes, Thumb, module ov083
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_020984e8(void);
extern void func_02099640(void);
extern int func_02099e9c(u16 *p);
extern void func_0209e474(int *p);
extern void *func_0208602c(void);
extern int func_02086108(void *ctx, int a);
extern void func_020860f0(void *ctx, int a);
extern char data_ov083_02279338;
extern char data_ov083_02279348;

struct UnkStruct_02278c60 {
    void *ptr;
    unsigned char type;
};

struct UnkStruct_02278c60_2 {
    unsigned char pad[0xb0];
    void *ptr;
    int unk_B4;
};

void func_ov083_02278c60(struct UnkStruct_02278c60_2 *self, struct UnkStruct_02278c60 *out)
{
    struct {
        u16 h;
        u8 pad[2];
        int arr[2];
    } local;
    u8 v;

    func_020984e8();
    func_02099640();
    out->ptr = &data_ov083_02279338;

    if (self->unk_B4 == -1) {
        local.h = 0x37e0;
        self->unk_B4 = func_02099e9c(&local.h);
        if (self->unk_B4 >= 0) {
            out->ptr = &data_ov083_02279348;
            out->type = 0;
            return;
        }
    }

    local.arr[0] = 0;
    local.arr[1] = 0;
    func_0209e474(local.arr);

    v = ((unsigned char *) &local)[6];
    if (v < 6 || v >= 0x12) {
        out->type = 0;
        return;
    }

    if (func_02086108(func_0208602c(), 1) == 0) {
        func_020860f0(func_0208602c(), 1);
        v = ((unsigned char *) self->ptr)[0x718];
        if (v == 0) {
            out->type = 1;
            return;
        } else if (v >= 1 && v <= 5) {
            out->type = 2;
            return;
        } else {
            out->type = 3;
            return;
        }
    } else {
        out->type = 0xa;
        return;
    }
}
