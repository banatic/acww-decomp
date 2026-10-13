/* func_ov107_0229d054 @ 0x0229d054, 0x44 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov107_0229d388(void);
extern int func_ov107_0229d36c(char *p0, int p1);
extern void func_ov094_0229ab1c(char *arg1, int arg2);
extern int func_ov094_0229b98c(char *arg);
extern int func_ov107_0229d098(char *p0);

int func_ov107_0229d054(char *p0, int p1)
{
    int temp;
    if (func_ov107_0229d388() != 0) {
        temp = func_ov107_0229d36c(p0, p1);
        func_ov094_0229ab1c(p0 + 0x10c, temp);
        return func_ov094_0229b98c(p0 + 0xb6c);
    } else {
        return func_ov107_0229d098(p0);
    }
}
