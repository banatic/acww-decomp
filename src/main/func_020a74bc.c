/* func_020a74bc @ 0x020a74bc, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Context {
    unsigned char pad_00[0x110];
    unsigned char *unk_110;
} Context;

extern Context *data_020ccf94;
extern void (*data_020d1c2c)(int);
extern void func_020733ac(Context *);
extern unsigned char *func_020733c4(Context *);
extern int func_020b65c4(void);
extern void func_020733a0(Context *, int);
extern void MI_CpuCopy8(void *, const void *, unsigned int);

void func_020a74bc(void)
{
    Context *ctx = data_020ccf94;
    unsigned char *p6;
    unsigned char *p5;
    unsigned char *old;
    unsigned char *cur;
    unsigned char buf[8];
    int diff;
    int distance;
    int x;

    func_020733ac(ctx);
    p6 = func_020733c4(ctx);
    p5 = p6 + 2;
    x = func_020b65c4();
    old = ctx->unk_110 = p5 + 4;
    data_020d1c2c(x);
    cur = ctx->unk_110;
    diff = (int) (cur - old);
    if (diff != 0) {
        *(unsigned short *) (buf + 2) = (unsigned short) diff;
        buf[4] = 0;
        MI_CpuCopy8(buf + 2, p5, 4);
        p5 = cur;
    }
    distance = (int) (p5 - p6);
    *(unsigned short *) buf = (unsigned short) (distance - 2);
    MI_CpuCopy8(buf, p6, 2);
    func_020733a0(ctx, distance);
}
