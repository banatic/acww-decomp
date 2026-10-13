/* func_ov075_02278e18 @ 0x02278e18, 0x28 bytes, Thumb, module ov075
 * mwccarm 1.2/base -O4,s
 */

extern void func_020147e0(void *dst, void *src, int size);

int func_ov075_02278e18(void *self)
{
    if (*(unsigned char *) ((char *) self + 0x718) == 0) {
        func_020147e0((char *) self + 0x618, 0, 0);
    }
    return 1;
}
