/* func_0200f888 @ 0x0200f888, 0xd4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0200f888 {
    unsigned char pad_00[0xb0];
    unsigned int flags_b0;
    unsigned char pad_B4[0x614];
    int unk_6C8;
    int unk_6CC;
    int unk_6D0;
    int unk_6D4;
    int unk_6D8;
    int unk_6DC;
    unsigned char pad_6E0[0x24];
    int unk_704;
    unsigned char pad_708[0x134];
    unsigned char unk_83C[0x44];
} UnkStruct_0200f888;

extern int func_0200f290(void *self, int cmd);
extern int func_020b1cb0(const int *p);
extern void func_0200443c(int receiver, unsigned short value);

void func_0200f888(UnkStruct_0200f888 *self)
{
    unsigned int flag;
    unsigned int flags = self->flags_b0;
    unsigned int cond0, cond1;
    int local[3];

    cond0 = (flags & 4) ? 1 : 0;
    if (cond0 > 0) {
        cond1 = (flags & 2) ? 1 : 0;
        if (cond1 > 0) {
            return;
        }
    }

    if (func_0200f290(self, 0xa) == 0) {
        return;
    }

    flag = (self->unk_704 == 2) ? 1 : 0;

    local[0] = (self->unk_6C8 + self->unk_6D4) >> 1;
    local[1] = (self->unk_6CC + self->unk_6D8) >> 1;
    local[2] = (self->unk_6D0 + self->unk_6DC) >> 1;

    if (func_0200f290(self, 0x19) != 0) {
        int value = func_020b1cb0(local);
        asm {
            add r1, value, #0
            ldr r0, =0x83c
            add r0, self, r0
            add r2, flag, #0
            bl func_0200443c
        }
    } else {
        int value = func_020b1cb0(local);
        asm {
            add r1, value, #0
            ldr r0, =0x880
            add r0, self, r0
            add r2, flag, #0
            bl func_0200443c
        }
    }
}
