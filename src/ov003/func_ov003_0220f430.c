/* func_ov003_0220f430 @ 0x0220f430, 0x28 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x2d0];
    int unk_2D0;
} UnkStruct_0220f430;

extern int func_02056f94(void *p);
extern void func_ov003_0220f3d8(void *p, int a, int b);

void func_ov003_0220f430(UnkStruct_0220f430 *param)
{
    if (func_02056f94(&param->unk_2D0) != 0) {
        func_ov003_0220f3d8(param, 6, -1);
    }
}
