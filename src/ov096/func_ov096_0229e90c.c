/* func_ov096_0229e90c @ 0x0229e90c, 0x4e bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_0229f830(void *param0, int param1);
extern int func_ov096_0229f820(void *param0, int param1);
extern void func_ov096_0229e9a0(void *param0, int param1);
extern void func_ov096_0229e95c(void *param0, int param1);
extern void func_ov096_0229e0f8(void *param0, unsigned short param1);

void func_ov096_0229e90c(void *param0, int param1)
{
    if (func_ov096_0229f830(param0, param1)) {
        func_ov096_0229e9a0(param0, param1);
    } else {
        if (func_ov096_0229f820(param0, param1)) {
            func_ov096_0229e95c(param0, param1);
        } else {
            if (param1 == 0x25) {
                func_ov096_0229e9a0(param0, param1);
                func_ov096_0229e0f8(param0, *(unsigned short *) ((char *) param0 + 0xac));
            }
        }
    }
}
