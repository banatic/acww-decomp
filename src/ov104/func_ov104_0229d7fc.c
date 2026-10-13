/* func_ov104_0229d7fc @ 0x0229d7fc, 0x34 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov104_0229da80(void *arg0, int arg1);
extern int func_ov104_0229da38(void *arg0, int arg1);
extern int func_ov094_0229b788(void *arg0, int arg1);

int func_ov104_0229d7fc(void *arg0, int arg1)
{
    if (func_ov104_0229da80(arg0, arg1)) {
        int temp = func_ov104_0229da38(arg0, arg1);
        return func_ov094_0229b788((char *) arg0 + 0xd58, temp);
    } else {
        return 0;
    }
}
