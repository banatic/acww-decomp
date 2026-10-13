/* func_02071028 @ 0x02071028, 0xe8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020712ec(void *ctx, unsigned short *val);
extern void func_020713ec(void *ctx, unsigned short *val);

void func_02071028(void *ctx, int k)
{
    unsigned short vals[4];
    unsigned int i;
    int want;

    i = 0;
    want = (k & 3) + 1;
    do {
        vals[0] = (i < 0x34) ? (i * 4 + 0x450c) : 0x450c;
        if (func_020712ec(ctx, &vals[0]) == want) {
            func_020713ec(ctx, &vals[0]);
        }
        i++;
    } while (i < 0x34);
    i = 0;
    do {
        vals[1] = (i < 0x38) ? (unsigned short) (i + 0x12e8) : 0x12e8;
        if (func_020712ec(ctx, &vals[1]) == want) {
            func_020713ec(ctx, &vals[1]);
        }
        i++;
    } while (i < 0x38);
    i = 0;
    do {
        vals[2] = (i < 0x38) ? (unsigned short) (i + 0x12b0) : 0x12b0;
        if (func_020712ec(ctx, &vals[2]) == want) {
            func_020713ec(ctx, &vals[2]);
        }
        i++;
    } while (i < 0x38);
    i = 0;
    do {
        vals[3] = (i < 0x14) ? (i * 4 + 0x3894) : 0x3894;
        if (func_020712ec(ctx, &vals[3]) == want) {
            func_020713ec(ctx, &vals[3]);
        }
        i++;
    } while (i < 0x14);
}
