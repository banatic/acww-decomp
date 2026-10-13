/* func_ov071_02279570 @ 0x02279570, 0x22 bytes, Thumb, module ov071
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov071_02279594(void *);

int func_ov071_02279570(void *r0)
{
    if (*(int *) ((char *) r0 + 0x98) != 0) {
        if (func_ov071_02279594(r0)) {
            return 1;
        }
    }
    return 0;
}
