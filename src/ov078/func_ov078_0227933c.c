/* func_ov078_0227933c @ 0x0227933c, 0x22 bytes, Thumb, module ov078
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov078_02279360(void *);

int func_ov078_0227933c(void *self)
{
    if (*(int *) ((char *) self + 0x98) != 0) {
        if (func_ov078_02279360(self) != 0) {
            return 1;
        }
    }
    return 0;
}
