/* wfc_host_list: 3 functions, module ov146
 * mwccarm 1.2/base -O4,s
 * func_ov146_02299670 @ 0x02299670, 0x12 bytes, Thumb
 * func_ov146_02299660 @ 0x02299660, 0xe bytes, Thumb
 * func_ov146_02299650 @ 0x02299650, 0xe bytes, Thumb
 */

struct UnkStruct_02299670 {
    char pad_00[0xac];
    unsigned short unk_AC;
};

typedef struct {
    char pad_00[0xac];
    unsigned short unk_AC;
} UnkStruct_02299660;

struct FuncOvl146Struct {
    unsigned char pad_00[0xac];
    unsigned short unk_AC;
};

int func_ov146_02299670(struct UnkStruct_02299670 *s, unsigned short mask)
{
    if ((s->unk_AC & mask) != 0) {
        return 1;
    } else {
        return 0;
    }
}

void func_ov146_02299660(UnkStruct_02299660 *self, unsigned short mask)
{
    self->unk_AC = self->unk_AC | mask;
}

void func_ov146_02299650(struct FuncOvl146Struct *self, unsigned short bits)
{
    self->unk_AC &= ~bits;
}
