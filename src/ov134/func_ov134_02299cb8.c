/* func_ov134_02299cb8 @ 0x02299cb8, 0x56 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xd0];
    int unk_D0;
} UnkStruct_02299cb8;

extern int func_ov134_0229b884(UnkStruct_02299cb8 *a, int i);
extern int func_ov134_0229b848(UnkStruct_02299cb8 *a, int i, int *ptr);

int func_ov134_02299cb8(UnkStruct_02299cb8 *a, int threshold, unsigned int count)
{
    unsigned char i;
    int val;
    for (i = 0; i < count; i++) {
        val = func_ov134_0229b884(a, i);
        if (val != func_ov134_0229b848(a, i, &a->unk_D0)) {
            return 0;
        }
    }
    if (threshold <= func_ov134_0229b848(a, count, &a->unk_D0)) {
        return 0;
    }
    return 1;
}
