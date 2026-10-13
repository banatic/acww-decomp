/* func_ov003_02228dfc @ 0x02228dfc, 0x24 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x80];
    int unk_80;
    char pad_84[0x1c8];
} UnkStruct_02228dfc;
extern UnkStruct_02228dfc data_ov003_0225f76c[];

int func_ov003_02228dfc(void *a, int i)
{
    int r = 0;
    UnkStruct_02228dfc *e;
    if (i >= 0 && i < 6) {
        e = &data_ov003_0225f76c[i];
        e->unk_80 = 2;
        r = 1;
    }
    return r;
}
