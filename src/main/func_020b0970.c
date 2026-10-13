/* func_020b0970 @ 0x020b0970, 0xb0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020b0970 {
    unsigned short a0 : 7;
    unsigned short a1 : 4;
    unsigned short a2 : 5;
    unsigned short b0 : 7;
    unsigned short b1 : 7;
    unsigned short b2 : 2;
    unsigned char g;
    unsigned char h;
} UnkStruct_020b0970;

typedef struct DateTime {
    unsigned char sec;
    unsigned char min;
    unsigned char hour;
    unsigned char day;
    unsigned char mon;
    unsigned char year;
    unsigned short pad_06;
} DateTime;

typedef union DateTimeU {
    DateTime t;
    unsigned int w[2];
} DateTimeU;

extern void func_0209e474(DateTime *d);
extern void func_0209e140(DateTime *d, int n);

void func_020b0970(UnkStruct_020b0970 *p, unsigned short a, unsigned short b, int c)
{
    DateTimeU d;

    p->b0 = a >> 7;
    p->b1 = b >> 7;
    p->b2 = c;
    p->g = 0;
    d.w[0] = 0;
    d.w[1] = 0;
    func_0209e474(&d.t);
    if (d.t.hour < 6) {
        func_0209e140(&d.t, 1);
    }
    p->a0 = d.t.year;
    p->a1 = d.t.mon;
    p->a2 = d.t.day;
    p->h = 1;
}
