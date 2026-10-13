/* func_02041e48 @ 0x02041e48, 0xd8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021c75ac;
extern struct UnkStruct_02041e48 {
    int a;
    int b;
} data_021c75b8;
extern unsigned short data_021c76a8[96];
extern unsigned short data_021c75e8[96];

extern void MIi_CpuClear16(int value, void *dst, int size);
extern int FX_Sqrt(int value);

void func_02041e48(void)
{
    volatile unsigned short value[2];
    unsigned short *p;
    struct UnkStruct_02041e48 *p_data = &data_021c75b8;
    int i, r7, r6;

    if (data_021c75ac & 2) {
        p = data_021c75e8;
    } else {
        p = data_021c76a8;
    }

    {
        int b = p_data->b;
        if (b == 0) {
            value[0] = 0xff;
            MIi_CpuClear16(value[0], p, 0xc0);
            return;
        } else if (b == 0x1000) {
            value[1] = 0x8080;
            MIi_CpuClear16(value[1], data_021c75e8, 0x180);
            return;
        } else {
            r7 = (0x1000 - b) * 0xa0 >> 12;
            r6 = (r7 * r7) << 12;
            for (i = 0; i < 0x60; i++) {
                int delta = 0x60 - i;
                if (delta > r7) {
                    *p = 0x8080;
                } else {
                    int param = r6 - ((delta * delta) << 12);
                    int result = FX_Sqrt(param);
                    if (result < 0x80000) {
                        int t = (result >> 12);
                        t = 0x80 - t;
                        t &= 0xffff;
                        *p = (unsigned short) (((t << 8) & 0xff00) | ((0x100 - t) & 0xff));
                    } else {
                        *p = 0xff;
                    }
                }
                p++;
            }
        }
    }
}
