/* func_02061b1c @ 0x02061b1c, 0x310 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

extern unsigned char data_020e54a8;

#define IDX(v, lo, hi) (((v) >= (lo) && (v) <= (hi)) ? (int) ((v) - (lo)) : -1)

void func_02061b1c(unsigned short *out, unsigned short *in, int flag)
{
    unsigned int v;
    int i;
    int ok;

    ok = (data_020e54a8 == 1) ? 1 : 0;
    if (ok || flag) {
        ok = 0;
        v = *in;
        if (v >= 0x11a8 && v <= 0x12a7) {
            ok = 1;
        }
        if (ok) {
            i = IDX(v, 0x11a8, 0x12a7);
            *out = (unsigned short) ((unsigned) i < 0x100 ? 0x3984 + i * 4 : 0x3984);
            return;
        }
        if (v >= 0x12b0 && v <= 0x12e7) {
            i = IDX(v, 0x12b0, 0x12e7);
            *out = (unsigned short) ((unsigned) i < 0x38 ? 0x42a4 + i * 4 : 0x42a4);
            return;
        }
        if (v >= 0x12e8 && v <= 0x131f) {
            i = IDX(v, 0x12e8, 0x131f);
            *out = (unsigned short) ((unsigned) i < 0x38 ? 0x4384 + i * 4 : 0x4384);
            return;
        }
        if (v >= 0x1380 && v <= 0x139f) {
            i = IDX(v, 0x1380, 0x139f);
            *out = (unsigned short) ((unsigned) i < 0x20 ? 0x3e24 + i * 4 : 0x3e24);
            return;
        }
        if (v >= 0x13c8 && v <= 0x1407) {
            i = IDX(v, 0x13c8, 0x1407);
            *out = (unsigned short) ((unsigned) i < 0x40 ? 0x3fa4 + i * 4 : 0x3fa4);
            return;
        }
        if (v >= 0x13a8 && v <= 0x13c7) {
            i = IDX(v, 0x13a8, 0x13c7);
            *out = (unsigned short) ((unsigned) i < 0x20 ? 0x40a4 + i * 4 : 0x40a4);
            return;
        }
        if (v >= 0x1431 && v <= 0x1470) {
            i = IDX(v, 0x1431, 0x1470);
            *out = (unsigned short) ((unsigned) i < 0x40 ? 0x4124 + i * 4 : 0x4124);
            return;
        }
        if (v >= 0x137c && v <= 0x137c) {
            *out = (unsigned short) 0x44dc;
            return;
        }
        if (v >= 0x1408 && v <= 0x1428) {
            i = IDX(v, 0x1408, 0x1428);
            *out = (unsigned short) ((unsigned) i < 0x21 ? 0x4464 + i * 4 : 0x4464);
            return;
        }
        if (v >= 0x1471 && v <= 0x1491) {
            i = IDX(v, 0x1471, 0x1491);
            *out = (unsigned short) ((unsigned) i < 0x21 ? 0x4464 + i * 4 : 0x4464);
            return;
        }
        if (v >= 0x1554 && v <= 0x155c) {
            i = IDX(v, 0x1554, 0x155c);
            *out = (unsigned short) ((unsigned) i < 9 ? 0x44e8 + i * 4 : 0x44e8);
            return;
        }
    } else {
        ok = 0;
        v = *in;
        if (v >= 0x137c && v <= 0x137c) {
            ok = 1;
        }
        if (ok) {
            *out = 0x1e;
            return;
        }
        if (v >= 0x1408 && v <= 0x1428) {
            *out = (unsigned short) IDX(v, 0x1408, 0x1428);
            return;
        }
        if (v >= 0x1471 && v <= 0x1491) {
            *out = (unsigned short) IDX(v, 0x1471, 0x1491);
            return;
        }
        if (v >= 0x153b && v <= 0x1541) {
            *out = (unsigned short) (IDX(v, 0x153b, 0x1541) + 0xd4);
            return;
        }
    }
    *out = (unsigned short) v;
}
