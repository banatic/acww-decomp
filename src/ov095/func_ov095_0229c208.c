/* func_ov095_0229c208 @ 0x0229c208, 0x22 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229c208 {
    char pad_00[0x1b];
    unsigned char unk_1B;
};
struct UnkStruct_0229c208_2;

extern void func_ov095_0229c22c(struct UnkStruct_0229c208 *, unsigned char, struct UnkStruct_0229c208_2 *, int);
extern void func_ov095_0229bf7c(struct UnkStruct_0229c208 *, struct UnkStruct_0229c208_2 *);

void func_ov095_0229c208(struct UnkStruct_0229c208 *param0, struct UnkStruct_0229c208_2 *param1)
{
    func_ov095_0229c22c(param0, param0->unk_1B, param1, 0);
    func_ov095_0229bf7c(param0, param1);
}
