/* func_02042d94 @ 0x02042d94, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02042d14(void *a, void *b, int *c);
extern unsigned char data_020ca5d4[8];
extern void *func_0204e414(void);
void func_02042d94(void *param0, int *param1)
{
    void *result;
    int local1, local2;
    unsigned char *p;
    int i;

    result = func_0204e414();
    if (result == 0) {
        return;
    }

    {
        int *q = (int *) result + 1;
        local1 = q[0] << 4;
        local2 = q[1] << 4;
    }

    for (p = data_020ca5d4, i = 0; i < 8; p++, i++) {
        unsigned char b = *p;
        int r3 = param1[0] - ((b >> 4) - 8);
        int y = param1[1];
        int r2 = y - ((b & 0xF) - 8);
        int local[2];

        if (r3 < 0 || r3 >= local1 || r2 < 0 || r2 >= local2) {
            continue;
        }

        if (r3 == param1[0] && r2 == param1[1]) {
            continue;
        }

        local[0] = r3;
        local[1] = r2;
        if (func_02042d14(param0, result, local) != 0) {
            return;
        }
    }
}
