/* func_ov004_02225a14 @ 0x02225a14, 0x4c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern char *data_ov004_02258200;
extern int func_02016884(void *a, int b, void *c);

int func_ov004_02225a14(void)
{
    char *p = data_ov004_02258200;

    if (p != 0) {
        if (func_02016884(p + 0x334, 0xff, p + 0x2a0) != 0) {
            if (*(int *) (data_ov004_02258200 + 0x654) == 0) {
                return 1;
            }
        }
        return 0;
    }
    return 1;
}
