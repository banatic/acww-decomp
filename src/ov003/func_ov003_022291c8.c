/* func_ov003_022291c8 @ 0x022291c8, 0x1c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0x60];
} UnkStruct_022291c8;
extern UnkStruct_022291c8 data_ov003_0225f4dc[];

int func_ov003_022291c8(void *a, unsigned int i)
{
    UnkStruct_022291c8 *e;
    if (i >= 4) {
        return 0;
    }
    e = &data_ov003_0225f4dc[i];
    e->unk_40 = 4;
    return 1;
}
