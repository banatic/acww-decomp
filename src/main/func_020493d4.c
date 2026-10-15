/* func_020493d4 @ 0x020493d4, 0x264 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

extern int func_0204f5e0(int, int, int, int, int, int);
extern int func_0204ba94(int);
extern void func_0204a198(int, int, int, int);
extern unsigned char data_020cacc0[];

typedef struct {
    volatile int vc;     // sp+0c
    int ok;              // sp+10
    int cnt;             // sp+14
    int hit;             // sp+18
    volatile int fm[4];  // 1c m1c, 20 m20, 24 m24, 28 m28
    volatile int fn[5];  // 2c n2c, 30 n30, 34 n34, 38 n38, 3c n3c
    volatile int t40;    // 40: read twice at the outer call
    int az[13];          // 44 z44, 48 z48, 4c..74 a4c..a74
    int b[9];            // 78..98
    volatile int unk_90; // 9c
    volatile int na0;    // a0
} WK;

void func_020493d4(int a, int p2, int *p)
{
    WK w;
    int mr3, mr2, mr1, m7;
    int nr2, nr1, n6;
    int j, jd, yy, xx, yd, xd, hit2, hitv, t4, dx;
    int lim;
    unsigned short t, t2;
    unsigned char *tbl;
    unsigned char bb;

    w.vc = 0;
    w.b[0] = 0;
    w.b[1] = 0;
    w.b[2] = 0;
    w.b[3] = 0;
    w.b[4] = 0;
    w.b[5] = 0;
    w.b[6] = 0;
    w.b[7] = 0;
    w.b[8] = 0;
    w.az[12] = 0;
    w.az[2] = 0;
    w.az[3] = 0;
    w.az[4] = 0;
    w.az[5] = 0;
    w.az[6] = 0;
    w.az[7] = 0;
    w.az[8] = 0;
    w.az[9] = 0;
    w.az[10] = 0;
    w.az[11] = 0;
    w.az[1] = 0;
    w.az[0] = 0;

    for (; lim = p[1], w.vc < lim; w.vc++) {
        j = w.az[0];
        if (p[0] <= 0) {
            continue;
        }
        w.t40 = w.vc >> 4;
        for (; j < p[0]; j++) {
            jd = j >> 4;
            t4 = w.t40 << 4;
            hitv = func_0204f5e0(p2, jd, w.t40, j - (jd << 4), w.vc - t4, w.az[1]);
            w.hit = hitv;
            if (hitv == 0) {
                continue;
            }
            mr3 = 1;
            mr2 = 1;
            mr1 = 1;
            m7 = 1;
            w.unk_90 = 1;
            w.fm[0] = 1;
            w.fm[1] = 1;
            w.fm[2] = 1;
            w.fm[3] = w.az[2];
            t = *(unsigned short *) *(volatile int *) &w.hit;
            if (t >= 0x26 && t <= 0x2a) {
                w.fm[3] = 1;
            }
            if (w.fm[3] == 0 && (t < 0x5d || t > 0x61)) {
                w.fm[2] = w.az[3];
            }
            if (w.fm[2] == 0 && (t < 0x2f || t > 0x56)) {
                w.fm[1] = w.az[4];
            }
            if (w.fm[1] == 0 && (t < 0x57 || t > 0x5b)) {
                w.fm[0] = w.az[5];
            }
            if (w.fm[0] == 0 && (t < 0x66 || t > 0x68)) {
                w.unk_90 = w.az[6];
            }
            if (w.unk_90 == 0 && t != 0x69) {
                m7 = w.az[7];
            }
            if (m7 == 0 && (t < 0x6a || t > 0x6c)) {
                mr1 = w.az[8];
            }
            if (mr1 == 0 && t != 0x6d) {
                mr2 = w.az[9];
            }
            if (mr2 == 0 && (t < 0xc8 || t > 0xcf)) {
                mr3 = w.az[10];
            }
            if (mr3 == 0) {
                continue;
            }
            if (func_0204ba94(w.hit) == 0) {
                continue;
            }
            w.ok = w.az[11];
            tbl = data_020cacc0;
            w.cnt = w.az[11];
            do {
                bb = *tbl;
                yy = j - ((bb >> 4) - 8);
                dx = (bb & 15) - 8;
                xx = w.vc - dx;
                if (yy < 0 || yy >= p[0]) {
                    continue;
                }
                if (xx < 0 || xx >= p[1]) {
                    continue;
                }
                yd = yy >> 4;
                xd = xx >> 4;
                if ((hit2 = func_0204f5e0(p2, yd, xd, yy - (yd << 4), xx - (xd << 4), w.az[12])) == 0) {
                    continue;
                }
                nr2 = 1;
                nr1 = 1;
                n6 = 1;
                w.na0 = 1;
                w.fn[0] = 1;
                w.fn[1] = 1;
                w.fn[2] = 1;
                w.fn[3] = 1;
                w.fn[4] = w.b[0];
                t2 = *(unsigned short *) hit2;
                if (t2 >= 0x26 && t2 <= 0x2a) {
                    w.fn[4] = 1;
                }
                if (w.fn[4] == 0 && (t2 < 0x5d || t2 > 0x61)) {
                    w.fn[3] = w.b[1];
                }
                if (w.fn[3] == 0 && (t2 < 0x2f || t2 > 0x56)) {
                    w.fn[2] = w.b[2];
                }
                if (w.fn[2] == 0 && (t2 < 0x57 || t2 > 0x5b)) {
                    w.fn[1] = w.b[3];
                }
                if (w.fn[1] == 0 && (t2 < 0x66 || t2 > 0x68)) {
                    w.fn[0] = w.b[4];
                }
                if (w.fn[0] == 0 && t2 != 0x69) {
                    w.na0 = w.b[5];
                }
                if (w.na0 == 0 && (t2 < 0x6a || t2 > 0x6c)) {
                    n6 = w.b[6];
                }
                if (n6 == 0 && t2 != 0x6d) {
                    nr1 = w.b[7];
                }
                if (nr1 == 0 && (t2 < 0xc8 || t2 > 0xcf)) {
                    nr2 = w.b[8];
                }
                if (nr2 == 0) {
                    continue;
                }
                w.ok = w.ok + 1;
            } while (tbl++, w.cnt++, w.cnt < 0x30);
            if (w.ok >= 8) {
                func_0204a198(p2, *(unsigned short *) w.hit, j, w.vc);
            }
        }
    }
}
