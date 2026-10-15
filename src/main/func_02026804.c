/* func_02026804 @ 0x02026804, 0x128 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02026804_3 {
    int unk_00;
    u8 unk_04;
    u8 pad_05[3];
} UnkStruct_02026804_3;

extern UnkStruct_02026804_3 data_020d8ff0;
extern int *data_020d9cc0[];
extern int data_020d9fa0[];

typedef struct UnkStruct_02026804 {
    char pad_00[0x100];
    void *unk_100;
    char buffer104[30];
    u8 unk_122;
    char pad_123[0x15a - 0x123];
    u16 unk_15A;
    char pad_15C[0x164 - 0x15c];
    int int164;
} UnkStruct_02026804;

typedef struct UnkStruct_02026804_2 {
    char *unk_00;
    u8 unk_04;
} UnkStruct_02026804_2;

extern int func_0202d9c4(void *self);
extern int func_0209bc40(int a);
extern int func_0209b91c(int a);
extern int func_0209bd44(int a);
extern int func_0209b914(int a);
extern int func_0209bcc4(int a, int *idx);
extern int func_0209b8d0(int a);
extern int func_0207dd10(int a);
extern int func_02080864(int a, int b);
extern int func_020822b0(unsigned char *);
extern int func_02015dd4(void *self, int a, u8 *buf, void *d, u8 *p);
extern int func_0208150c(int a);
extern int func_020036e8(int a);
extern int func_0202da38(void *self, void *p1, void *p2, int len, int a, int f0, u8 f4, int x, int y);

void func_02026804(UnkStruct_02026804 *self, UnkStruct_02026804_2 *out)
{
    UnkStruct_02026804_3 local_data;
    u8 buf[2];
    int idx;
    int r4, r6;
    int a;

    local_data = data_020d8ff0;
    r6 = 0;
    r4 = func_0209bc40(func_0202d9c4(self));
    idx = 0;

    if (func_0209bd44(func_0209b91c(self->int164)) != 0) {
        r6 = func_0209b914(self->int164);
        r4 = func_0209bc40(func_0209b91c(self->int164));
    }

    func_0209bcc4(func_0202d9c4(self), &idx);

    if (r6 < func_0209b8d0(r4)) {
        if (idx < 5) {
            local_data.unk_00 = data_020d9cc0[idx][r6];
            if (r4 == 4) {
                r6 = *(int *) ((char *) self->unk_100 + 0x830);
                buf[0] = (u8) func_020822b0((unsigned char *) func_02080864(r6, func_0207dd10(r6)));
                buf[1] = 0;
                func_02015dd4(self, 0, buf, data_020d9fa0, &buf[1]);
            }
            if (r4 != 0 && r4 != 1) {
                self->unk_15A = 0x5e;
            }
        }
    }

    if (local_data.unk_00 != 0) {
        a = func_020036e8(func_0208150c(*(int *) ((char *) self->unk_100 + 0x830)));
        func_0202da38(self, self->buffer104, &self->unk_122, 30, a, local_data.unk_00, local_data.unk_04, 0, 0);
    }

    out->unk_00 = self->buffer104;
    out->unk_04 = self->unk_122;
}
