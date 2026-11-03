/* calendar: 12 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209ded0 @ 0x0209ded0, 0xc bytes, Thumb
 * func_0209de88 @ 0x0209de88, 0x48 bytes, Thumb
 * func_0209de44 @ 0x0209de44, 0x44 bytes, Thumb
 * func_0209de24 @ 0x0209de24, 0x20 bytes, Thumb
 * func_0209ddd4 @ 0x0209ddd4, 0x4e bytes, Thumb
 * func_0209dd9c @ 0x0209dd9c, 0x36 bytes, Thumb
 * func_0209dcdc @ 0x0209dcdc, 0xc0 bytes, Thumb
 * func_0209dcac @ 0x0209dcac, 0x2e bytes, Thumb
 * func_0209dc74 @ 0x0209dc74, 0x38 bytes, Thumb
 * func_0209dc48 @ 0x0209dc48, 0x2a bytes, Thumb
 * func_0209dc10 @ 0x0209dc10, 0x38 bytes, Thumb
 * func_0209dbe4 @ 0x0209dbe4, 0x2a bytes, Thumb
 */

typedef union {
    struct {
        unsigned char a;
        unsigned char b;
    } unk_00;
    unsigned short raw;
} Pair;

typedef struct {
    unsigned char d, m, y;
} Date;

typedef struct {
    unsigned char pad_00[3];
    unsigned char b0;
    unsigned char b1;
    unsigned char b2;
} UnkStruct_0209dbe4;

extern int data_021dc744;
extern void func_0209df64(void *);
extern unsigned char data_020d1aec[];
extern unsigned char data_020d1af8[];
extern unsigned short data_020d1b5c[2][13];
extern void func_0209def4(void *);
extern unsigned char data_020d1b2c[];
extern unsigned char data_020d1b04[];

unsigned char func_0209de24(unsigned int a, unsigned int index);
int func_0209dcdc(const Date *p, const Date *q);

int func_0209ded0(void)
{
    return *(int *) ((char *) ((int) &data_021dc744) + (12));
}

int func_0209de88(int p1, int p2, int p3)
{
    char arr[4];
    int buf[2];
    int x;
    int ax;
    int rem;
    arr[2] = p1;
    arr[1] = p2;
    arr[0] = p3;
    func_0209df64(buf);
    x = func_0209dcdc((const Date *) arr, (const Date *) buf);
    ax = (x < 0) ? (-x) : (x);
    rem = ax % 7;
    if (x < 0) {
        rem = 7 - rem;
    }
    x = func_0209ded0();
    return (x + rem) % 7;
}

int func_0209de44(int a, int b, int c, int d)
{
    int res = -1;
    int ret1;
    int t;
    int val;
    int ret2;
    ret1 = func_0209de88(a, b, 1);
    if (c < ret1) {
        t = c - ret1 + 8;
    } else {
        t = c + 1 - ret1;
    }
    val = t + 7 * (d - 1);
    ret2 = (int) func_0209de24(a, b);
    if (val < ret2) {
        res = val;
    }
    return res;
}

unsigned char func_0209de24(unsigned int a, unsigned int index)
{
    if ((a & 3) == 0) {
        return data_020d1aec[index - 1];
    } else {
        return data_020d1af8[index - 1];
    }
}

void func_0209ddd4(Pair p1, Pair p2, Pair *out)
{
    Pair local;

    local.raw = p1.raw;
    local.unk_00.a += p2.unk_00.a;
    local.unk_00.b += p2.unk_00.b;
    while (local.unk_00.a >= 0x3c) {
        local.unk_00.b++;
        local.unk_00.a -= 0x3c;
    }
    while (local.unk_00.b >= 0x18) {
        local.unk_00.b -= 0x18;
    }
    out->raw = local.raw;
}

int func_0209dd9c(const unsigned char *a, const unsigned char *b)
{
    int result = 1;
    if (a[2] < b[2]) {
        result = 0;
    } else if (a[2] != b[2]) {
        // do nothing
    } else {
        if (a[1] < b[1]) {
            result = 0;
        } else if (a[1] != b[1]) {
            // do nothing
        } else {
            if (a[0] < b[0]) {
                result = 0;
            }
        }
    }
    return result;
}

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

    if (func_0209dd9c((const unsigned char *) p, (const unsigned char *) q)) {
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

int func_0209dcac(void)
{
    unsigned char buf[2];
    unsigned char b;
    int result;

    func_0209def4(buf);
    b = buf[1];
    if (b < 5) {
        result = 3;
    } else if (b < 12) {
        result = 0;
    } else if (b < 17) {
        result = 1;
    } else {
        result = 2;
    }
    return result;
}

int func_0209dc74(unsigned char *arr)
{
    unsigned char local[2];
    unsigned short value;
    unsigned short *p;
    int i;
    int result = 0;

    local[1] = arr[1];
    local[0] = arr[0];
    value = *(unsigned short *) local;
    for (p = (unsigned short *) data_020d1b2c, i = 0; i < 0x17; p++, i++) {
        if (value <= *p) {
            result = i;
            break;
        }
    }
    return result;
}

int func_0209dc48(unsigned char *arg0)
{
    unsigned char local_4[4];
    unsigned char *local_0;

    local_0 = local_4;
    local_4[0] = 1;
    local_4[1] = 1;
    local_4[2] = 0;
    local_4[3] = 0;
    local_4[2] = arg0[5];
    local_4[1] = arg0[4];
    local_4[0] = arg0[3];
    return func_0209dc74(local_4);
}

int func_0209dc10(unsigned char *arr)
{
    unsigned char local[2];
    unsigned short value;
    unsigned short *p;
    int i;
    int result = 0;

    local[1] = arr[1];
    local[0] = arr[0];
    value = *(unsigned short *) local;
    for (p = (unsigned short *) data_020d1b04, i = 0; i < 0x13; p++, i++) {
        if (value <= *p) {
            result = i;
            break;
        }
    }
    return result;
}

int func_0209dbe4(UnkStruct_0209dbe4 *p)
{
    unsigned char arr[4];
    arr[0] = 1;
    arr[1] = 1;
    arr[2] = 0;
    arr[3] = 0;
    arr[2] = p->b2;
    arr[1] = p->b1;
    arr[0] = p->b0;
    return func_0209dc10(arr);
}
