/* func_ov076_02279230 @ 0x02279230, 0x48 bytes, Thumb, module ov076
 * mwccarm 1.2/base -O4,s
 */

extern int func_02019e00(unsigned char *p);
extern int func_02019de8(unsigned char *p);
extern void func_ov076_02279370(unsigned char *obj, int arg);

int func_ov076_02279230(unsigned char *obj)
{
    if (func_02019e00(obj + 0x564) == 3) {
        if (func_02019de8(obj + 0x564) != 0) {
            if (*(unsigned char *) (obj + 0x71c) == 0) {
                func_ov076_02279370(obj, 0);
            } else {
                func_ov076_02279370(obj, 4);
            }
        }
    }
    return 1;
}
