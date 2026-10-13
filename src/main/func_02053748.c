/* func_02053748 @ 0x02053748, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0206e6e8(void *);
extern void *func_0206e7bc(void *, int);
extern int func_02053de4(int);

extern unsigned char data_021c8c48[];

int func_02053748(int param)
{
    int x;
    void *p;
    void *q;
    int flag;
    int c;

    if (param >= 0x6E9) {
        x = 0x6E8;
    } else {
        x = param;
    }
    p = func_0206e6e8((void *) data_021c8c48);
    q = func_0206e7bc(p, x);
    if (q != 0) {
        if ((((unsigned char *) q)[1] >> 7) & 1) {
            flag = 1;
        } else {
            flag = 0;
        }
    } else {
        flag = 0;
    }

    c = func_02053de4(param);
    if (c != 0x23 && c != 0x24 && c != 0x25) {
        return flag;
    }
    return 0;
}
