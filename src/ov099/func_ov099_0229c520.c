/* func_ov099_0229c520 @ 0x0229c520, 0x4c bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207d24(int, int);
extern void func_ov002_0220a374(int, int);
extern void func_ov002_02208098(int, int);

void func_ov099_0229c520(int r0, int r1)
{
    int r5 = r0;
    int r4 = r1;
    int r0_2;
    int r1_2;
    int r0_3;
    int r1_3;
    int r0_4;
    int r1_4;

    r0_2 = r5 + 0x218c;
    r1_2 = 1;
    func_ov002_02207d24(r0_2, r1_2);

    r0_3 = r5 + 0x8d;
    r1_3 = *(unsigned char *) r0_3;
    r0_4 = r5 + 0x290a;
    *(unsigned char *) r0_4 = r1_3;

    r0_4 = r5 + 0x2909;
    *(unsigned char *) r0_4 = r4;

    r0_4 = r5 + 0x2274;
    r1_4 = 6;
    func_ov002_0220a374(r0_4, r1_4);

    r0_4 = r5 + 0;
    r1_4 = 0xe;
    func_ov002_02208098(r0_4, r1_4);
}
