/* func_02099794 @ 0x02099794, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct S_99794 {
    unsigned short x;
};

void func_02099794(char *p0, struct S_99794 v)
{
    *(unsigned short *) (p0 + 0x2412) = v.x;
}
