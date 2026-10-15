/* func_02039cf8 @ 0x02039cf8, 0xa0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209d368(void);
extern void func_02039cb4(void *);

struct UnkStruct_02039cf8 {
    char pad_00[0xc];
    int unk_0C;
    char pad_10[0x3c];
    int unk_4C;
    char pad_50[0x58];
    int unk_A8;
};

void func_02039cf8(struct UnkStruct_02039cf8 *self)
{
    int r4;
    int r6;
    int t;

    if (self->unk_0C == 0) {
        asm {
            ldr r0, =0x136
            mov r1, #4
        }
        r4 = func_0209d368() + 2;
    } else {
        asm {
            ldr r0, =0x12c
            mov r1, #4
        }
        r4 = func_0209d368() + 2;
    }

    if (self->unk_0C == 0) {
        asm {
            ldr r0, =0x136
            mov r1, #5
        }
        r6 = func_0209d368() - 6;
    } else {
        asm {
            ldr r0, =0x12c
            mov r1, #5
        }
        r6 = func_0209d368() + 6;
    }

    if (self->unk_0C == 0) {
        asm {
            ldr r0, =0x136
            mov r1, #6
        }
        t = func_0209d368() + 2;
    } else {
        asm {
            ldr r0, =0x12c
            mov r1, #6
        }
        t = func_0209d368() - 2;
    }

    if (self->unk_A8 > r4) {
        self->unk_4C += r6;
    } else {
        self->unk_4C += t;
    }

    self->unk_A8 -= 1;

    if (self->unk_A8 <= 0) {
        self->unk_4C = 0;
        func_02039cb4(self);
    }
}
