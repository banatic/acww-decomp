/* frame_ctrl: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02056e84 @ 0x02056e84, 0x2c bytes, Thumb
 * func_02056e60 @ 0x02056e60, 0x24 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x34];
    int unk_34;
    int unk_38;
} UnkStruct_02056e84;

typedef struct {
    unsigned char pad_00[0x34];
    unsigned int unk_34;
    unsigned int unk_38;
} UnkStruct_02056e60;

extern unsigned int __arm FX_Div(unsigned int, unsigned int);

int func_02056e84(UnkStruct_02056e84 *obj)
{
    if (obj->unk_38 != 0) {
        obj->unk_34 += obj->unk_38;

        if (obj->unk_34 >= 0x1000) {
            obj->unk_34 = 0x1000;
            obj->unk_38 = 0;
            return 1;
        }

        return 0;
    }

    return 1;
}

void func_02056e60(UnkStruct_02056e60 *s, unsigned int size)
{
    s->unk_34 = 0;
    if (size == 0) {
        s->unk_38 = 0;
    } else {
        s->unk_38 = FX_Div(0x1000, size << 12);
    }
}
