/* func_0209251c @ 0x0209251c, 0xb4 bytes, Thumb, module main
 * mwccarm 1.2/base -O2,s
 */

typedef struct {
    unsigned char b[4];
} Key;
typedef struct {
    int x;
    int y;
    int z;
} Vec;
typedef struct {
    int pad_00;
    int unk_04;
    int unk_08;
    int unk_0C;
} UnkStruct_0209251c;
typedef struct {
    UnkStruct_0209251c *p;
} Mid;

typedef struct Node Node;
struct Node {
    Node *next;
    char pad_04[0x20];
    unsigned short unk_24;
    unsigned short unk_26;
    char pad_28[8];
    int unk_30;
};

typedef struct {
    char pad_00[8];
    Node *head;
    char pad_0C[0xc];
    Mid *unk_18;
    int pad_1C;
    int unk_20;
    int unk_24;
    int unk_28;
    char pad_2C[0x54 - 0x2c];
    int unk_54;
} UnkStruct_0209251c_2;

typedef struct {
    char pad_00[4];
    Key key;
    char pad_08[4];
    UnkStruct_0209251c_2 *unk_0C;
} UnkStruct_0209251c_3;

typedef struct {
    int x;
    int y;
    int z;
    char pad_0C[2];
    short d;
    short e;
    int unk_14;
    int pad_18;
} UnkStruct_0209251c_4;

extern UnkStruct_0209251c_4 data_021d52d8[];
extern void func_020914dc(UnkStruct_0209251c_4 *);

int func_0209251c(UnkStruct_0209251c_3 *o)
{
    struct {
        Key k;
        Vec v;
    } L;
    UnkStruct_0209251c_4 *t;
    UnkStruct_0209251c_2 *s;
    Node *n;
    int ret;
    unsigned char *src;
    unsigned char *dst;
    unsigned int cnt;
    UnkStruct_0209251c_2 *s2;
    Node *n2;

    src = (unsigned char *) o + 4;
    dst = (unsigned char *) &L;
    cnt = 4;
    do {
        *dst++ = *src++;
    } while (--cnt != 0);

    t = &data_021d52d8[*(unsigned char *) &L];
    ret = 0;

    if (t->unk_14 != -1 && t->d != 0) {
        L.v.x = t->x;
        L.v.y = t->y;
        L.v.z = t->z;
        s = o->unk_0C;
        s->unk_20 = L.v.x + s->unk_18->p->unk_04;
        s->unk_24 = L.v.y + s->unk_18->p->unk_08;
        s->unk_28 = L.v.z + s->unk_18->p->unk_0C;

        if (t->d > 0) {
            t->d--;
        }

        o->unk_0C->unk_54 = t->e;
        n = o->unk_0C->head;
        while (n != 0) {
            n->unk_30 = t->e;
            n = n->next;
        }
        ret = 1;
    }

    if (!ret) {
        s2 = o->unk_0C;
        n2 = s2->head;
        while (n2 != 0) {
            n2->unk_26 = n2->unk_24;
            n2 = n2->next;
        }
        func_020914dc(t);
    }

    return ret;
}
