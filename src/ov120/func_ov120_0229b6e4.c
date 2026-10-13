/* func_ov120_0229b6e4 @ 0x0229b6e4, 0x38 bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40;
extern void func_ov120_0229aa30(void *p, int n);
extern void func_0208e95c(void *p, int n);
extern void func_ov002_02208098(void *p, int n);

void func_ov120_0229b6e4(void *param)
{
    if (!(data_021fbe40 & 1)) {
        func_0208e95c((char *) param + 0x674, 3);
        func_ov002_02208098(param, 8);
    } else {
        func_ov120_0229aa30(param, 1);
    }
}
