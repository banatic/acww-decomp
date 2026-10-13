/* func_020445c0 @ 0x020445c0, 0x190 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204ba94(volatile unsigned short *);
extern unsigned short data_020ca64c[];

int func_020445c0(unsigned short *out, unsigned short *out2, unsigned short id)
{
    volatile unsigned short v;
    unsigned int ok;
    unsigned short a, b;
    unsigned short c, d;
    unsigned int ok3;
    unsigned short e, f;
    int idx;
    int ret;

    v = 0xfff1;
    ret = 1;
    v = id;

    ok = 0;
    a = v;
    b = v;
    if (b >= 0x1408 && a <= 0x1428) {
        ok = 1;
    }
    if (ok != 0) {
        *out = (a >= 0x1408 && a <= 0x1428) ? (a - 0x1408) : -1;
        goto end;
    }
    if (a >= 0x1471 && a <= 0x1491) {
        *out = (a >= 0x1471 && a <= 0x1491) ? (a - 0x1471) : -1;
        goto end;
    }
    if (a >= 0x137c && a <= 0x137c) {
        *out = 0x1e;
        goto end;
    }
    if (a >= 0x14fe && a <= 0x1517) {
        idx = (a >= 0x14fe && a <= 0x1517) ? (a - 0x14fe) : -1;
        *out = idx;
        *out2 = ((unsigned int) idx < 0x21) ? (unsigned short) (idx + 0x1408) : 0x1408;
        goto end;
    }
    if (a >= 0x151d && a <= 0x151e) {
        if (a == 0x151d) {
            *out = 0x26;
            *out2 = 0x26;
        } else {
            *out = 0x5d;
            *out2 = 0x5d;
        }
        goto end;
    }
    if (func_0204ba94(&v) != 0) {
        ok = 0;
        c = v;
        d = v;
        if (d >= 0xc8 && c <= 0xcf) {
            ok = 1;
        }
        if (ok != 0) {
            *out = 0xc8;
        } else {
            *out = 0x26;
        }
        goto end;
    }
    ok3 = 0;
    e = v;
    f = v;
    if (f >= 0x1518 && e <= 0x151c) {
        ok3 = 1;
    }
    if (ok3 != 0) {
        idx = (e >= 0x1518 && e <= 0x151c) ? (e - 0x1518) : -1;
        *out = data_020ca64c[idx];
        goto end;
    }
    if (id == 0x1548) {
        *out = 0xc8;
        goto end;
    }
    if (id == 0x1567) {
        *out = 0xd4;
        *out2 = 0x1408;
        goto end;
    }
    ret = 0;
end:
    return ret;
}
