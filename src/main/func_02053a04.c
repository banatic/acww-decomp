/* func_02053a04 @ 0x02053a04, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0206e6ec(void *p);
extern void *func_0206e7bc(void *p, int n);

extern unsigned char data_021c8c48[];

int func_02053a04(int param)
{
    void *p1;
    void *q1;
    int flag1;
    int v1;
    void *p2;
    void *q2;
    int flag2;
    int v2;

    if (param >= 1769) {
        v1 = 1768;
    } else {
        v1 = param;
    }
    p1 = func_0206e6ec((void *) data_021c8c48);
    q1 = func_0206e7bc(p1, v1);

    if (q1 != 0) {
        flag1 = (((unsigned char *) q1)[7] >> 2) & 1 ? 1 : 0;
    } else {
        flag1 = 0;
    }

    if (param >= 1769) {
        v2 = 1768;
    } else {
        v2 = param;
    }
    p2 = func_0206e6ec((void *) data_021c8c48);
    q2 = func_0206e7bc(p2, v2);

    if (flag1 != 0) {
        return 1;
    }

    if (q2 != 0) {
        flag2 = (((unsigned char *) q2)[7] >> 3) & 1 ? 1 : 0;
    } else {
        flag2 = 0;
    }

    if (flag2 != 0) {
        return 2;
    }
    return 0;
}
