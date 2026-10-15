/* func_020f8494 @ 0x020f8494, 0x35c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern int func_020eed18(void *h, int a);
extern int func_020eedb8(int seq, int a, void *h);
extern unsigned int func_020f1d3c(void *rng, unsigned int range);
extern void func_0210b6d4(void *h, int a, int b);
extern void ciAddUNQUIETFilter(void *p, void *q);
extern char data_021fd1bc[];

typedef struct {
    int unk_00;
    void *unk_04;
    void *unk_08;
    unsigned char unk_0C;
    unsigned char unk_0D;
    unsigned short unk_0E;
    unsigned short unk_10;
    unsigned short unk_12;
    unsigned short unk_14;
} UnkStruct_020f8494;

void func_020f8494(UnkStruct_020f8494 *p, int code, void *q)
{
    unsigned int v;

    if (p->unk_0C == 1) {
        p->unk_0C = 0;
        func_020eed18(&p->unk_08, 0);
        func_020eedb8(0x12d, 1, &p->unk_08);
        func_020eed18(&p->unk_04, 0);
        func_020eedb8(0x132, 1, &p->unk_04);
        p->unk_14 = 0;
        p->unk_12 = 0;
        p->unk_0E = 0;
        p->unk_10 = 0;
    } else if (code == 0) {
        func_020eed18(&p->unk_08, 0);
        func_020eed18(&p->unk_04, 0);
        if (func_020f1d3c(data_021fd1bc, 100) < 0x28) {
            func_020eedb8(0x12e, 1, &p->unk_08);
            func_020eedb8(0x132, 1, &p->unk_04);
            p->unk_14 = 1;
        } else {
            func_020eedb8(0x130, 1, &p->unk_08);
            func_020eedb8(0x133, 1, &p->unk_04);
            p->unk_14 = 2;
        }
    } else if (code == 0x5a && p->unk_14 != 0) {
        v = func_020f1d3c(data_021fd1bc, 3);
        func_020eed18(&p->unk_08, 0);
        func_020eed18(&p->unk_04, 0);
        if (v == 0) {
            func_020eedb8(0x12f, 1, &p->unk_08);
            func_020eedb8(0x134, 1, &p->unk_04);
            p->unk_14 = 3;
        } else if (v == 1) {
            func_020eedb8(0x12f, 1, &p->unk_08);
            func_020eedb8(0x135, 1, &p->unk_04);
            p->unk_14 = 4;
        } else {
            func_020eedb8(0x131, 1, &p->unk_08);
            func_020eedb8(0x134, 1, &p->unk_04);
            p->unk_14 = 5;
        }
    } else if (code == 0x78 && p->unk_14 == 0) {
        v = func_020f1d3c(data_021fd1bc, 2);
        func_020eed18(&p->unk_08, 0);
        func_020eed18(&p->unk_04, 0);
        if (v == 0) {
            func_020eedb8(0x12f, 1, &p->unk_08);
            func_020eedb8(0x134, 1, &p->unk_04);
            p->unk_14 = 3;
        } else {
            func_020eedb8(0x12f, 1, &p->unk_08);
            func_020eedb8(0x135, 1, &p->unk_04);
            p->unk_14 = 4;
        }
    }

    if (p->unk_12 != p->unk_14) {
        if (p->unk_10 == 0) {
            p->unk_10 = (unsigned short) (p->unk_10 + 1);
        } else if (p->unk_10 == 1) {
            if (func_020f1d3c(data_021fd1bc, 2) == 0) {
                p->unk_10 = (unsigned short) (p->unk_10 + 1);
            } else {
                p->unk_10 = 0;
                p->unk_0E = (unsigned short) ((p->unk_0E + 1) % 2);
            }
        } else if (p->unk_10 >= 2) {
            p->unk_10 = 0;
            p->unk_0E = (unsigned short) ((p->unk_0E + 1) % 2);
        }
        if (p->unk_0E % 2 == 1) {
            func_0210b6d4(&p->unk_08, 0x3f, 1);
        }
        p->unk_12 = p->unk_14;
    }
    ciAddUNQUIETFilter(p, q);
}
