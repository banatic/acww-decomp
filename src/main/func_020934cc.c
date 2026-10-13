/* func_020934cc @ 0x020934cc, 0xf8 bytes, Thumb, module main
 * mwccarm 1.2/base -O2,s
 */

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    short unk_0C;
    short unk_0E;
    char pad1[0x14 - 0x10];
    int unk_14;
    char pad2[0x1c - 0x18];
} Entry;

typedef struct {
    char pad_00[0xc];
    int count;
    char pad1[0x18 - 0x10];
    int **unk_18;
    int flags1c;
    int unk_20;
    int unk_24;
    int unk_28;
    char pad2[0x3c - 0x2c];
    short unk_3C;
    short unk_3E;
    short unk_40;
} HObj;

typedef struct {
    char pad_00[4];
    unsigned char id[4];
    char pad1[0xc - 8];
    HObj *h;
} UnkStruct_020934cc;

extern Entry data_021d52d8[];
extern int data_020e29dc;
extern void func_020ea6e0(int *v, int angle);
extern int func_0209493c(HObj *h, int p1, void *p2, int p3, int p4, int p5, void *p6, int p7, void *p8);
extern void func_020914dc(Entry *e);

int func_020934cc(UnkStruct_020934cc *self)
{
    unsigned char id[4];
    int done;
    Entry *e;
    int t1, t2;
    int v[3];

    {
        unsigned char *src = (unsigned char *) self + 4;
        unsigned char *dst = id;
        int n = 4;
        do {
            *dst++ = *src++;
            n--;
        } while (n != 0);
    }

    e = &data_021d52d8[id[0]];
    done = 0;

    if (e->unk_14 != -1 && e->unk_0E != 0) {
        HObj *h;
        v[0] = 0;
        v[1] = 0;
        v[2] = 0x1000;
        h = self->h;
        h->unk_20 = e->unk_00 + (*h->unk_18)[1];
        h->unk_24 = e->unk_04 + (*h->unk_18)[2];
        h->unk_28 = e->unk_08 + (*h->unk_18)[3];
        func_020ea6e0(v, e->unk_0C);
        t1 = v[1];
        t2 = v[2];
        h = self->h;
        h->unk_3C = (short) v[0];
        h->unk_3E = (short) t1;
        h->unk_40 = (short) t2;
        func_0209493c(self->h, 0x71, &data_020e29dc, -1, 0, 0x71, &data_020e29dc, 0x72, &data_020e29dc);
        if (e->unk_0E > 0) {
            e->unk_0E = (short) (e->unk_0E - 1);
        }
        done = 1;
    }

    if (!done) {
        self->h->flags1c |= 2;
        if (self->h->count > 0) {
            done = func_0209493c(self->h, 0x71, &data_020e29dc, -1, 0, 0x71, &data_020e29dc, 0x72, &data_020e29dc);
        }
    }

    if (!done) {
        func_020914dc(e);
    }

    return done;
}
