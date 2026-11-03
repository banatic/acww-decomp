/* room_object_4: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0220cdf8 @ 0x0220cdf8, 0xc bytes, Thumb
 * func_ov004_0220cdec @ 0x0220cdec, 0xc bytes, Thumb
 * func_ov004_0220cdd8 @ 0x0220cdd8, 0x14 bytes, Thumb
 */

int func_ov004_0220cdd8(void *self, int id);

int func_ov004_0220cdf8(int p0)
{
    return func_ov004_0220cdd8((void *) p0, 5);
}

int func_ov004_0220cdec(int a)
{
    return func_ov004_0220cdd8((void *) a, 7);
}

int func_ov004_0220cdd8(void *self, int id)
{
    if (*(int *) ((char *) self + 0x534) == id) {
        return 1;
    } else {
        return 0;
    }
}
