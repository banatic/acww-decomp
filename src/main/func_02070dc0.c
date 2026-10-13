/* func_02070dc0 @ 0x02070dc0, 0xd8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02071298(void *ctx, unsigned short *val);
extern void FX_Div(int a, int b);

void func_02070dc0(void *ctx)
{
    unsigned short vals[4];
    unsigned int r5;
    int r4 = 0;

    r5 = 0;
    do {
        vals[0] = (r5 < 20) ? (r5 * 4 + 0x3894) : 0x3894;
        if (func_02071298(ctx, &vals[0])) {
            r4++;
        }
        r5++;
    } while (r5 < 20);

    r5 = 0;
    do {
        vals[1] = (r5 < 56) ? (unsigned short) (r5 + 0x12e8) : 0x12e8;
        if (func_02071298(ctx, &vals[1])) {
            r4++;
        }
        r5++;
    } while (r5 < 56);

    r5 = 0;
    do {
        vals[2] = (r5 < 56) ? (unsigned short) (r5 + 0x12b0) : 0x12b0;
        if (func_02071298(ctx, &vals[2])) {
            r4++;
        }
        r5++;
    } while (r5 < 56);

    r5 = 0;
    do {
        vals[3] = (r5 < 52) ? (r5 * 4 + 0x450c) : 0x450c;
        if (func_02071298(ctx, &vals[3])) {
            r4++;
        }
        r5++;
    } while (r5 < 52);

    FX_Div((100 * r4) << 12, 0x000b8000);
}
