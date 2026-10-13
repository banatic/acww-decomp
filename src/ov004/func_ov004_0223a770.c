/* func_ov004_0223a770 @ 0x0223a770, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a, b;
} UnkStruct_0223a770;
extern UnkStruct_0223a770 data_ov004_02247fb4[];
extern UnkStruct_0223a770 data_ov004_02247ce4;
UnkStruct_0223a770 *func_ov004_0223a770(int i)
{
    if (i < 0x6e9) {
        return &data_ov004_02247fb4[i];
    }
    return &data_ov004_02247ce4;
}
