/* func_ov128_0229c794 @ 0x0229c794, 0x60 bytes, Thumb, module ov128
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fe54(void);
extern void func_ov128_0229b9f0(void *);
extern int func_ov128_0229b7ec(void *, int);
extern void func_ov002_0220b1a4(void *, int, int, int);
extern void func_ov127_02299de8(void *, int, int);
extern void func_ov128_0229bb60(void *, int);

int func_ov128_0229c794(void *param)
{
    func_0206fe54();
    func_ov128_0229b9f0(param);
    if (func_ov128_0229b7ec(param, 1)) {
        func_ov002_0220b1a4((char *) param + 0x94, 0, (*(int *) ((char *) param + 0x2d50)) >> 2, 1);
        func_ov127_02299de8((char *) param + 0x4a4, *(int *) ((char *) param + 0x2d50), 6);
    }
    if (func_ov128_0229b7ec(param, 1)) {
        func_ov128_0229bb60(param, *(int *) ((char *) param + 0x2d50));
    }
    return 1;
}
