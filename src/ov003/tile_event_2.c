/* tile_event_2: 5 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02221488 @ 0x02221488, 0x2c bytes, Thumb
 * func_ov003_02221464 @ 0x02221464, 0x24 bytes, Thumb
 * func_ov003_022213f8 @ 0x022213f8, 0x6a bytes, Thumb
 * func_ov003_0222139c @ 0x0222139c, 0x5c bytes, Thumb
 * func_ov003_02221340 @ 0x02221340, 0x5c bytes, Thumb
 */

typedef struct {
    int pad_00;
    int flag;
    char rest[0x9C];
} Entry;

struct UnkStruct_022213f8 {
    int x, y;
};

struct UnkStruct_022213f8_2 {
    int x, y, z;
};

typedef struct {
    char pad_00[4];
    int unk_04;
    char pad_08[8];
    int unk_10;
    int unk_14;
    char pad_18[0x88];
    unsigned char unk_A0;
    char pad_A1[3];
} Elem;

typedef struct {
    int x;
    int y;
} UnkStruct_02221340;

extern void func_ov003_02222860(void *);
extern int func_020044a0(void *);
extern void *func_0204e414(void);
extern void func_ov003_02222880(int a, int b, struct UnkStruct_022213f8 *l1, struct UnkStruct_022213f8_2 *l2, int e,
                                unsigned short f, void *p, short g, int h);
extern int data_020ccf94;
extern int func_02073d90(int);
extern Elem data_ov003_0223cfe4[];

void func_ov003_02221488(void *p)
{
    int i;
    for (i = 0; i < 20; i++) {
        if (*(int *) ((char *) p + 4) != 0) {
            func_ov003_02222860(p);
        }
        func_020044a0((char *) p + 0x60);
        p = (char *) p + 0xa4;
    }
}

Entry *func_ov003_02221464(Entry *base, int idx)
{
    Entry *result = 0;
    int i;
    Entry *p;

    p = base + idx * 4;
    for (i = 0; i < 4; i++) {
        if (p->flag == 0) {
            result = p;
            break;
        }
        p++;
    }
    return result;
}

int func_ov003_022213f8(int a, int b, struct UnkStruct_022213f8 *c, struct UnkStruct_022213f8_2 *d, int e, unsigned short f,
                        short g, int h)
{
    void *alloc;
    int flag;
    int result;
    struct UnkStruct_022213f8 l1;
    struct UnkStruct_022213f8_2 l2;

    alloc = func_0204e414();
    if (alloc == 0) {
        return 0;
    }

    flag = 0;
    result = (int) func_ov003_02221464((Entry *) a, b);
    if (result != 0) {
        l2.x = d->x;
        l2.y = d->y;
        l2.z = d->z;
        l1.x = c->x;
        l1.y = c->y;
        func_ov003_02222880(result, b, &l1, &l2, e, f, alloc, g, h);
        flag = 1;
    }
    return flag;
}

int func_ov003_0222139c(int *a, int b, int *c, int *d, int e, unsigned short f, short g, int h)
{
    int v2[2];
    int v3[3];

    if (func_02073d90(data_020ccf94) == 0) {
        b = 0;
    }

    v3[0] = d[0];
    v3[1] = d[1];
    v3[2] = d[2];

    v2[0] = c[0];
    v2[1] = c[1];

    return func_ov003_022213f8((int) a, b, (struct UnkStruct_022213f8 *) v2, (struct UnkStruct_022213f8_2 *) v3, e, f, g, h);
}

int func_ov003_02221340(int idx, UnkStruct_02221340 *key)
{
    int found;
    int i;
    UnkStruct_02221340 loc;
    UnkStruct_02221340 *q;
    Elem *e;
    found = 0;
    e = &data_ov003_0223cfe4[idx * 4];
    i = 0;
    for (; i < 4; i++) {
        if (e->unk_04 != 0) {
            loc.x = e->unk_10;
            q = &loc;
            loc.y = e->unk_14;
            if ((loc.x == key->x) && (q->y == key->y)) {
                if (e->unk_A0 != 0) {
                    found = 1;
                }
                func_ov003_02222860(e);
                break;
            }
        }
        e++;
    }

    return found;
}
