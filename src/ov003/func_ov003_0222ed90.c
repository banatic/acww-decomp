/* func_ov003_0222ed90 @ 0x0222ed90, 0x80 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov003_02260994[];
extern void func_ov003_0222fa20(void *a, void *b, int c);
extern void func_ov003_0222f6b0(void *a, void *b, int c, int d);
extern void func_ov003_0222fe18(void *a, void *b, int c);

void func_ov003_0222ed90(void *ctx)
{
    char *o = data_ov003_02260994;
    unsigned char i = 0;
    do {
        switch (*(unsigned char *) (o + 0x250)) {
            case 2:
                func_ov003_0222fa20(ctx, o, 1);
                break;
            case 3:
                if (*(int *) (o + 0x204) > 0x1000) {
                    func_ov003_0222f6b0(ctx, o, i, 2);
                }
                break;
            case 4:
                *(char *) (o + 0x251) = 0xa;
                func_ov003_0222fe18(ctx, o, 2);
                break;
        }
        o += 0x25c;
        i = (unsigned char) (i + 1);
    } while (i < 2);
}
