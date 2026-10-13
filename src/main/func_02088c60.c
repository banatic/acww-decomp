/* func_02088c60 @ 0x02088c60, 0x94 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a, b, c, d;
} Quad;
typedef struct {
    char pad_00[6];
    short v;
} UnkStruct_02088c60;
typedef struct {
    UnkStruct_02088c60 unk_00, s1, s2, s3;
} Entry;

int func_02088c60(Entry *table, int *countp, Quad *q)
{
    unsigned int *qu = (unsigned int *) q;
    unsigned short c0 = (unsigned short) (qu[0] >> 4);
    unsigned short c1 = (unsigned short) (qu[1] >> 4);
    unsigned short c2 = (unsigned short) (qu[2] >> 4);
    unsigned short c3 = (unsigned short) (qu[3] >> 4);
    int i = 0;
    int count = *countp;

    for (; i < count; i += 4) {
        Entry *e = (Entry *) ((char *) table + i * 8);
        if (c0 != (unsigned short) e->unk_00.v) {
            continue;
        }
        if (c1 != (unsigned short) e->s1.v) {
            continue;
        }
        if (c2 != (unsigned short) e->s2.v) {
            continue;
        }
        if (c3 != (unsigned short) e->s3.v) {
            continue;
        }
        return i >> 2;
    }

    if (count < 0x80) {
        Entry *e = (Entry *) ((char *) table + count * 8);
        int ret;
        e->unk_00.v = (short) (q->a >> 4);
        e->s1.v = (short) (q->b >> 4);
        e->s2.v = (short) (q->c >> 4);
        e->s3.v = (short) (q->d >> 4);
        ret = *countp >> 2;
        *countp = *countp + 4;
        return ret;
    }
    return -1;
}
