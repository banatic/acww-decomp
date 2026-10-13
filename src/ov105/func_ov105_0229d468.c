/* func_ov105_0229d468 @ 0x0229d468, 0x34 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov105_0229d76c(char *, int);
extern int func_ov105_0229d718(char *, int);
extern int func_ov094_0229b788(char *, int);

int func_ov105_0229d468(char *arg1, int arg2)
{
    if (func_ov105_0229d76c(arg1, arg2)) {
        return func_ov094_0229b788(arg1 + 0xd5c, func_ov105_0229d718(arg1, arg2));
    } else {
        return 0;
    }
}
