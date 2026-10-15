/* func_ov129_0229be04 @ 0x0229be04, 0x52 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov129_0229bd1c(void *argument0);
extern int func_ov127_022996d8(int a);
extern int func_ov127_022996c8(int a);
extern int func_ov127_022996e4(unsigned short *out, int a, int b);
extern void func_ov129_0229be58(void *obj, unsigned short val, int param);

void func_ov129_0229be04(void *obj, int param)
{
    unsigned short local[10];
    int v1, v2, count, i;

    if (param == 0xFF) {
        return;
    }
    if (func_ov129_0229bd1c(obj) == -1) {
        return;
    }

    v1 = func_ov127_022996d8(param);
    v2 = func_ov127_022996c8(param);
    count = func_ov127_022996e4(local, v1, v2);

    for (i = 0; i < count; i++) {
        func_ov129_0229be58(obj, local[i], param);
    }
}
