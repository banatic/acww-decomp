/* func_020f4690 @ 0x020f4690, 0x48c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern void func_020eed18(void *h, int a);
extern void func_020eedb8(int seq, int a, void *h);
extern void func_020eed68(void *h, int a, int b, int c, int d, int e);
extern int func_020f5e50(void *obj, int n);
extern int func_020f5c64(void *obj, int n);
extern int *func_020f5a4c(void);
extern int func_020f5e24(int v);
extern int func_020f4b1c(int val, int base);
extern void func_020f5cf8(int x, int *out1, int *out2);
extern void func_0210b634(void *h, unsigned short a, int b);
extern void NNS_SndPlayerSetTrackVolume(void *h, int track, int vol);
extern void func_0210b734(void *h, int a);
extern void NNS_SndPlayerSetVolume(void *h, int a);
extern unsigned short data_0213e858;
extern unsigned char data_021fd1bc[];

typedef struct {
    int unk_00;
    void *unk_04;
    unsigned short unk_08;
    unsigned char unk_0A;
} UnkStruct_020f4690;

#define LIVE(p) (((unsigned int) ((p)->unk_04 != 0)) > 0)

void func_020f4690(UnkStruct_020f4690 *p, void *obj)
{
    int v, w;
    int a, b;

    if (data_021fd1bc[0x4d] == 1) {
        return;
    }

    if (p->unk_0A & 4) {
        if (LIVE(p)) {
            func_020eed18(&p->unk_04, 0);
        }
        p->unk_0A = (unsigned char) (p->unk_0A & ~4);
    }

    if (p->unk_0A & 1) {
        switch (p->unk_08) {
            case 0x80d:
                v = func_020f5e50(obj, 1);
                break;
            case 0x7f7:
            case 0x7f8:
            case 0x7fb:
            case 0x7fc:
            case 0x7fe:
            case 0x7ff:
                v = func_020f5e50(obj, 2);
                break;
            case 0x4ce:
            case 0x7f9:
            case 0x7fa:
            case 0x7fd:
            case 0x800:
            case 0x801:
            case 0x802:
            case 0x803:
            case 0x804:
            case 0x805:
            case 0x80a:
                v = 0;
                break;
            default:
                v = func_020f5e50(obj, 0);
                break;
        }

        if (v > (func_020f5a4c()[4] >> 12)) {
            if (LIVE(p)) {
                func_020eed18(&p->unk_04, 0);
            }
            p->unk_0A = (unsigned char) (p->unk_0A & ~1);
            return;
        }
        v = func_020f5e24(v);
        if (v == 0) {
            if (LIVE(p)) {
                func_020eed18(&p->unk_04, 0);
            }
            p->unk_0A = (unsigned char) (p->unk_0A & ~1);
            return;
        }

        if (!LIVE(p) || (unsigned short) (p->unk_08 + 0xf7fd) <= 1) {
            if (p->unk_08 == 0x837) {
                func_020eedb8((unsigned short) (p->unk_08 % 1000), (unsigned short) (p->unk_08 / 1000), &p->unk_04);
            } else {
                int t = func_020f4b1c(p->unk_08, v);
                func_020eed68(&p->unk_04, -1, -1, t, p->unk_08 / 1000, p->unk_08 % 1000);
            }
        }

        if (LIVE(p)) {
            if (p->unk_08 != 0x837) {
                func_0210b734(&p->unk_04, func_020f4b1c(p->unk_08, v));
            }
            switch (p->unk_08) {
                case 0x80b:
                    w = func_020f5c64(obj, 1);
                    break;
                case 0x805:
                case 0x80d:
                    w = 0;
                    break;
                case 0x7f7:
                case 0x7f8:
                case 0x7f9:
                case 0x7fa:
                case 0x7fb:
                case 0x7fc:
                case 0x7fd:
                case 0x7fe:
                case 0x7ff:
                case 0x800:
                case 0x801:
                case 0x802:
                case 0x803:
                case 0x804:
                    w = func_020f5c64(obj, 2);
                    break;
                default:
                    w = func_020f5c64(obj, 0);
                    break;
            }
            if (p->unk_08 == 0x4ce || p->unk_08 == 0x80a) {
                func_020f5cf8(((int *) obj)[2], &a, &b);
                NNS_SndPlayerSetTrackVolume(&p->unk_04, 3, a);
                NNS_SndPlayerSetTrackVolume(&p->unk_04, 0xc, b);
            } else {
                NNS_SndPlayerSetVolume(&p->unk_04, v);
                func_0210b634(&p->unk_04, data_0213e858, w);
            }
        }
        p->unk_0A = (unsigned char) (p->unk_0A & ~1);
    } else if (!(p->unk_0A & 2)) {
        if (LIVE(p)) {
            func_020eed18(&p->unk_04, 0);
        }
    }
    p->unk_0A = (unsigned char) (p->unk_0A & ~1);
}
