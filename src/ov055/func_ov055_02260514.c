/* func_ov055_02260514 @ 0x02260514, 0x30 bytes, Thumb, module ov055
 * mwccarm 1.2/base -O4,s
 */

extern int func_02090040(int arg);
extern int func_020a145c(void);

void func_ov055_02260514(void *self)
{
    int result;

    if (((unsigned char *) self)[0x710]) {
        return;
    }
    result = ((void) (func_02090040(4)), func_020a145c());
    if (result == 1 || result == 4) {
        ((unsigned char *) self)[0x710] = 1;
    }
}
