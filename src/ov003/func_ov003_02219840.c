/* func_ov003_02219840 @ 0x02219840, 0x34 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x7f0];
    int unk_7F0;
} UnkStruct_02219840;

extern UnkStruct_02219840 *func_02096718(int);
extern int func_ov003_0220d69c(UnkStruct_02219840 *ptr, int a, int b);

int func_ov003_02219840(void)
{
    UnkStruct_02219840 *ptr = func_02096718(4);
    if (ptr != 0) {
        if (ptr->unk_7F0 == 0x89) {
            return 0;
        }
        return func_ov003_0220d69c(ptr, 6, -1);
    } else {
        return 0;
    }
}
