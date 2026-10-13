/* func_02030818 @ 0x02030818, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_01ffcb2c(int a, int b);
extern int *data_020da1a8;

int func_02030818(int *p)
{
    int x;
    int val;
    x = func_01ffcb2c(p[0] >> 13, p[2] >> 13);
    if (x >= 0x68 && x <= 0x6e) {
        x -= 0x68;
    } else {
        x = -1;
    }
    if (x >= 0) {
        val = *(int *) ((char *) data_020da1a8 + 0x12c);
        if (x == val) {
            return 1;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}
