/* func_02070d24 @ 0x02070d24, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned long long data[6];
} UnkStruct_02070d24;
extern UnkStruct_02070d24 data_021cfe68;
extern UnkStruct_02070d24 data_021cfe98[];
void func_02070d24(int idx)
{
    data_021cfe68 = data_021cfe98[idx];
}
