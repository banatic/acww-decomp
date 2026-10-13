/* func_02040164 @ 0x02040164, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02040164(short *r0, int r1);

void func_02040164(short *r0, int r1)
{
    int r4 = 0;
    short r3 = 0x63;
    short r2 = 5;
    while (r4 < r1) {
        *r0 = r3;
        *(r0 + 1) = r2;
        r0 += 6;
        r4++;
    }
}
