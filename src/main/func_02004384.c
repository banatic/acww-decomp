/* func_02004384 @ 0x02004384, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021c67a4;
extern int data_021c67b8[];

void func_020f5054(int r0, int r1, void *r2);

void func_02004384(int r0, int r1, int *r2)
{
    if (r2 != 0 && data_021c67a4 != 0) {
        int sp[3];
        sp[0] = r2[0] - data_021c67b8[0];
        sp[1] = r2[1] - data_021c67b8[1];
        sp[2] = r2[2] - data_021c67b8[2];
        func_020f5054(r0, r1, sp);
    }
}
