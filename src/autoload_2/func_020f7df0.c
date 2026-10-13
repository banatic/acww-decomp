/* func_020f7df0 @ 0x020f7df0, 0x654 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern void func_020eed18(void *h, int a);
extern void func_020eedb8(int seq, int a, void *h);
extern unsigned int func_020f1d3c(void *rng, unsigned int range);
extern void NNS_SndPlayerSetTrackVolume(void *h, int track, int vol);
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
} UnkStruct_020f7df0;

void func_020f7df0(UnkStruct_020f7df0 *p, int code, void *q)
{
    int thrA, thrB, thrC, thrD, thrE, thrF;
    int base;
    int v;

    p->unk_12 = (unsigned short) (p->unk_12 + 1);
    if (p->unk_0E == 0xf && p->unk_12 >= 0x8c) {
        p->unk_0D = 1;
        p->unk_12 = 0;
        thrA = 0x32;
        thrB = 0x4b;
        thrC = 0x19;
        thrD = 0x32;
        thrE = 0x4b;
        thrF = 0x58;
    } else if (p->unk_0E == 0x10 && p->unk_12 >= 0x64) {
        p->unk_0D = 1;
        p->unk_12 = 0;
        thrA = 0x32;
        thrB = 0x4b;
        thrC = 0x19;
        thrD = 0x32;
        thrE = 0x4b;
        thrF = 0x58;
    } else if (p->unk_0E % 5 <= 2 && p->unk_12 >= 0x78) {
        p->unk_0D = 1;
        p->unk_12 = 0;
        if (p->unk_0E / 5 == 0) {
            thrA = 0x32;
            thrB = 0x4b;
            thrC = 0x19;
            thrD = 0x32;
            thrE = 0x4b;
            thrF = 0x58;
        } else if (p->unk_0E / 5 == 1) {
            thrA = 0x28;
            thrB = 0x50;
            thrC = 0x19;
            thrD = 0x32;
            thrE = 0x4b;
            thrF = 0x58;
        } else {
            thrA = 0x28;
            thrB = 0x3c;
            thrC = 0x19;
            thrD = 0x32;
            thrE = 0x4b;
            thrF = 0x58;
        }
    } else if (p->unk_0E % 5 >= 3 && p->unk_12 >= 0x46) {
        p->unk_0D = 1;
        p->unk_12 = 0;
        if (p->unk_0E / 5 == 0) {
            thrA = 0x32;
            thrB = 0x4b;
            thrC = 0x23;
            thrD = 0x46;
            thrE = 0x64;
            thrF = 0x64;
        } else if (p->unk_0E / 5 == 1) {
            thrA = 0x28;
            thrB = 0x50;
            thrC = 0x23;
            thrD = 0x46;
            thrE = 0x64;
            thrF = 0x64;
        } else {
            thrA = 0x28;
            thrB = 0x3c;
            thrC = 0x23;
            thrD = 0x46;
            thrE = 0x64;
            thrF = 0x64;
        }
    }

    if (p->unk_0D == 1) {
        func_020eed18(&p->unk_08, 0);
        p->unk_10 = p->unk_0E;
        v = (short) func_020f1d3c(data_021fd1bc, 100);
        if (v <= thrA) {
            base = 0;
        } else if (v <= thrB) {
            base = 5;
        } else {
            base = 10;
        }
        v = (short) func_020f1d3c(data_021fd1bc, 100);
        if (v <= thrC) {
            p->unk_0E = (unsigned short) base;
            if (p->unk_10 % 5 != p->unk_0E % 5) {
                func_020eed18(&p->unk_04, 0);
                func_020eedb8(0x13e, 1, &p->unk_04);
            }
        } else if (v <= thrD) {
            p->unk_0E = (unsigned short) (base + 1);
            if (p->unk_10 % 5 != p->unk_0E % 5) {
                func_020eed18(&p->unk_04, 0);
                func_020eedb8(0x13f, 1, &p->unk_04);
            }
        } else if (v <= thrE) {
            p->unk_0E = (unsigned short) (base + 2);
            if (p->unk_10 % 5 != p->unk_0E % 5) {
                func_020eed18(&p->unk_04, 0);
                func_020eedb8(0x140, 1, &p->unk_04);
            }
        } else if (v <= thrF) {
            p->unk_0E = (unsigned short) (base + 3);
            if (p->unk_10 % 5 != p->unk_0E % 5) {
                func_020eed18(&p->unk_04, 0);
                func_020eedb8(0x141, 1, &p->unk_04);
            }
        } else {
            p->unk_0E = (unsigned short) (base + 4);
            if (p->unk_10 % 5 != p->unk_0E % 5) {
                func_020eed18(&p->unk_04, 0);
                func_020eedb8(0x142, 1, &p->unk_04);
            }
        }

        if (base / 5 == 0) {
            NNS_SndPlayerSetTrackVolume(&p->unk_04, 3, 100);
            if (func_020f1d3c(data_021fd1bc, 100) < 0x28 && code > 0x5a) {
                func_020eedb8(0x146, 1, &p->unk_08);
                NNS_SndPlayerSetTrackVolume(&p->unk_08, 3, 100);
            }
        } else if (base / 5 == 1) {
            NNS_SndPlayerSetTrackVolume(&p->unk_04, 3, 0x4b);
            func_020eedb8(0x145, 1, &p->unk_08);
        } else {
            NNS_SndPlayerSetTrackVolume(&p->unk_04, 3, 0x7f);
            if (func_020f1d3c(data_021fd1bc, 100) < 0x28 && code > 0x5a && p->unk_0E <= 0xd) {
                func_020eedb8(0x146, 1, &p->unk_08);
                NNS_SndPlayerSetTrackVolume(&p->unk_08, 3, 0x50);
            }
        }

        if (p->unk_10 == 0xb || p->unk_10 == 0xd) {
            v = (short) func_020f1d3c(data_021fd1bc, 100);
            if (v <= 0x14) {
                func_020eed18(&p->unk_04, 0);
                func_020eedb8(0x143, 1, &p->unk_04);
                p->unk_0E = 0xf;
            } else if (v <= 0x28) {
                func_020eed18(&p->unk_04, 0);
                func_020eedb8(0x144, 1, &p->unk_04);
                p->unk_0E = 0x10;
            }
        }
        p->unk_0D = 0;
    }
    ciAddUNQUIETFilter(p, q);
}
