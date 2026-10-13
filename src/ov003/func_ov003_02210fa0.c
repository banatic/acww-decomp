/* func_ov003_02210fa0 @ 0x02210fa0, 0x6c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_0221138c(void *);
extern int func_02073908(int *, int);
extern void func_0201100c(void *);
extern void func_0200f434(void *, void *);
extern void func_02010d64(void *);
extern void func_ov003_0221100c(void *);
extern int *data_020ccf94;

struct Params {
    char pad_00[0x2d8];
    int unk_2D8;
    char pad_2DC[0x7d4 - 0x2dc];
    int arr_0x7d4[3];
    char pad_7E0[0x800 - 0x7e0];
    int unk_800;
};

void func_ov003_02210fa0(struct Params *param)
{
    func_ov003_0221138c(param);
    if (func_02073908(data_020ccf94, param->unk_800) != 0) {
        if (((unsigned int) param->unk_2D8 << 4) >> 16 >= 0x19) {
            func_0201100c(param);
        }
    } else {
        int local[3];
        int *p = param->arr_0x7d4;
        local[0] = p[0];
        local[1] = p[1];
        local[2] = p[2];
        func_0200f434(param, local);
    }
    func_02010d64(param);
    func_ov003_0221100c(param);
}
