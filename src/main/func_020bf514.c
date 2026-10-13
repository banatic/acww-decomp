/* func_020bf514 @ 0x020bf514, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021f6cdc;

struct UnkStruct_020bf514 {
    char pad_00[0x28];
    int unk_28;
    short sfield;
    unsigned char flag;
};

extern void func_020bf3c8(struct UnkStruct_020bf514 *s, int a2);

int func_020bf514(struct UnkStruct_020bf514 *s, int a1, int a2, int a3)
{
    int flag = 0;

    if (s->flag) {
        s->unk_28 += a1;
        if (s->unk_28 > data_021f6cdc) {
            flag = 1;
        }
    } else {
        s->unk_28 -= a1;
        if (s->unk_28 < 0) {
            flag = 1;
        }
    }

    if (!flag) {
        s->sfield = s->sfield + a3;
        func_020bf3c8(s, a2);
    }

    return flag;
}
