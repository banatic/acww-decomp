/* func_ov003_02215db8 @ 0x02215db8, 0x44 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f94(void *p);
extern int func_ov003_02215bc0(void *p, int a, int b);
extern int func_02073908(void *p, int n);
extern void func_0203ae84(void);
extern void *data_020ccf94;

struct Param0 {
    char pad_00[0x2d0];
    char unk_2D0[0x800 - 0x2d0];
    int unk_800;
};

void func_ov003_02215db8(struct Param0 *param0)
{
    if (func_02056f94(&param0->unk_2D0)) {
        func_ov003_02215bc0(param0, 6, -1);
        if (func_02073908(data_020ccf94, param0->unk_800)) {
            func_0203ae84();
        }
    }
}
