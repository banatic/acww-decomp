/* func_ov072_022796c8 @ 0x022796c8, 0x64 bytes, Thumb, module ov072
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202ec58(void *obj);
extern int func_02087178(int *ptr);
extern int func_020871a8(int *ptr);
extern void func_ov072_02279628(void *obj, int arg);
extern int data_021ebcd2;

int func_ov072_022796c8(void *obj)
{
    if (func_0202ec58(obj) == 0) {
        return 0;
    }
    {
        int *p = &data_021ebcd2;
        if (func_02087178(p) != 0) {
            if (func_020871a8(p) >= 5) {
                ((char *) obj)[0x718] = 1;
            }
            func_ov072_02279628(obj, 1);
        } else {
            func_ov072_02279628(obj, 0);
        }
    }
    ((unsigned int *) ((char *) obj + 0x4e8))[0] |= 2;
    return 1;
}
