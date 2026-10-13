/* func_ov075_022790e4 @ 0x022790e4, 0x22 bytes, Thumb, module ov075
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov075_02279108(void *);

int func_ov075_022790e4(void *self)
{
    if (*(int *) ((char *) self + 0x98) != 0) {
        if (func_ov075_02279108(self)) {
            return 1;
        }
    }
    return 0;
}
