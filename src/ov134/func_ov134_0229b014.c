/* func_ov134_0229b014 @ 0x0229b014, 0x1e bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov134_0229ac38(void *argument0);
extern void func_ov134_0229af60(int);

int func_ov134_0229b014(int param)
{
    int result;
    if (func_ov134_0229ac38((void *) param) != 0) {
        func_ov134_0229af60(param);
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
