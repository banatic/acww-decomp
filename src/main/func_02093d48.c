/* func_02093d48 @ 0x02093d48, 0xcc bytes, Thumb, module main
 * mwccarm 1.2/base -O2,s
 */

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    char pad0[0xe - 0xc];
    short unk_0E;
    char pad1[0x14 - 0x10];
    int unk_14;
    char pad_18[0x1c - 0x18];
} Entry;

typedef struct {
    char pad0[0xc];
    int count;
    char pad1[0x18 - 0x10];
    int **unk_18;
    int flags1c;
    int unk_20;
    int unk_24;
    int unk_28;
} HObj;

typedef struct {
    char pad0[4];
    unsigned char id[4];
    char pad1[0xc - 8];
    HObj *h;
} UnkStruct_02093d48;

extern Entry data_021d52d8[];
extern int data_020e29dc;
extern int func_02094a4c(HObj *h, int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8);
extern void func_020914dc(Entry *e);

int func_02093d48(UnkStruct_02093d48 *self)
{
    unsigned char id[4];
    int done;
    Entry *e;

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
        HObj *h = self->h;
        h->unk_20 = e->unk_00 + (*h->unk_18)[1];
        h->unk_24 = e->unk_04 + (*h->unk_18)[2];
        h->unk_28 = e->unk_08 + (*h->unk_18)[3];

        func_02094a4c(self->h, 0x5f, (int) &data_020e29dc, -1, 0, -1, 0, -1, 0);

        if (e->unk_0E > 0) {
            e->unk_0E = (short) (e->unk_0E - 1);
        }
        done = 1;
    }

    if (!done) {
        self->h->flags1c |= 2;
        if (self->h->count > 0) {
            done = func_02094a4c(self->h, 0x5f, (int) &data_020e29dc, -1, 0, -1, 0, -1, 0);
        }
    }

    if (!done) {
        func_020914dc(e);
    }

    return done;
}
