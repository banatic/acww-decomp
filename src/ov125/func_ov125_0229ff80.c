/* func_ov125_0229ff80 @ 0x0229ff80, 0x44 bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220909c(void *ptr);
extern void func_ov002_022096d8(void *ptr, int value);
extern int func_0208e4bc(void *ptr);
extern void func_ov125_0229f994(void *ptr);
extern unsigned char *func_ov002_02208098(void *ptr, unsigned char value);

void func_ov125_0229ff80(void *param)
{
    if (func_ov002_0220909c((char *) param + 0x180)) {
        func_ov002_022096d8((char *) param + 0x180, 0);
        if (func_0208e4bc((char *) param + 0x644)) {
            func_ov125_0229f994(param);
        }
        func_ov002_02208098(param, 9);
    }
}
