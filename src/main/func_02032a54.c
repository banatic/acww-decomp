/* func_02032a54 @ 0x02032a54, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Elem {
    unsigned char pad_00[8];
    int unk_08;
    unsigned char pad_0C[0x38 - 0xc];
    unsigned char unk_38;
    unsigned char pad_39[0x40 - 0x39];
};

struct UnkStruct_02032a54_2 {
    unsigned char pad_00[4];
    int cmpVal;
};
struct UnkStruct_02032a54 {
    unsigned char pad_00[4];
    int flags;
    int val;
};

struct UnkStruct_02032a54_3 {
    unsigned char pad_00[4];
    struct UnkStruct_02032a54 *c;
    struct UnkStruct_02032a54_2 *b;
};

extern int func_0202fb8c(void *src, unsigned int size);

void func_02032a54(struct UnkStruct_02032a54_3 *self, struct Elem *list)
{
    volatile unsigned char scratch[8];
    int count;
    struct Elem *end;
    int mask;
    struct Elem *e;

    (void) &scratch;
    count = *(int *) ((char *) list + 0xa00);
    end = (struct Elem *) ((char *) list + (count << 6));
    mask = 1;

    for (e = list; e < end; e = (struct Elem *) ((char *) e + 0x40)) {
        if (self->b->cmpVal < e->unk_08) {
            if (func_0202fb8c(e, (unsigned int) self->b)) {
                self->b->cmpVal = e->unk_08;
                self->c->flags |= mask;
                self->c->val = e->unk_38;
            }
        }
    }
}
