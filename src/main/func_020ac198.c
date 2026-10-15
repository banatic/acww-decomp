/* func_020ac198 @ 0x020ac198, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef unsigned short uint16_t;

struct UnkStruct_020ac198 {
    unsigned char pad_00[0x70];
    int unk_70;
};

extern uint16_t data_020d1de8[];
extern void func_020ac358(struct UnkStruct_020ac198 *, int, uint16_t);

int func_020ac198(struct UnkStruct_020ac198 *s, int arg1)
{
    uint16_t v;
    int result;

    v = data_020d1de8[s->unk_70];
    s->unk_70 = s->unk_70 + 1;
    if (s->unk_70 >= 5) {
        result = 1;
    } else {
        result = 0;
    }
    func_020ac358(s, arg1, v);
    return result;
}
