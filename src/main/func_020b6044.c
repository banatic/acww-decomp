/* func_020b6044 @ 0x020b6044, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Rec {
    char pad_00[0x16];
    short unk_16;
    unsigned char unk_18;
    char pad_19[3];
} Rec;
typedef struct Tbl {
    Rec *recs;
    unsigned char count;
} Tbl;
typedef struct Root {
    char pad_00[0xc];
    Tbl *t;
} Root;

extern Root *data_021f6948;

int func_020b6044(void *unused, int idx, int *outA, short *outB)
{
    Tbl *t;
    Rec *r;
    int n;

    *outA = 0;
    *outB = 0;
    if (idx == -1) {
        goto ret0;
    }
    if (data_021f6948 == 0) {
        goto ret0;
    }
    t = data_021f6948->t;
    if (t == 0) {
        goto ret0;
    }
    r = t->recs;
    if (r == 0) {
        goto ret0;
    }
    n = t->count;
    if (idx < 0) {
        goto ret0;
    }
    if (idx >= n) {
        goto ret0;
    }
    r = (Rec *) ((char *) r + idx * 0x1c);
    if (outA != 0) {
        *outA = r->unk_18;
    }
    if (outB != 0) {
        *outB = r->unk_16;
    }
    return 1;
ret0:
    return 0;
}
