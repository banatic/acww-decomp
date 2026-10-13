/* func_02065284 @ 0x02065284, 0x98 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    unsigned short unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1C;
    int unk_20;
} UnkStruct_02065284;

extern unsigned short data_020ccb98[];

void func_02065284(UnkStruct_02065284 *obj)
{
    int scale, val, c, l, m;

    obj->unk_08 = 0;
    obj->unk_0C = -4096;
    obj->unk_10 = 0;
    obj->unk_1C += obj->unk_20;

    if (obj->unk_18 == 0) {
        if (obj->unk_1C >= 0x1000) {
            obj->unk_1C = 0x1000;
            obj->unk_20 = -614;
            obj->unk_18 = 1;
        }
    } else {
        if (obj->unk_1C < 0) {
            obj->unk_1C = 0;
            obj->unk_00 = 9;
            obj->unk_14 = 0;
        }
    }

    if (obj->unk_00 != 9) {
        scale = obj->unk_1C;
        val = data_020ccb98[obj->unk_00 - 1];
        c = ((((val & 0x7c00) >> 10) * scale) >> 12) << 10;
        l = ((val & 0x1f) * scale) >> 12;
        m = ((((val & 0x3e0) >> 5) * scale) >> 12) << 5;
        obj->unk_04 = (unsigned short) (c | (l | m));
    }
}
