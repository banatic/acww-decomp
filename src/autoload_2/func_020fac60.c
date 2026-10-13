/* func_020fac60 @ 0x020fac60, 0xbc bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

typedef struct UnkStruct_020fac60 UnkStruct_020fac60;
typedef struct UnkStruct_020fac60_2 UnkStruct_020fac60_2;
typedef struct UnkStruct_020fac60_3 UnkStruct_020fac60_3;
typedef struct UnkStruct_020fac60_4 UnkStruct_020fac60_4;
typedef struct UnkStruct_020fac60_5 UnkStruct_020fac60_5;
typedef struct UnkStruct_020fac60_6 UnkStruct_020fac60_6;
typedef struct Node Node;

typedef void (*Callback)(UnkStruct_020fac60 *self, Node *node, void *arg2);

struct Node {
    Node *next;
};

struct UnkStruct_020fac60_4 {
    unsigned int lower : 16;
    unsigned int bit16 : 1;
    unsigned int upper : 15;
};

struct UnkStruct_020fac60_5 {
    unsigned short lower : 7;
    unsigned short mode : 2;
    unsigned short upper : 7;
    unsigned char pad[0xd];
    unsigned char byte;
};

struct UnkStruct_020fac60_3 {
    UnkStruct_020fac60_4 *d;
    unsigned char pad[0x10];
    UnkStruct_020fac60_5 *e;
};

struct UnkStruct_020fac60_2 {
    unsigned char pad_00[0x10];
    Node *list;
    unsigned char pad1[0x4];
    UnkStruct_020fac60_3 *c;
};

struct UnkStruct_020fac60_6 {
    unsigned char data[0x14];
};

struct UnkStruct_020fac60 {
    unsigned char pad_00[0x20];
    UnkStruct_020fac60_6 *base;
    unsigned char pad1[0x10];
    UnkStruct_020fac60_2 *b;
};

extern void func_020fb8e8(UnkStruct_020fac60_6 *elem, int index, UnkStruct_020fac60_6 *base);
extern void func_020fd01c(UnkStruct_020fac60 *self, Node *node, void *arg2);
extern void func_020fc174(UnkStruct_020fac60 *self, Node *node, void *arg2);
extern void func_020fb9d4(UnkStruct_020fac60 *self, Node *node, void *arg2);

void func_020fac60(UnkStruct_020fac60 *self, void *arg2)
{
    UnkStruct_020fac60_2 *b;
    UnkStruct_020fac60_3 *c;
    UnkStruct_020fac60_5 *e;
    Node *node;
    int idx;
    Callback cb = 0;

    b = self->b;
    c = b->c;
    if (!c->d->bit16) {
        return;
    }
    e = c->e;
    idx = e->byte;
    func_020fb8e8(&self->base[idx], idx, self->base);
    e = c->e;
    switch (e->mode) {
        case 0:
            cb = func_020fd01c;
            break;
        case 1:
            cb = func_020fc174;
            break;
        case 2:
            cb = func_020fb9d4;
            break;
        default:
            break;
    }
    node = b->list;
    if (node != 0) {
        do {
            cb(self, node, arg2);
            node = node->next;
        } while (node != 0);
    }
}
