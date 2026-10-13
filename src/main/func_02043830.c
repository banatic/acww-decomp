/* func_02043830 @ 0x02043830, 0xac bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b6660(void);
extern void *func_0204e414(void);
extern void *func_0204f5e0(void *ctx, int a, int b, int c, int d, int flag);
extern int func_0204f294(void *ctx, int x, int y);
extern int func_0204eda8(void *ctx, int x, int y);
extern int func_02042f20(void *table, int arg, int type, void *coords, int a5, int a6, int a7, int a8, int a9, int a10);
extern int data_021c7c48[];

int func_02043830(int a0, int *coords)
{
    void *ctx;
    int zero;
    int result;
    int sel;

    if (func_020b6660() == 0) {
        return ~0;
    }

    ctx = func_0204e414();
    zero = 0;
    result = ~zero;
    if (ctx == 0) {
        goto done;
    }

    {
        int x = coords[0];
        int y = coords[1];
        int hx = x >> 4;
        int hy = y >> 4;
        void *p = func_0204f5e0(ctx, hx, hy, x - (hx << 4), y - (hy << 4), zero);

        if (p == 0) {
            goto done;
        }
        if (*(unsigned short *) p != 0x1566) {
            goto done;
        }
        if (func_0204f294(ctx, coords[0], coords[1]) == 0) {
            goto done;
        }
        sel = 0xfd;
        if (func_0204eda8(ctx, coords[0], coords[1]) == 0) {
            sel = 0xfc;
        }
        {
            int local[2];
            local[0] = coords[0];
            local[1] = coords[1];
            result = func_02042f20(data_021c7c48, 0, 0x19, local, sel, 0xfff1, 0, 0, 0, a0);
        }
    }

done:
    return result;
}
