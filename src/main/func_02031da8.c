/* func_02031da8 @ 0x02031da8, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void VEC_Subtract(int *a, int *b, int *c);

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
