/* field_collision_2: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02032eb8 @ 0x02032eb8, 0x54 bytes, Thumb
 * func_02032e80 @ 0x02032e80, 0x36 bytes, Thumb
 */

typedef struct Src {
    int a, b, c;
} Src;

typedef struct Node {
    char pad_00[0x14];
    unsigned char unk_14;
    char pad_15[0x1c - 0x15];
    int type;
    char pad_20[0x24 - 0x20];
} Node;

typedef struct Header {
    int count;
    Node arr[1];
} Header;

typedef struct {
    unsigned int count;
    char pad_04[0x20];
} UnkStruct_02032e80;

extern int func_02030580(Node *p, Src *src, int extra);
extern void func_020330bc(void *entry, int p2, int p3, int p4, int a, int b);

int func_02032eb8(Header *h, Src *src, int extra, int *out, unsigned int mode, int value)
{
    Node *start = h->arr;
    Node *p;
    volatile int a, b, c;
    for (p = start; p < start + h->count; p++) {
        a = src->a;
        b = src->b;
        c = src->c;
        if (p->type == 1 && func_02030580(p, src, extra)) {
            *out = p->unk_14;
            return 1;
        }
    }
    return 0;
}

int func_02032e80(UnkStruct_02032e80 *self, int p2, int p3, int p4, int a, int b)
{
    if (self->count >= 0x10) {
        goto fail;
    }
    func_020330bc((char *) self + 4 + *(volatile unsigned int *) &self->count * 0x24, p2, p3, p4, a, b);
    self->count++;
    return 1;
fail:
    return 0;
}
