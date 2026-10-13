/* func_ov004_02222a30 @ 0x02222a30, 0x58 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204bcdc(void *p);
extern int func_0204bc64(void *p);

int func_ov004_02222a30(unsigned short *p, int flag)
{
    unsigned short local;
    int t1, t2;
    unsigned int cond;

    if (flag == 0) {
        if (func_0204bcdc(p) != 0) {
            local = 0x155e;
            t1 = func_0204bc64(p);
            t2 = func_0204bc64(&local);
            cond = (t1 == t2) ? 1 : 0;
        } else {
            cond = (*p == 0x155e) ? 1 : 0;
        }
        if (cond != 0) {
            return 1;
        }
    }
    return 0;
}
