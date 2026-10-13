/* func_ov054_02261490 @ 0x02261490, 0x22 bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02261490 {
    char pad_00[0xB0];
    void *unk_B0;
};

extern int func_ov054_02260498(void *);
extern void func_020a1894(void);
extern void func_ov054_02261cc4(struct UnkStruct_02261490 *, int);

void func_ov054_02261490(struct UnkStruct_02261490 *obj)
{
    if (func_ov054_02260498(obj->unk_B0) != 0) {
        func_020a1894();
        func_ov054_02261cc4(obj, 0xF);
    }
}
