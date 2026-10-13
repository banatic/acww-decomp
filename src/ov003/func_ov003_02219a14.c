/* func_ov003_02219a14 @ 0x02219a14, 0x2c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct Triple {
    int a;
    int b;
    int c;
};
extern int func_02096718(int);
extern int func_ov003_0220f538(int, struct Triple, int, int);
int func_ov003_02219a14(struct Triple *param)
{
    int r = func_02096718(4);
    if (r) {
        return func_ov003_0220f538(r, *param, 6, -1);
    }
    return 0;
}
