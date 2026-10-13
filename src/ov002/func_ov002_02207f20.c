/* func_ov002_02207f20 @ 0x02207f20, 0x1c bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02208558(void *r0, int r1, int r2, int r3, int r4);

void func_ov002_02207f20(void *r0, int r1, int r2, int r3, int r4)
{
    if (r2 == 0) {
        r2 = 4;
    }
    func_ov002_02208558((char *) r0 + 0x70, r1, r2, r3, r4);
}
