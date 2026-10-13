/* func_02096204 @ 0x02096204, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int *func_02096260(void *);
extern char *func_02096254(void *);
extern int *func_02096244(void *);
extern short *func_02096238(void *);

void func_02096204(void *param)
{
    int *a;
    char *b;
    int *c;
    short *d;

    a = func_02096260(param);
    *a = 0x93;

    b = func_02096254(param);
    *b = 0x33;

    c = func_02096244(param);
    c[0] = 0;
    c[1] = 0;
    c[2] = 0;

    d = func_02096238(param);
    *d = 0;
}
