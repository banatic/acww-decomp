/* func_ov127_02299abc @ 0x02299abc, 0x9c bytes, Thumb, module ov127
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x2826];
    short unk_2826;
    short unk_2828;
} UnkStruct_02299abc;

extern void func_ov127_02299868(UnkStruct_02299abc *s, int flag);

int func_ov127_02299abc(UnkStruct_02299abc *s, int value, int flag)
{
    short orig26 = *(volatile short *) &s->unk_2826;

    if (flag != 0 && s->unk_2828 != 0) {
        int old28 = s->unk_2828;
        s->unk_2828 = (short) (old28 + value);
        if (s->unk_2828 < -68) {
            s->unk_2828 = -68;
        } else if (s->unk_2828 > 76) {
            s->unk_2828 = 76;
        }
        if (s->unk_2828 * old28 < 0) {
            s->unk_2828 = 0;
        }
        return 1;
    }

    s->unk_2826 = (short) (*(volatile short *) &s->unk_2826 + value);
    if (s->unk_2826 < -24) {
        s->unk_2826 = -24;
        if (flag) {
            s->unk_2828 = (short) value;
        }
    } else if (s->unk_2826 > 84) {
        s->unk_2826 = 84;
        if (flag) {
            s->unk_2828 = (short) value;
        }
    }

    func_ov127_02299868(s, 1);

    if (orig26 != s->unk_2826) {
        return 1;
    }
    return 0;
}
