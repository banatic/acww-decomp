/* func_0201b458 @ 0x0201b458, 0x284 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x5c];
    int pos[3];
    unsigned char pad_68[0x26];
    unsigned short type;
} OBJA;

typedef struct {
    int pos[3];
} OBJB;

extern int func_0204ed30(void *, void *);
extern void func_0204f7e0(int *, void *);
extern void func_01ffd070(int *, int *, int *);
extern int func_020ea990(void *, int *);
extern int func_02078e98(int *, int);
extern char *func_02137550(void *, int);
extern void *func_02095794(int);
extern int func_02073d90(void *);
extern int func_020eaa6c(int *, int *);
extern void *data_021c80bc;
extern void *data_020ccf94;
extern int data_020c81fc[][3];
extern unsigned int data_020c81b4[];

void func_0201b458(int *out, OBJA *a, OBJB *b)
{
    int res0, resb, bestidx, resh, i10, v14, v18, best1c, v20, res24, j28;
    int i30, i34, i38, i3c, best, cnt;
    unsigned int ub;
    int v40[3], v4c[3], v58[3], v64[3], arr70[4][3];
    int va0[3], vac[3], vb8[3], vc4[3], vd0[3];
    void *G;
    unsigned short tt;

    out[0] = b->pos[0];
    out[1] = b->pos[1];
    out[2] = b->pos[2];
    G = data_021c80bc;
    res0 = func_0204ed30(G, a->pos);
    resb = func_0204ed30(G, b);
    func_0204f7e0(v40, a->pos);
    func_0204f7e0(v4c, b);
    bestidx = 0;
    v40[1] = 0;
    v4c[1] = 0;

    if (res0 == 0) {
        best = 0;
        i10 = bestidx;
        i30 = bestidx;
        for (; i10 < 4; i10++) {
            func_01ffd070(vac, v40, data_020c81fc[i10]);
            v58[0] = vac[0];
            v58[1] = vac[1];
            v58[2] = vac[2];
            resh = func_020ea990(a->pos, v58);
            if (func_0204ed30(G, v58) == 0) {
                continue;
            }
            if (func_02078e98(v58, i30) == 0) {
                continue;
            }
            if (best != 0 && best <= resh) {
                continue;
            }
            best = resh;
            bestidx = i10;
        }
        if (best != 0) {
            func_01ffd070(vb8, v40, data_020c81fc[bestidx]);
            out[0] = vb8[0];
            out[1] = vb8[1];
            out[2] = vb8[2];
        } else {
            out[0] = b->pos[0];
            out[1] = b->pos[1];
            out[2] = b->pos[2];
        }
        return;
    }

    best1c = bestidx;
    res24 = func_020ea990(b, v40);
    func_02137550(arr70, 0x30);
    tt = a->type;
    if (tt >= 0xe000 || tt < 0x2000) {
        v14 = 2;
        v18 = 0;
    } else if (tt < 0x6000) {
        v14 = 3;
        v18 = 1;
    } else if (tt < 0xa000) {
        v14 = 0;
        v18 = 2;
    } else {
        v14 = 1;
        v18 = 3;
    }
    if (func_02073d90(data_020ccf94) != 0) {
        i34 = 0;
        for (ub = 0; ub < 4; ub++) {
            void *q;
            q = func_02095794(ub);
            if (q == 0) {
                continue;
            }
            func_0204f7e0(va0, q);
            va0[1] = i34;
            arr70[ub][0] = va0[0];
            arr70[ub][1] = va0[1];
            arr70[ub][2] = va0[2];
        }
    }
    best = 0;
    i38 = 0;
    i3c = 0;
    for (cnt = 0; cnt < 4; cnt++) {
        func_01ffd070(vc4, v40, data_020c81fc[cnt]);
        v64[0] = vc4[0];
        v64[1] = vc4[1];
        v64[2] = vc4[2];
        v20 = func_020ea990(b, v64);
        if (cnt == v14) {
            v20 -= 0x2000;
        } else if (cnt == v18) {
            v20 += 0x2000;
        }
        for (j28 = i38; j28 < 4; j28++) {
            func_020eaa6c(v64, arr70[j28]);
        }
        if (func_02078e98(v64, i3c) == 0) {
            continue;
        }
        if ((data_020c81b4[cnt] & res0) == 0) {
            continue;
        }
        if (best1c != 0 && best1c <= v20) {
            continue;
        }
        best1c = v20;
        bestidx = cnt;
    }
    if (resb == 0 && best1c > res24) {
        out[0] = a->pos[0];
        out[1] = a->pos[1];
        out[2] = a->pos[2];
    } else {
        func_01ffd070(vd0, v40, data_020c81fc[bestidx]);
        out[0] = vd0[0];
        out[1] = vd0[1];
        out[2] = vd0[2];
    }
}
