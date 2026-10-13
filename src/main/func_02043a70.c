/* func_02043a70 @ 0x02043a70, 0xd0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021c80bc;
extern int data_021c7c48[];

extern void *func_0204f5e0(void *obj, int a, int b, int c, int d, int flag);
extern int func_02042f20(void *table, int arg, int type, void *coords, int a5, int a6, int a7, int a8, int a9, int a10);

int func_02043a70(int arg0, int *coords)
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
            int saved;
            int mode;
            int v = *(unsigned short *) p;

            if (((v & 0xf000) >> 12) == 1) {
                type = 3;
                saved = v;
                mode = 0;
                goto check;
            } else {
                int x2 = coords[0];
                int y2 = coords[1];
                int hx2 = x2 >> 4;
                int hy2 = y2 >> 4;
                void *p2 = func_0204f5e0(obj, hx2, hy2, x2 - (hx2 << 4), y2 - (hy2 << 4), 1);

                if (p2 != 0) {
                    int v2 = *(unsigned short *) p2;
                    if (((v2 & 0xf000) >> 12) == 1) {
                        type = 3;
                        saved = v2;
                        mode = 1;
                    }
                }
            }

        check:
            if (type != 0) {
                int local[2];
                local[0] = coords[0];
                local[1] = coords[1];
                result = func_02042f20(data_021c7c48, arg0, type, local, 0xfff1, saved, 0, mode, 0, -1);
            }
        }
    }

done:
    return result;
}
