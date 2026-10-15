/* func_02004bbc @ 0x02004bbc, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020952e0(void);
extern __arm int func_020e9968(int a, int b, int c);
extern void *__arm memset(int a, int b, int c);
extern int data_021c9ab4;

int func_02004bbc(int arg)
{
    int var;
    int tmp;
    int result;

    var = data_021c9ab4;
    tmp = func_020952e0();
    result = func_020e9968(var, arg, tmp);
    if (result == 0) {
        return 0;
    } else {
        memset(result, 0, arg);
        return result;
    }
}
