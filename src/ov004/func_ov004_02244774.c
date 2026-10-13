/* func_ov004_02244774 @ 0x02244774, 0x4c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020e8870(short *, int, int);
void func_ov004_02244774(char *self, int a, int b)
{
    short t = *(short *) (self + 0x192);
    if (func_020e8870(&t, *(short *) (self + 0xac), 0xe38) != 0) {
        *(short *) (self + 0x172) = (short) b;
        *(char *) (self + 0x170) = (char) a;
    }
    *(short *) (self + 0x192) = t;
}
