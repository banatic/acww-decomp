/* func_02056e84 @ 0x02056e84, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x34];
    int unk_34;
    int unk_38;
} UnkStruct_02056e84;

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
