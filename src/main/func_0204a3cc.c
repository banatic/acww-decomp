/* func_0204a3cc @ 0x0204a3cc, 0x208 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Pair {
    int a;
    int b;
} Pair;

typedef struct Cell {
    int unk_00;
    unsigned char unk_04;
    unsigned char unk_05;
    unsigned char unk_06;
    unsigned char unk_07;
    unsigned short unk_08;
    unsigned short unk_0A;
    unsigned short unk_0C;
    unsigned short unk_0E;
    int unk_10;
    int unk_14;
    unsigned short unk_18;
    unsigned short unk_1A;
    unsigned char unk_1C;
    unsigned char unk_1D;
    unsigned char unk_1E;
    unsigned char unk_1F;
    int c0 : 1;
    int c1 : 1;
    int c2 : 1;
    int c3 : 1;
    int c4 : 1;
    int c5 : 8;
    int c13 : 1;
    int c14 : 1;
    int c15 : 17;
} Cell;

typedef union UnkStruct_0204a3cc_2 {
    unsigned char v;
    struct {
        int b0 : 5;
        int b5 : 1;
        int b6 : 1;
        int b7 : 1;
        int b8 : 24;
    } b;
} UnkStruct_0204a3cc_2;

typedef struct UnkStruct_0204a3cc {
    int unk_00;
    char pad_04[0x18 - 4];
    char unk_18;
    char pad_19[0x24 - 0x19];
    unsigned char unk_24;
    unsigned char unk_25;
    unsigned short unk_26;
    unsigned short unk_28;
    unsigned short unk_2A;
    unsigned char unk_2C;
    unsigned char unk_2D;
    unsigned char unk_2E;
    char pad_2F[1];
    UnkStruct_0204a3cc_2 unk_30;
    int unk_34;
    int unk_38;
    int unk_3C;
    int unk_40;
    Cell grid[1][4];
} UnkStruct_0204a3cc;

typedef struct UnkStruct_0204a3cc_3 {
    int unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_0204a3cc_3;

typedef struct GS {
    int hdr;
    int counts[5];
} GS;

extern GS data_021c79c4;
extern void func_0204a848(Cell *, UnkStruct_0204a3cc_3 *, int, int);
extern int func_0204a824(UnkStruct_0204a3cc *, int);
extern void func_0204b0c0(void *, Pair *, Cell *);
extern int func_0204a398(UnkStruct_0204a3cc *, int *, int, int);

int func_0204a3cc(UnkStruct_0204a3cc *p, UnkStruct_0204a3cc_3 *q)
{
    int result;

    int i;
    int j;
    int nx;
    int ny;
    int C;
    int t;
    int A;
    int B;
    Cell *c;
    int u;
    Pair loc;

    A = -1;
    B = -1;
    C = 0x2710;
    p->unk_24 = 0;
    p->unk_26 = 0;
    p->unk_25 = 0;
    p->unk_28 = 0;
    p->unk_2A = 0;
    p->unk_2C = 0;
    p->unk_2D = 0;
    p->unk_34 = A;
    p->unk_38 = A;
    p->unk_3C = A;
    p->unk_40 = A;
    p->unk_2E = 0;
    p->unk_30.v = 0;
    i = 0;
    for (j = 0; j < 5; j++) {
        data_021c79c4.counts[j] = 0;
    }
    nx = q->unk_04 - 2;
    ny = q->unk_08 - 2;
    for (i = 0; i < nx; i++) {
        for (j = 0; j < ny; j++) {
            c = &p->grid[i][j];
            func_0204a848(c, q, i + 1, j + 1);
            if (c->c1) {
                p->unk_24 = p->unk_24 + 1;
            }
            if (c->c2) {
                p->unk_25 = p->unk_25 + 1;
            }
            if (c->c4) {
                p->unk_2C = p->unk_2C + 1;
            }
            if (c->unk_1D) {
                p->unk_2D = p->unk_2D + c->unk_1D;
            }
            p->unk_30.b.b5 = p->unk_30.b.b5 | c->c13;
            p->unk_2A = p->unk_2A + (c->unk_07 + (c->unk_05 + (c->unk_04 + c->unk_06)));
            p->unk_26 = p->unk_26 + c->unk_0E;
            p->unk_28 = p->unk_28 + c->unk_08;
            if ((int) c->unk_0C > 0) {
                p->unk_30.b.b7 = 1;
            }
            p->unk_30.b.b6 = p->unk_30.b.b6 | c->c14;
            t = c->unk_00;
            data_021c79c4.counts[func_0204a824(p, t)]++;
            if (t < C) {
                A = i;
                B = j;
                C = t;
            }
            if (c->c0) {
                p->unk_34 = i;
                p->unk_38 = j;
                u = c->unk_14;
                p->unk_3C = c->unk_10;
                p->unk_40 = u;
            }
        }
    }
    loc.a = A;
    loc.b = B;
    func_0204b0c0(&p->unk_18, &loc, &p->grid[A][B]);
    result = func_0204a398(p, data_021c79c4.counts, nx, ny);
    p->unk_00 = result;
    return result;
}
