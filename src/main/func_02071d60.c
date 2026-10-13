/* func_02071d60 @ 0x02071d60, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02071d60 {
    char pad_00[0x64];
    int unk_64;
};

extern struct UnkStruct_02071d60 *data_020ccf94;
extern int func_02073d90(struct UnkStruct_02071d60 *p);

int func_02071d60(int param)
{
    struct UnkStruct_02071d60 *p = data_020ccf94;
    if (func_02073d90(p) && param == 9) {
        return p->unk_64;
    }
    return param;
}
