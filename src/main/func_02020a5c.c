/* func_02020a5c @ 0x02020a5c, 0x194 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02020a5c {
    u8 pad_00[0x830];
    void *unk_830;
} UnkStruct_02020a5c;

typedef struct UnkStruct_02020a5c_2 {
    u8 pad_00[0x100];
    UnkStruct_02020a5c *inner;
    char name[0x1e];
    u8 unk_122;
    u8 pad_123[0x13c - 0x123];
    u8 unk_13C;
} UnkStruct_02020a5c_2;

typedef struct {
    char *ptr;
    u8 byte;
} UnkStruct_02020a5c_3;

typedef struct {
    int a;
    u8 b;
} ErrData;

typedef struct {
    u8 pad_00[0x1d];
    u8 unk_1D;
} Obj2;

extern ErrData data_020c89f8;
extern ErrData data_020c8b28;
extern ErrData data_020c8ca0;
extern ErrData data_020c8a38;
extern ErrData data_020c8970;
extern ErrData data_020c8c88;

extern Obj2 *func_0207f270(int);
extern void *func_020794c4(unsigned char *);
extern int func_0202c424(UnkStruct_02020a5c_2 *self, int *out);
extern void func_0202bcd4(UnkStruct_02020a5c_2 *self);
extern int func_0202c420(UnkStruct_02020a5c_2 *self);
extern int func_0202c3f0(UnkStruct_02020a5c_2 *self);
extern int func_0202c3e4(UnkStruct_02020a5c_2 *self, int r7);
extern ErrData *func_0202c388(UnkStruct_02020a5c_2 *self, int *a, void *b);
extern int func_0202c31c(UnkStruct_02020a5c_2 *self, int *a, void *b);
extern ErrData *func_0202c2c4(UnkStruct_02020a5c_2 *self, int a);
extern int func_0202c2a8(UnkStruct_02020a5c_2 *self);
extern int func_0202c37c(UnkStruct_02020a5c_2 *self, int r7);
extern ErrData *func_0202c350(UnkStruct_02020a5c_2 *self);
extern int func_0202c27c(UnkStruct_02020a5c_2 *self, Obj2 *obj2);
extern ErrData *func_0202c254(UnkStruct_02020a5c_2 *self, int *a, Obj2 *obj2);
extern int func_0202c248(UnkStruct_02020a5c_2 *self, void *a);
extern int func_0202c23c(UnkStruct_02020a5c_2 *self, void *a);
extern int func_0202c230(UnkStruct_02020a5c_2 *self, void *a);
extern unsigned int func_0208150c(void *p);
extern int func_020036e8(unsigned char *);
extern int func_0202da38(UnkStruct_02020a5c_2 *self, char *name, u8 *byte, int len, int a, int b, int c, int d, int e);

int func_02020a5c(UnkStruct_02020a5c_2 *self, UnkStruct_02020a5c_3 *out)
{
    void *local_18;
    ErrData *err = 0;
    int flag;
    void *local_20;
    int local_24 = -1;
    int local_28;
    int local_2c;
    Obj2 *r6;
    int r7;

    local_18 = self->inner->unk_830;
    r6 = func_0207f270((int) local_18);
    local_20 = func_020794c4((unsigned char *) r6);
    flag = 0;
    local_28 = 0;
    local_2c = 0;
    r7 = func_0202c424(self, &local_2c);
    func_0202bcd4(self);

    if (func_0202c420(self) != 0) {
        err = &data_020c89f8;
        if (r7 == 0) {
            self->unk_13C = 1;
        }
    } else if (func_0202c3f0(self) != 0) {
        err = &data_020c8b28;
        if (r7 == 0) {
            self->unk_13C = 1;
        }
    } else if (func_0202c3e4(self, r7) != 0) {
        err = func_0202c388(self, &local_28, local_18);
    } else if (func_0202c31c(self, &local_24, (char *) self->inner + 0x5c) != 0) {
        err = func_0202c2c4(self, local_24);
    } else if (func_0202c2a8(self) != 0) {
        err = &data_020c8ca0;
    } else if (func_0202c37c(self, r7) != 0) {
        err = func_0202c350(self);
    } else if (func_0202c27c(self, r6) != 0) {
        err = func_0202c254(self, &local_28, r6);
    } else if (func_0202c248(self, local_20) != 0) {
        err = &data_020c8a38;
    } else if (func_0202c23c(self, local_20) != 0) {
        err = &data_020c8970;
    } else if (func_0202c230(self, local_20) != 0) {
        err = &data_020c8c88;
    }

    if (err != 0) {
        func_0202da38(self, self->name, &self->unk_122, 0x1e, func_020036e8((unsigned char *) func_0208150c(local_18)), err->a,
                      err->b, local_28, 0);
        flag = 1;
    }

    out->ptr = self->name;
    out->byte = self->unk_122;
    r6->unk_1D |= 4;
    return flag;
}
