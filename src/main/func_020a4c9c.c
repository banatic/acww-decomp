/* func_020a4c9c @ 0x020a4c9c, 0xe8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_020a259c(void *, int);
extern int func_02073dd4(void *, unsigned int);
extern void func_0207428c(void);
extern int func_0209ffb0(void *receiver);
extern int func_020a0174(void);
extern int func_020a238c(void *);
extern int func_020a2120(void *, int);
extern void func_020a261c(void *object);
extern void func_020a25cc(void *receiver);
extern void func_020a4e94(void *, int);
typedef struct SomeObj {
    u8 pad_00[0x64];
    u32 unk_64;
} SomeObj;
extern SomeObj *data_020ccf94;
typedef struct UnkStruct_020a4c9c {
    u8 pad_00[0xA1];
    u8 mode;
    u8 pad_A2[0x6C];
    struct {
        u8 lo : 4;
        u8 hi : 4;
    } flags;
} UnkStruct_020a4c9c;
void func_020a4c9c(UnkStruct_020a4c9c *self)
{
    switch (self->mode) {
        case 0: {
            SomeObj *p;
            if (func_020a259c(self, 0) != 0) {
                p = data_020ccf94;
                if (func_02073dd4(p, p->unk_64) != 0) {
                    func_0207428c();
                    if (func_0209ffb0(self) != 0) {
                        func_020a0174();
                    }
                }
                self->mode = 1;
            }
            break;
        }

        case 1: {
            int r;
            r = func_020a238c(self);
            if (r == 1) {
                self->mode = 4;
            } else if (r == 3) {
            } else {
                self->mode = 2;
            }
            break;
        }

        case 2: {
            int r;
            r = func_020a2120(self, self->flags.hi);
            if (r == 1) {
                self->mode = 4;
            } else if (r == 0) {
                self->mode = 3;
            }
            break;
        }

        case 3: {
            int r;
            r = func_020a2120(self, self->flags.lo);
            if (r == 1) {
                self->mode = 4;
            } else if (r == 0) {
                self->mode = 6;
            }
            break;
        }

        case 4:
            func_020a261c(self);
            self->mode = 5;
            break;

        case 5:
            break;

        default:
            func_020a25cc(self);
            func_020a4e94(self, 0xc);
            break;
    }
}
