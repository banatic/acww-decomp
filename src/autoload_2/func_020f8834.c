/* func_020f8834 @ 0x020f8834, 0x350 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020eed18(void *h, int a);
extern void func_020eedb8(int seq, int a, void *h);
extern unsigned int func_020f1d3c(void *rng, unsigned int range);
extern void NNS_SndPlayerWriteVariable(void *h, int varNo, int val);
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
} UnkStruct_020f8834;

void func_020f8834(UnkStruct_020f8834 *p, int code, void *q)
{
    unsigned int v;

    if (p->unk_0C == 1) {
        p->unk_0C = 0;
        func_020eed18(&p->unk_04, 0);
        func_020eedb8(0x136, 1, &p->unk_04);
        p->unk_10 = 0;
    } else if (code == 0) {
        if (func_020f1d3c(data_021fd1bc, 100) < 0x46) {
            NNS_SndPlayerWriteVariable(&p->unk_04, 0, 1);
        }
        func_020eed18(&p->unk_08, 0);
        func_020eedb8(0x139, 1, &p->unk_08);
    } else if (code == 0x5a) {
        if (func_020f1d3c(data_021fd1bc, 100) < 0x3c) {
            NNS_SndPlayerWriteVariable(&p->unk_04, 1, 1);
            p->unk_0E = 1;
        }
        v = func_020f1d3c(data_021fd1bc, 100);
        func_020eed18(&p->unk_08, 0);
        if (v < 0x21) {
            func_020eedb8(0x13a, 1, &p->unk_08);
        } else if (v < 0x42) {
            func_020eedb8(0x13b, 1, &p->unk_08);
        } else {
            func_020eedb8(0x13c, 1, &p->unk_08);
        }
    } else if (code == 0x91) {
        v = func_020f1d3c(data_021fd1bc, 100);
        func_020eed18(&p->unk_08, 0);
        if (v < 0x21) {
            func_020eedb8(0x13a, 1, &p->unk_08);
        } else if (v < 0x42) {
            func_020eedb8(0x13b, 1, &p->unk_08);
        } else {
            func_020eedb8(0x13c, 1, &p->unk_08);
        }
    } else if (code == 0xb4) {
        if (func_020f1d3c(data_021fd1bc, 100) < 0x46 && p->unk_0E != 1) {
            NNS_SndPlayerWriteVariable(&p->unk_04, 1, 1);
            p->unk_0E = 2;
        }
        if (func_020f1d3c(data_021fd1bc, 100) < 0x3c && p->unk_0E != 1) {
            NNS_SndPlayerWriteVariable(&p->unk_04, 0, 1);
            p->unk_0E = 2;
        }
    } else if (code == 0xfa) {
        v = func_020f1d3c(data_021fd1bc, 100);
        if (p->unk_0E != 2) {
            if (v < 0x46) {
                NNS_SndPlayerWriteVariable(&p->unk_04, 2, 1);
                p->unk_0E = 3;
            } else {
                NNS_SndPlayerWriteVariable(&p->unk_04, 0, 1);
                p->unk_0E = 4;
            }
        }
        func_020eed18(&p->unk_08, 0);
        func_020eedb8(0x13d, 1, &p->unk_08);
    } else if (p->unk_10 == 0x67) {
        func_020eed18(&p->unk_04, 0);
        func_020eedb8(0x137, 1, &p->unk_04);
    } else if (p->unk_10 == 0x2bc) {
        func_020eed18(&p->unk_04, 0);
        func_020eedb8(0x138, 1, &p->unk_04);
    } else if (p->unk_10 == 0x384) {
        func_020eed18(&p->unk_04, 0);
        func_020eedb8(0x136, 1, &p->unk_04);
        p->unk_10 = 0;
    }
    p->unk_10 = (unsigned short) (p->unk_10 + 1);
    ciAddUNQUIETFilter(p, q);
}
