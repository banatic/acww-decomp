/* func_ov094_0229ace4 @ 0x0229ace4, 0x3c bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229ace4;

extern void func_ov094_0229ad64(struct UnkStruct_0229ace4 *, int, unsigned short *, int);

struct UnkStruct_0229ace4 {
    char pad_00[0xa34];
    unsigned short *unk_A34;
};

void func_ov094_0229ace4(struct UnkStruct_0229ace4 *p, unsigned short *arr)
{
    int i;
    int param = 15;
    int zero = 0;
    unsigned short val;

    for (i = 0; i < 15; i++) {
        val = arr[i];
        func_ov094_0229ad64(p, param, &val, zero);
        param++;
    }
    p->unk_A34 = arr;
}
