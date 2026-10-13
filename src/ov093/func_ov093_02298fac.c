/* func_ov093_02298fac @ 0x02298fac, 0x10 bytes, Thumb, module ov093
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[5];
    unsigned char unk_05;
} UnkStruct_02298fac;

int func_ov093_02298fac(UnkStruct_02298fac *p, int mask)
{
    if (p->unk_05 & mask) {
        return 1;
    }
    return 0;
}
