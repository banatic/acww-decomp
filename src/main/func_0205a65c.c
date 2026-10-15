/* func_0205a65c @ 0x0205a65c, 0x94 bytes, Thumb, module main
 * mwccarm 1.2/base -O2,s
 */

extern int func_0204f5e0(int, int, int, int, int, int);
extern int func_0204bcdc(void *);
extern int func_0204bc64(int);
extern int func_0205391c(int);
extern unsigned char data_021c9774[];

struct UnkStruct_0205a65c {
    int unk_00;
    int unk_04;
    unsigned int unk_08;
    unsigned int unk_0C;
};

void func_0205a65c(struct UnkStruct_0205a65c *s, int param1)
{
    unsigned char r7 = 0;
    do {
        int r5 = s->unk_04;
        while (r5 <= s->unk_0C) {
            int r4 = s->unk_00;
            if (r4 <= s->unk_08) {
                int hi_r5 = r5 >> 4;
                while (r4 <= s->unk_08) {
                    int hi_r4 = r4 >> 4;
                    int low_r4 = r4 - (hi_r4 << 4);
                    int low_r5 = r5 - (hi_r5 << 4);
                    int res = func_0204f5e0(param1, hi_r4, hi_r5, low_r4, low_r5, r7);
                    if (res != 0 && func_0204bcdc((void *) res) != 0) {
                        int res2 = func_0204bc64(res);
                        if (func_0205391c((int) res2) != 0) {
                            int idx = res2 >> 3;
                            res2 &= 7;
                            data_021c9774[idx] |= (1 << res2);
                        }
                    }
                    r4++;
                }
            }
            r5++;
        }
        r7++;
    } while (r7 < 2);
}
