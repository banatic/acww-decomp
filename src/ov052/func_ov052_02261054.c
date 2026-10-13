/* func_ov052_02261054 @ 0x02261054, 0x70 bytes, Thumb, module ov052
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020adfa4(void *p, unsigned int a, unsigned int b);
extern int func_0204bcdc(void *p);
extern int func_0204bc64(void *p);
extern unsigned char data_021f3b30;

int func_ov052_02261054(void)
{
    int val, val2;
    unsigned int val3;
    unsigned short local8;
    unsigned int i = 0;
    void *p;
    int t1, t2, cond;

    val = i;
    val3 = i;
    val2 = i;

    while (i < 3) {
        p = func_020adfa4(&data_021f3b30, i, val3);
        if (func_0204bcdc(p) != 0) {
            local8 = 0x1547;
            t1 = func_0204bc64(p);
            t2 = func_0204bc64(&local8);
            cond = (t1 == t2) ? 1 : val;
        } else {
            cond = (*(unsigned short *) p == 0x1547) ? 1 : val2;
        }
        if (cond == 0) {
            return 0;
        }
        i++;
    }
    return 1;
}
