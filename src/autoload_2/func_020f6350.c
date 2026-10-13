/* func_020f6350 @ 0x020f6350, 0x178 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

typedef struct {
    unsigned char pad_00[0x3c];
    unsigned char unk_3C;
} State;

typedef struct {
    unsigned char pad_00[6];
    unsigned char unk_06;
    unsigned char pad_07[0x1d - 0x7];
    unsigned char unk_1D;
} UnkStruct_020f6350;

typedef struct {
    unsigned char pad_00[4];
    unsigned short unk_04;
    signed char unk_06;
    unsigned char pad_07[3];
    unsigned char unk_0A;
} Player;

typedef struct {
    unsigned char pad_00[0x28];
    void *unk_28;
    UnkStruct_020f6350 *unk_2C;
    State *unk_30;
} Glob;

extern Glob data_021fd1bc;
extern unsigned char data_0213f0a4;
extern unsigned short data_021fd264;
extern void func_020eed18(Player *p, int n);
extern int NNS_SndArcPlayerStartSeqArc(Player *p, unsigned short seq, int flags);
extern void *func_020eef70(void);
extern void NNS_SndHeapLoadState(void *heap, int state);
extern void func_0210e1d0(unsigned short n, void *heap);
extern void func_0210e198(int n, void *heap);

void func_020f6350(Player *p, unsigned short value)
{
    State *st = data_021fd1bc.unk_30;
    UnkStruct_020f6350 *x;
    void *heap;
    unsigned short n;
    int flag;

    if (st->unk_3C == 1) {
        return;
    }

    func_020eed18(p, 0);
    st->unk_3C = 2;

    data_021fd264 = p->unk_04;
    p->unk_04 = value;
    flag = 0;
    p->unk_0A = 1;
    p->unk_06 = -1;

    if (NNS_SndArcPlayerStartSeqArc(p, p->unk_04, flag) != 0) {
        if (data_021fd264 == p->unk_04) {
            flag = 1;
        }
        func_020eed18(p, 0);
    }

    if (flag) {
        return;
    }

    x = data_021fd1bc.unk_2C;
    if (x == 0) {
        return;
    }

    if (x->unk_06 != 0) {
        data_0213f0a4 = 2;
    } else {
        data_0213f0a4 = (data_0213f0a4 == 1) ? 2 : 1;
    }

    if (data_0213f0a4 == 1) {
        heap = func_020eef70();
        NNS_SndHeapLoadState(heap, x->unk_1D + 1);
    } else if (data_0213f0a4 == 2) {
        heap = data_021fd1bc.unk_28;
        func_020eef70();
        NNS_SndHeapLoadState(heap, 0);
    }

    n = p->unk_04;
    func_0210e1d0(n, heap);
    func_0210e198(n + 0x25f, heap);
}