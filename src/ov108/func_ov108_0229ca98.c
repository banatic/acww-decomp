/* func_ov108_0229ca98 @ 0x0229ca98, 0x30 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov108_0229cd70(void *arg0, int arg1);
extern int func_ov108_0229cd5c(void *arg0, int arg1);
extern void func_ov094_0229b938(void *ptr, int value);

void func_ov108_0229ca98(void *arg0, int arg1)
{
    if (func_ov108_0229cd70(arg0, arg1)) {
        int value = func_ov108_0229cd5c(arg0, arg1);
        func_ov094_0229b938((char *) arg0 + 0xd50, value);
    }
}
