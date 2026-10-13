/* func_ov003_0222c1f4 @ 0x0222c1f4, 0x20 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x34];
    char unk_34;
    char pad_35[0x2b];
} UnkStruct_0222c1f4;
extern UnkStruct_0222c1f4 data_ov003_0225f35c[];
extern char data_ov003_0225f390[];
void *func_ov003_0222c1f4(int i)
{
    if (i < 0 || i >= 4) {
        return data_ov003_0225f390;
    }
    return &data_ov003_0225f35c[i].unk_34;
}
