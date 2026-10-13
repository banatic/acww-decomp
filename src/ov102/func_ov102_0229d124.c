/* func_ov102_0229d124 @ 0x0229d124, 0x52 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov102_0229d074(void);
extern int func_ov102_0229cff8(int, int);
extern int func_ov102_0229d034(int, int);
extern int func_ov094_02299b04(void);
extern int func_ov094_02299a54(int);

int func_ov102_0229d124(int r5, int r4)
{
    if (func_ov102_0229d074()) {
        return 0;
    }
    if (func_ov102_0229cff8(r5, r4)) {
        return 1;
    }
    r4 = func_ov102_0229d034(r5, r4);
    if (func_ov094_02299b04()) {
        return 1;
    }
    if (func_ov094_02299a54(r4)) {
        return 1;
    }
    return 0;
}
