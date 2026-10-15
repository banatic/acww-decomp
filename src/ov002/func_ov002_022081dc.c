/* func_ov002_022081dc @ 0x022081dc, 0x18 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_022081dc(void *object);
extern int func_020ee550(void *object);

int func_ov002_022081dc(void *object)
{
    if (func_020ee550(object) != 0) {
        return 1;
    } else {
        return 0;
    }
}
