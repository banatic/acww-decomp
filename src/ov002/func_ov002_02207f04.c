/* func_ov002_02207f04 @ 0x02207f04, 0x1c bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220851c(int p0, int p1, int p2, int p3, int p4);

void func_ov002_02207f04(int p0, int p1, int p2, int p3, int p4)
{
    if (p2 == 0) {
        p2 = 3;
    }
    func_ov002_0220851c(p0 + 0x70, p1, p2, p3, p4);
}
