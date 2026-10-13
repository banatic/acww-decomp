/* func_ov105_0229d3b4 @ 0x0229d3b4, 0x50 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov105_0229d76c(void);
extern int func_ov105_0229d75c(char *, int);
extern int func_ov105_0229d718(char *, int);
extern void func_ov105_0229d404(char *);
extern void func_ov094_0229b950(char *, int);
extern void func_ov094_0229ab5c(char *);

void func_ov105_0229d3b4(char *arg1, int arg2)
{
    if (func_ov105_0229d76c() || func_ov105_0229d75c(arg1, arg2)) {
        int ret = func_ov105_0229d718(arg1, arg2);
        func_ov094_0229b950(arg1 + 0xd5c, ret);
        func_ov094_0229ab5c(arg1 + 0x2fc);
    } else {
        func_ov105_0229d404(arg1);
    }
}
