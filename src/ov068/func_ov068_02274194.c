/* func_ov068_02274194 @ 0x02274194, 0x50 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02274194 {
    char pad_00[0x652];
    unsigned short unk_652;
    char pad_654[0xf7];
    char unk_74B;
    char unk_74C;
};

struct UnkStruct_02274194_2 {
    char pad_00[0xb4];
    struct UnkStruct_02274194 *inner;
};

extern unsigned short func_ov068_02273980(void);

void func_ov068_02274194(struct UnkStruct_02274194_2 *obj, int cond)
{
    if (cond == 0) {
        obj->inner->unk_74C = 1;
    } else {
        obj->inner->unk_74C = 0;
        obj->inner->unk_74B = 0;
        obj->inner->unk_652 =
            (unsigned short) ((void) *(struct UnkStruct_02274194 *volatile *) &obj->inner, func_ov068_02273980());
    }
}
