/* func_020fa270 @ 0x020fa270, 0x14c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

// SPL emitter list step: ages each emitter and unlinks the finished ones.
// next is read first because the body may unlink the node.
struct UnkStruct_020fa270 {
    unsigned int e0 : 14;
    unsigned int e14 : 1;
    unsigned int e15 : 17;
    unsigned char pad_04[0x2e];
    unsigned short unk_32;
    unsigned char pad1[4];
    unsigned short unk_38;
};

struct Node {
    struct Node *next;
    unsigned char pad_04[8];
    unsigned int unk_0C;
    unsigned char pad1[4];
    unsigned int unk_14;
    struct UnkStruct_020fa270 **unk_18;
    unsigned int b0 : 1;
    unsigned int b1 : 1;
    unsigned int b2 : 1;
    unsigned int b3 : 1;
    unsigned int b4 : 1;
    unsigned int b5 : 27;
    unsigned char pad_20[0x18];
    unsigned short unk_38;
    unsigned char pad_3A[0x2e];
    unsigned int d0 : 16;
    unsigned int d16 : 3;
    unsigned int d19 : 13;
};

struct UnkStruct_020fa270_2 {
    unsigned int unk_00;
    struct Node *head;
    unsigned int unk_08;
    unsigned int unk_0C;
};

extern unsigned short data_021fd274;
extern void func_020fadf8(struct UnkStruct_020fa270_2 *, struct Node *);
extern int func_020ff83c(struct Node **, struct Node *);
extern void func_020ff8ec(unsigned int *, int);

void func_020fa270(struct UnkStruct_020fa270_2 *self)
{
    struct Node *n;
    struct Node *nx;
    struct UnkStruct_020fa270 *p;
    unsigned int v;

    n = self->head;
    if (n == 0) {
        goto tail;
    }
    do {
        p = *n->unk_18;
        nx = n->next;
        if (!n->b4) {
            if (n->unk_38 >= p->unk_32) {
                n->b4 = 1;
                n->unk_38 = 0;
            }
        }
        if (!n->b2) {
            v = n->d16;
            if (v == 0 || data_021fd274 == v - 1) {
                func_020fadf8(self, n);
            }
        }
        if ((p->e14 && p->unk_38 != 0 && n->b4 && n->unk_38 > p->unk_38) || n->b0) {
            if (n->unk_0C == 0 && n->unk_14 == 0) {
                func_020ff8ec(&self->unk_0C, func_020ff83c(&self->head, n));
            }
        }
        n = nx;
    } while (n != 0);
tail:
    data_021fd274 = data_021fd274 + 1;
    if (data_021fd274 > 1) {
        data_021fd274 = 0;
    }
}
