/* func_ov083_02278b64 @ 0x02278b64, 0xfc bytes, Thumb, module ov083
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 unk_00;
    u8 unk_01;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06;
} UnkStruct_02278b64_2;

typedef struct UnkStruct_02278b64 {
    u8 pad_00[0x1e];
    u8 mode;
    u8 pad_1F[0x40 - 0x1f];
    void *callback;
    u8 pad_44[0xb4 - 0x44];
    int value;
    u16 result;
} UnkStruct_02278b64;

extern int func_020154b4(void *, void *, int, int, int);
extern int func_0209a000(void *, int);
extern void func_0206844c(void *, void *, void *);
extern int func_0202ea80(int, int);
extern int func_020984e8(void);
extern int func_02099670(int argument0);
extern void func_02088aac(void *argument0);
extern int func_02099fe8(void);
extern void func_020ad7c8(void *);
extern void func_02015de4(void *, void *, int, int);
extern u8 data_ov083_02279338[];
extern u8 data_ov083_02279348[];

void func_ov083_02278b64(UnkStruct_02278b64 *self)
{
    u8 *p = data_ov083_02279338;
    int r4 = 0xff;
    UnkStruct_02278b64_2 buf;

    if (self->value >= 0) {
        if (self->mode == 1 || self->mode == 4) {
            self->value = -2;
        }
        if (self->mode == 2) {
            buf.unk_02 = 0x1559;
            func_020154b4(self, &buf.unk_02, 0, 5, 0);
            buf.unk_04 = 0x1559;
            func_0209a000(&buf.unk_04, 0);
            buf.unk_00 = 4;
            func_0206844c(self->callback, &buf.unk_00, data_ov083_02279348);
        }
    } else {
        if (self->mode == 5 || self->mode == 6 || self->mode == 9) {
            if (func_0202ea80(0x1d, 1) == 0) {

                func_02088aac((void *) func_02099670(func_020984e8()));
                if (func_02099fe8() >= 0) {
                    r4 = 7;
                    func_020ad7c8(&buf.unk_06);
                    self->result = buf.unk_06;
                }
            }
        }
        if (self->mode == 7) {
            func_020154b4(self, &self->result, 0, 5, 0);
            func_0209a000(&self->result, 0);
            func_02015de4(self, &self->result, 0, 7);
            r4 = 8;
        }
        if (r4 != 0xff) {
            buf.unk_01 = (u8) r4;
            func_0206844c(self->callback, &buf.unk_01, p);
        }
    }
}
