/* func_02070d4c @ 0x02070d4c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned long long data[6];
} UnkStruct_02070d4c;

extern UnkStruct_02070d4c data_021cfe68;
extern UnkStruct_02070d4c data_021cfe98[];

void func_02070d4c(int index)
{
    data_021cfe98[index] = data_021cfe68;
}
