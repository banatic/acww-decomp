/* func_ov112_0229f9dc @ 0x0229f9dc, 0x50 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov112_0229fb8c(int, int);
extern void func_ov002_0220a4c8(void *receiver);

void func_ov112_0229f9dc(int r0, int r1)
{
    int r4;
    int r5;
    int r0_2;
    int r1_2;

    r5 = r0;
    r4 = r1;
    r4 = r4 * 3;
    r4 = r4 >> 1;
    if (r4 < 0) {
        r4 = 0;
    }
    if (r4 > 0x3c) {
        r4 = 0x3c;
    }
    func_ov112_0229fb8c(r5, r4);
    r0_2 = r5;
    r0_2 = r0_2 + 0xbb;
    r0_2 = *(unsigned char *) r0_2;
    r1_2 = r0_2 - r4;
    if (r1_2 >= 4 || r1_2 <= -4) {
        func_ov002_0220a4c8((void *) (r5 + 0x4234));
        *(unsigned char *) (r5 + 0xbb) = r4;
    }
}
