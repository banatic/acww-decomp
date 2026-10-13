/* func_ov009_02265660 @ 0x02265660, 0x20 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern void MTX_MultVec43(int, int, void *);
extern void func_0203f7d0(int, void *);

void func_ov009_02265660(int a, int b, int c)
{
    char buf[16];
    MTX_MultVec43(b, c, buf);
    func_0203f7d0(a, buf);
}
