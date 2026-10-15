/* func_ov106_0229cd88 @ 0x0229cd88, 0x5c bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov106_0229d3a0(char *, char *);
extern int func_ov106_0229d390(char *, char *);
extern int func_ov106_0229d360(char *, char *);
extern int func_ov094_0229b8d8(char *, int);
extern int func_02066830(char *, int);
extern void func_ov094_0229b890(char *, int);

void func_ov106_0229cd88(char *self, char *arg)
{
    int result, temp;

    if (func_ov106_0229d3a0(self, arg) == 0) {
        if (func_ov106_0229d390(self, arg) == 0) {
            return;
        }
    }
    result = func_ov106_0229d360(self, arg);
    *(self + 0xb4) = 1;
    temp = func_ov094_0229b8d8(self + 0xb58, result);
    func_02066830(self + 0x4180, temp);
    func_ov094_0229b890(self + 0xb58, result);
}
