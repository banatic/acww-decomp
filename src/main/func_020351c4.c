/* func_020351c4 @ 0x020351c4, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[28];
} UnkStruct_020351c4;

extern UnkStruct_020351c4 *data_021c526c;
extern int func_02034f44(UnkStruct_020351c4 *ptr);

UnkStruct_020351c4 *func_020351c4(void)
{
    int idx = func_02034f44(data_021c526c);
    UnkStruct_020351c4 *result = 0;
    if (idx >= 0) {
        result = &data_021c526c[idx];
    }
    return result;
}
