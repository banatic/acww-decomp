/* func_02096ad0 @ 0x02096ad0, 0x134 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char unk_00;
    unsigned char pad_01;
    short unk_02;
} UnkStruct_02096ad0;

extern void *data_020ccf94;

extern int func_02073dd4(void *g, int i);
extern int func_02073918(void *g, int i);
extern int func_020a7330(int i);
extern int *func_02096260(int w);
extern unsigned char *func_02096254(int w);
extern int *func_02096244(int w);
extern unsigned short *func_02096238(int w);
extern int func_02096518(int *a, int k, int w);
extern int func_02096614(UnkStruct_02096ad0 *s, int *b, int *c, int k, int w);
extern int func_0209658c(short *h, int k, int w);
extern void func_02095304(int *w, UnkStruct_02096ad0 *s, int *p, int *a, int *b, int *c);
extern void *func_020961a8(int n);
extern void func_020771cc(int a, void *b, int c, int d);

int func_02096ad0(void)
{
    void *g;
    void *g2;
    int i;
    int k;
    int *q;
    unsigned char v;
    void *e;
    int n;
    int *p8;
    unsigned char *p12;
    unsigned short *p10;
    UnkStruct_02096ad0 s;
    int w;
    int v1c;
    int v20;
    int v24;
    int t24;

    i = 3;
    g = data_020ccf94;
    k = ~0;
    for (; i >= 0; i--) {
        if (func_02073dd4(g, i) == 0) {
            continue;
        }
        if (func_02073918(g, i) != 0) {
            continue;
        }
        w = i;
        s.unk_00 = (unsigned char) func_020a7330(i);
        p8 = func_02096260(w);
        p12 = func_02096254(w);
        q = func_02096244(w);
        p10 = func_02096238(w);
        v = s.unk_00;
        if (v == 0xc || v == 0xd || v == 0xe || v == 0x2f || v == 0x2e) {
            continue;
        }
        if (func_02096518(&v1c, k, w) == 0) {
            continue;
        }
        if (func_02096614(&s, &v20, &v24, k, w) == 0) {
            continue;
        }
        if (func_0209658c(&s.unk_02, k, w) == 0) {
            continue;
        }
        func_02095304(&w, &s, p8, &v1c, &v20, &v24);
        *p8 = v1c;
        *p12 = s.unk_00;
        t24 = v24;
        q[0] = v20;
        q[1] = 0;
        q[2] = t24;
        *p10 = s.unk_02;
    }
    g2 = data_020ccf94;
    if (func_02073dd4(g2, *(int *) ((char *) g2 + 0x64)) != 0) {
        e = func_020961a8(4);
        if (e != 0) {
            n = *(int *) ((char *) g + 0x68);
            if (n < 4) {
                func_020771cc(n + 4, (char *) e + 0x8e, 0, 0);
                func_020771cc(n, (char *) e + 0x5c, 0, 0);
                n = n + 8;
                func_020771cc(n, 0, 0, 0);
            }
        }
    }
    return 1;
}
