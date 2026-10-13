/* func_ov144_0229af28 @ 0x0229af28, 0x28 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f48(void *param, int flag);
extern void func_ov002_022080a0(void *param, int flag);
extern void func_ov144_0229a7c8(void *param);
extern int func_ov144_0229ae64(void *param);

int func_ov144_0229af28(void *param)
{
    if (func_ov002_02207f48(param, 0)) {
        func_ov002_022080a0(param, 2);
        func_ov144_0229a7c8(param);
    }
    return func_ov144_0229ae64(param);
}
