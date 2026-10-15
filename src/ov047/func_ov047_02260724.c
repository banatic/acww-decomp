/* func_ov047_02260724 @ 0x02260724, 0x34 bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short func_0206f9d8(int (*func)(unsigned short *, int));
extern int func_ov047_02261c00(unsigned short *value, int status);

void func_ov047_02260724(void *obj, int flag)
{
    if (flag == 0) {
        if (func_0206f9d8(func_ov047_02261c00) == 0) {
            *(int *) ((char *) obj + 0xd0) = 0x18;
        } else {
            *(int *) ((char *) obj + 0xd0) = 0x16;
        }
    } else {
        *(int *) ((char *) obj + 0xd0) = 0x3e;
    }
}
