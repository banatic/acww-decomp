/* func_ov121_0229b968 @ 0x0229b968, 0x6c bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov121_02299c10(void *);
extern int func_ov121_02299a5c(void *, int);
extern int func_020b9bbc(void *, void *, int, int, int);
extern void func_ov121_02299a3c(void *, int);
extern int func_ov002_02207d5c(void *);
extern void func_ov121_0229a480(void *);
extern void func_ov002_022091cc(void *);

void func_ov121_0229b968(char *param)
{
    func_ov121_02299c10(param);
    if (func_ov121_02299a5c(param, 2)) {
        if (func_020b9bbc(param + 0x91c, param + 0x98c, 6, 0x800, 0)) {
            func_ov121_02299a3c(param, 2);
        }
    }
    if (func_ov002_02207d5c(param + 0x2d8)) {
        func_ov121_0229a480(param);
    }
    func_ov002_022091cc(param + 0x528);
}
