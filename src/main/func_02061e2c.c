/* func_02061e2c @ 0x02061e2c, 0x2ec bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204be38(unsigned short *);
extern int func_0204bd84(unsigned short *);

void func_02061e2c(unsigned short *out, unsigned short *pin)
{
    unsigned int ok;
    unsigned short v;
    unsigned short w0, w1;
    int idx;

    ok = 0;
    v = *pin;

    if (v >= 0x3984 && v <= 0x3d83) {
        ok = 1;
    }
    if (ok != 0) {
        idx = (v >= 0x3984 && v <= 0x3d83) ? ((v - 0x3984) >> 2) : -1;
        *out = ((unsigned int) idx < 0x100) ? (unsigned short) (idx + 0x11a8) : 0x11a8;
        goto end;
    }
    if (v >= 0x42a4 && v <= 0x4383) {
        idx = (v >= 0x42a4 && v <= 0x4383) ? ((v - 0x42a4) >> 2) : -1;
        *out = ((unsigned int) idx < 0x38) ? (unsigned short) (idx + 0x12b0) : 0x12b0;
        goto end;
    }
    if (v >= 0x4384 && v <= 0x4463) {
        idx = (v >= 0x4384 && v <= 0x4463) ? ((v - 0x4384) >> 2) : -1;
        *out = ((unsigned int) idx < 0x38) ? (unsigned short) (idx + 0x12e8) : 0x12e8;
        goto end;
    }
    if (v >= 0x3e24 && v <= 0x3ea3) {
        idx = (v >= 0x3e24 && v <= 0x3ea3) ? ((v - 0x3e24) >> 2) : -1;
        *out = ((unsigned int) idx < 0x20) ? (unsigned short) (idx + 0x1380) : 0x1380;
        goto end;
    }
    if (v >= 0x3fa4 && v <= 0x40a3) {
        idx = (v >= 0x3fa4 && v <= 0x40a3) ? ((v - 0x3fa4) >> 2) : -1;
        *out = ((unsigned int) idx < 0x40) ? (unsigned short) (idx + 0x13c8) : 0x13c8;
        goto end;
    }
    if (v >= 0x40a4 && v <= 0x4123) {
        idx = (v >= 0x40a4 && v <= 0x4123) ? ((v - 0x40a4) >> 2) : -1;
        *out = ((unsigned int) idx < 0x20) ? (unsigned short) (idx + 0x13a8) : 0x13a8;
        goto end;
    }
    if (v >= 0x4124 && v <= 0x4223) {
        idx = (v >= 0x4124 && v <= 0x4223) ? ((v - 0x4124) >> 2) : -1;
        *out = ((unsigned int) idx < 0x40) ? (unsigned short) (idx + 0x1431) : 0x1431;
        goto end;
    }
    if (v >= 0x44e8 && v <= 0x450b) {
        idx = (v >= 0x44e8 && v <= 0x450b) ? ((v - 0x44e8) >> 2) : -1;
        *out = ((unsigned int) idx < 0x9) ? (unsigned short) (idx + 0x1554) : 0x1554;
        goto end;
    }
    idx = -1;
    if (v >= 0x4464 && v <= 0x44e7) {
        idx = (v >= 0x4464 && v <= 0x44e7) ? ((v - 0x4464) >> 2) : -1;
    }
    ok = 0;
    if (v <= 0x20) {
        ok = 1;
    }
    if (ok != 0) {
        idx = v;
    }
    if (idx != -1) {
        w0 = ((unsigned int) idx < 0x21) ? (unsigned short) (idx + 0x1408) : 0x1408;
        if (func_0204be38(&w0) != 0) {
            *out = w0;
            goto end;
        }
        w1 = ((unsigned int) idx < 0x21) ? (unsigned short) (idx + 0x1471) : 0x1471;
        if (func_0204bd84(&w1) != 0) {
            *out = w1;
            goto end;
        }
        *out = 0x137c;
        goto end;
    }
    if ((v >= 0xd4 && v <= 0xda) || (v >= 0xdb && v <= 0xe1)) {
        idx = (v >= 0xd4 && v <= 0xda) ? (v - 0xd4) : (v - 0xdb);
        *out = ((unsigned int) idx < 7) ? (unsigned short) (idx + 0x153b) : 0x153b;
        goto end;
    }
    *out = v;
end:;
}
