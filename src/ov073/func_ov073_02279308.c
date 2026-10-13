/* func_ov073_02279308 @ 0x02279308, 0x22 bytes, Thumb, module ov073
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02279308 {
    char pad_00[0x98];
    int unk_98;
};

extern int func_ov073_0227932c(struct UnkStruct_02279308 *a);

int func_ov073_02279308(struct UnkStruct_02279308 *a)
{
    if (a->unk_98) {
        if (func_ov073_0227932c(a)) {
            return 1;
        }
    }
    return 0;
}
