/* donation_list: 4 functions, module ov145
 * mwccarm 1.2/base -O4,s
 * func_ov145_0229967c @ 0x0229967c, 0x74 bytes, Thumb
 * func_ov145_02299668 @ 0x02299668, 0x12 bytes, Thumb
 * func_ov145_02299658 @ 0x02299658, 0xe bytes, Thumb
 * func_ov145_02299648 @ 0x02299648, 0xe bytes, Thumb
 */

typedef struct {
    char pad_00[0xb4];
    unsigned short unk_B4;
} UnkStruct_02299668;

struct UnkStruct_02299658 {
    char pad_00[0xb4];
    unsigned short unk_B4;
};

typedef struct {
    unsigned char pad_00[0xb4];
    unsigned short flags;
} UnkStruct_02299648;

extern void func_ov145_0229996c(void *self, int val);
extern void func_ov145_022996f0(void *self, int val);

void func_ov145_0229967c(char *self)
{
    unsigned char state = *(unsigned char *) (self + 0xc6);

    switch (state) {
        case 0:
            return;
        case 1:
            if (*(unsigned char *) (self + 0xc5) != 0) {
                *(unsigned char *) (self + 0xc5) = *(volatile unsigned char *) (self + 0xc5) - 1;
            } else {
                *(unsigned char *) (self + 0xc6) = 2;
                func_ov145_0229996c(self, *(unsigned char *) (self + 0xc1));
            }
            break;
        case 2:
            if (*(unsigned char *) (self + 0xc5) < 3) {
                *(unsigned char *) (self + 0xc5) = *(volatile unsigned char *) (self + 0xc5) + 1;
            } else {
                *(unsigned char *) (self + 0xc6) = 0;
                return;
            }
            break;
        default:
            break;
    }

    func_ov145_022996f0(self, *(unsigned char *) (self + 0xc5));
}

int func_ov145_02299668(UnkStruct_02299668 *self, int mask)
{
    if ((self->unk_B4 & mask) != 0) {
        return 1;
    }
    return 0;
}

void func_ov145_02299658(struct UnkStruct_02299658 *self, unsigned short mask)
{
    self->unk_B4 |= mask;
}

void func_ov145_02299648(UnkStruct_02299648 *p, unsigned short mask)
{
    p->flags = p->flags & ~mask;
}
