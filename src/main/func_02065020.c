/* func_02065020 @ 0x02065020, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b3658(void *p);
struct GlobalData {
    unsigned char pad_00[0x16a];
    unsigned short unk_16A;
    unsigned short unk_16C;
};
extern struct GlobalData *data_021cd864;
struct Arg {
    unsigned char pad_00[0x14];
    unsigned char flag;
    unsigned char pad_15[3];
    unsigned int mode;
    unsigned char pad_1C[0x18];
    unsigned short result;
};
void func_02065020(struct Arg *arg)
{
    int t;
    struct GlobalData *g;
    unsigned short raw1;
    unsigned int lm;
    unsigned short raw2;
    int low;
    int mid;
    int high;
    unsigned int low1;
    unsigned int low2;
    unsigned int mid1;
    unsigned int mid2;
    unsigned int high1;
    unsigned int high2;
    t = func_020b3658(((char *) arg) + 0x1c);
    g = data_021cd864;
    raw1 = g->unk_16C;
    raw2 = g->unk_16A;
    low1 = ((unsigned int) (raw1 << 27)) >> 27;
    low2 = ((unsigned int) (raw2 << 27)) >> 27;
    low = low1 + ((((int) (low2 - low1)) * t) >> 12);
    mid1 = ((unsigned int) (raw1 << 22)) >> 27;
    mid2 = ((unsigned int) (raw2 << 22)) >> 27;
    mid = mid1 + ((((int) (mid2 - mid1)) * t) >> 12);
    high1 = ((unsigned int) (raw1 << 17)) >> 27;
    high2 = ((unsigned int) (raw2 << 17)) >> 27;
    high = high1 + ((((int) (high2 - high1)) * t) >> 12);
    if (arg->flag == 0) {
        if (arg->mode != 0) {
            low = 0;
            mid = 0;
            high = 0;
        }
    } else if (arg->mode == 2) {
        low = 16;
        mid = 16;
        high = 13;
    }
    lm = low | (mid << 5);
    arg->result = (high << 10) | lm;
}
