/* func_ov107_0229d054 @ 0x0229d054, 0x44 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov107_0229d388(unsigned int object, unsigned int index);
extern int func_ov107_0229d36c(char *p0, int p1);
extern void func_ov094_0229ab1c(char *arg1, int arg2);
extern void func_ov094_0229b98c(char *arg);
extern void func_ov107_0229d098(char *p0);

void func_ov107_0229d054(char *p0, int p1)
{
    int temp;
    if (func_ov107_0229d388((unsigned int) p0, (unsigned int) p1) != 0) {
        temp = func_ov107_0229d36c(p0, p1);
        func_ov094_0229ab1c(p0 + 0x10c, temp);
        func_ov094_0229b98c(p0 + 0xb6c);
    } else {
        func_ov107_0229d098(p0);
    }
}
