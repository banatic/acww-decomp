/* unit_type_info_4: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02031da8 @ 0x02031da8, 0x60 bytes, Thumb
 * func_02031d90 @ 0x02031d90, 0x18 bytes, Thumb
 * func_02031d78 @ 0x02031d78, 0x18 bytes, Thumb
 * func_02031d60 @ 0x02031d60, 0x18 bytes, Thumb
 * func_02031d48 @ 0x02031d48, 0x18 bytes, Thumb
 */

extern void VEC_Subtract(int *a, int *b, int *c);
extern unsigned char data_020c908b[];
extern unsigned char data_020c908a[];
extern unsigned char data_020c9089[];
extern unsigned char data_020c9088[];

int func_02031da8(int *arg)
{
    int local[6];

    local[0] = arg[0];
    local[1] = arg[1];
    local[2] = arg[2];
    local[3] = (local[0] & 0xffffe000) + 0x1000;
    local[4] = 0;
    local[5] = (local[2] & 0xffffe000) + 0x1000;

    VEC_Subtract(&local[0], &local[3], &local[0]);

    {
        int diff = local[2] - local[0];
        int sum = local[0] + local[2];

        if (sum > 0) {
            if (diff > 0) {
                return 2;
            } else {
                return 3;
            }
        } else {
            if (diff > 0) {
                return 1;
            } else {
                return 0;
            }
        }
    }
}

int func_02031d90(int r0)
{
    if (r0 < 0x7c) {
        return data_020c908b[r0 * 30];
    }
    return 0;
}

int func_02031d78(int r0)
{
    if (r0 < 0x7c) {
        return data_020c908a[r0 * 0x1e];
    }
    return 0;
}

unsigned char func_02031d60(int r0)
{
    if (r0 < 0x7c) {
        return data_020c9089[r0 * 30];
    }
    return 0;
}

int func_02031d48(int r0)
{
    if (r0 < 0x7c) {
        return data_020c9088[r0 * 30];
    }
    return 0;
}
