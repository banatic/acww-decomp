/* camera_grid_4: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208c834 @ 0x0208c834, 0x5c bytes, Thumb
 * func_0208c804 @ 0x0208c804, 0x30 bytes, Thumb
 * func_0208c7cc @ 0x0208c7cc, 0x38 bytes, Thumb
 * func_0208c734 @ 0x0208c734, 0x98 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0208c834 {
    void *unk_00;
    unsigned char pad_04[8];
    unsigned char pad_0C[0xb4];
    int unk_C0;
    int unk_C4;
    int unk_C8;
    int unk_CC;
    int unk_D0;
    unsigned char unk_D4;
};

typedef struct {
    void *unk_00;
    unsigned char pad_04[8];
    unsigned char unk_0C;
} UnkStruct_0208c804;

typedef struct {
    u8 pad_00[0xC];
    u8 arr[9][0x14];
    u32 unk_C0;
    u8 pad_C4[0xC];
    u32 unk_D0;
} UnkStruct_0208c734;

extern void func_0208af30(void *self);
extern char data_020e2250;
extern void func_0208a1f4(void *);
extern void func_0208a1f8(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void func_0208c668(void *);
extern void func_0208af00(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void func_020edb3c(void *);
extern int func_0208aef0(void *);
extern int func_0208aeec(void *);
extern int func_0208a1d0(void *);
extern int func_0208a1b0(void *, int);
extern int func_0208a198(void *, int);
extern void func_02088df8(int, int, int, int, int, int, int, int, int, int, int, int);

struct UnkStruct_0208c834 *func_0208c834(struct UnkStruct_0208c834 *self)
{
    func_0208af30(self);
    self->unk_00 = &data_020e2250;
    __cxa_vec_ctor((void *) ((char *) self + 0xc), 9, 0x14, (void (*)(void *)) func_0208a1f8,
                   (void (*)(void *)) func_0208a1f4);
    self->unk_C0 = 0;
    self->unk_C4 = 0;
    self->unk_C8 = 0;
    self->unk_CC = 0;
    self->unk_D0 = 0;
    self->unk_D4 = 0;
    return self;
}

void *func_0208c804(void *arg)
{
    UnkStruct_0208c804 *obj = (UnkStruct_0208c804 *) arg;

    obj->unk_00 = ((unsigned char *) &data_020e2250);
    func_0208c668(obj);
    __cxa_vec_cleanup((void *) (&obj->unk_0C), 9, 20, (void (*)(void *)) func_0208a1f4);
    func_0208af00(obj);
    return obj;
}

void *func_0208c7cc(void *p)
{
    *(void **) p = ((int *) &data_020e2250);
    func_0208c668(p);
    __cxa_vec_cleanup((void *) ((char *) p + 12), 9, 20, (void (*)(void *)) func_0208a1f4);
    func_0208af00(p);
    func_020edb3c(p);
    return p;
}

void func_0208c734(UnkStruct_0208c734 *self)
{
    int first;
    int second;
    int i;
    int zero;
    int minus1;

    if (self->unk_C0 == 0) {
        return;
    }

    first = func_0208aef0(self);
    second = func_0208aeec(self);

    minus1 = -1;
    zero = 0;
    for (i = 0; i < 9; i++) {
        int result1;
        int result2;
        int result3;
        void *elem;
        int mode;

        elem = (u8 *) self + 0xC + i * 0x14;
        result1 = func_0208a1d0(elem);
        if (result1 != 0) {
            result2 = func_0208a1b0(elem, minus1);
            result3 = func_0208a198(elem, minus1);
            mode = (i == self->unk_D0) ? 6 : 5;
            func_02088df8(zero, result1, first + result2, second + result3, mode, minus1, 0x1000, 0x1000, zero, minus1, zero,
                          zero);
        }
    }
}
