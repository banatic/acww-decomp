/* func_0209dcdc @ 0x0209dcdc, 0xc0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char d, m, y;
} Date;
extern int func_0209dd9c(const Date *a, const Date *b);
extern unsigned short data_020d1b5c[2][13];
int func_0209dcdc(const Date *p, const Date *q)
{
    int sign = 1;
    int rem;
    int adj;
    int days;
    int d0;
    int m0;
    int y0;
    int diff;
    int d1;
    int y1;
    unsigned int lp;
    int m1;
    unsigned short (*tbl)[13] = data_020d1b5c;

    if (func_0209dd9c(p, q)) {
        d0 = q->d;
        m0 = q->m;
        y0 = q->y;
        d1 = p->d;
        m1 = p->m;
        y1 = p->y;
    } else {
        d0 = p->d;
        m0 = p->m;
        y0 = p->y;
        d1 = q->d;
        m1 = q->m;
        y1 = q->y;
        sign = -1;
    }
    diff = y1 - y0;
    rem = diff & 3;
    y0 = y0 & 3;
    adj = ((4 - y0) & 3) < rem;
    days = adj + (1461 * (diff >> 2) + 365 * rem);
    days = days + (d1 - 1);
    lp = ((y1 & 3) == 0);
    days = days + tbl[lp][m1 - 1];
    days = days - (d0 - 1);
    lp = (y0 == 0);
    days = days - tbl[lp][m0 - 1];
    return days * sign;
}
