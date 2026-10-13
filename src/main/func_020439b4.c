/* func_020439b4 @ 0x020439b4, 0x98 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021c80bc;
extern int data_021c7c48[];

extern void *func_0204f5e0(void *obj, int a, int b, int c, int d, int flag);
extern int func_02042f20(void *table, int arg, int type, void *coords, int a5, int a6, int a7, int a8, int a9, int a10);

int func_020439b4(int arg0, int *coords, int mode)
{
    void *obj = data_021c80bc;
    int zero = 0;
    int result = ~zero;

    if (obj == 0) {
        goto done;
    }

    {
        int x = coords[0];
        int y = coords[1];
        int hx = x >> 4;
        int hy = y >> 4;
        void *p = func_0204f5e0(obj, hx, hy, x - (hx << 4), y - (hy << 4), zero);

        if (p == 0) {
            goto done;
        }

        {
            int type = 0;
            int a5 = 0xfff1;
            int ok = 0;
            unsigned int v = *(unsigned short *) p;

            if (v >= 0xfc && v <= 0xfd) {
                ok = 1;
            }
            if (ok != 0 && mode != 2) {
                type = 0x14;
                a5 = 0xfff1;
            }
            if (type != 0) {
                int local[2];
                local[0] = coords[0];
                local[1] = coords[1];
                result = func_02042f20(data_021c7c48, arg0, type, local, a5, a5, 1, 0, 0, -1);
            }
        }
    }

done:
    return result;
}
