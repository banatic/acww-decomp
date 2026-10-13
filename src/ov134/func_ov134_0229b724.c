/* func_ov134_0229b724 @ 0x0229b724, 0x2c bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov134_0229b5ac(void *obj, int a3, int param3, int param4, int b9, int param6, int param7);

int func_ov134_0229b724(void *obj)
{
    int b9 = ((unsigned char *) obj)[0xb9];
    int a3 = ((unsigned char *) obj)[0xa3];
    return func_ov134_0229b5ac(obj, a3, 0x1c2, 3, b9, 15, 0);
}
