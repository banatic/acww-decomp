/* func_ov009_022645b8 @ 0x022645b8, 0x60 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022645b8_2 {
    char pad_00[0x284];
    void *slots;
};
struct Container {
    char pad_00[0x1c];
    void *arr;
};
struct Elem {
    int pad_00;
    int unk_04;
    int unk_08;
};
struct UnkStruct_022645b8 {
    int unk_00, t1, t2;
};
struct UnkStruct_022645b8_3 {
    int unk_00, unk_04, unk_08;
};

extern struct Container *func_ov009_02264884(struct UnkStruct_022645b8_2 *self);
extern unsigned int func_ov009_02264394(void *arr);
extern struct Elem *func_ov009_02264388(void *arr, int idx);
extern void func_ov009_02265660(struct UnkStruct_022645b8_3 *outbuf, struct UnkStruct_022645b8 *tmp, void *param2);
extern void func_020aced0(void *dst, struct UnkStruct_022645b8_3 *item);

void func_ov009_022645b8(struct UnkStruct_022645b8_2 *self, void *param2)
{
    struct Container *c;
    void *slot;
    unsigned int i;

    c = func_ov009_02264884(self);
    if (!c) {
        return;
    }
    slot = self->slots;
    if (!slot) {
        return;
    }
    for (i = 0; i < func_ov009_02264394(c->arr); i++) {
        struct Elem *e;
        struct UnkStruct_022645b8 tmp;
        struct UnkStruct_022645b8_3 outbuf;
        int f8v;

        e = func_ov009_02264388(c->arr, i);
        f8v = e->unk_08;
        tmp.unk_00 = e->unk_04;
        tmp.t1 = 0;
        tmp.t2 = f8v;
        func_ov009_02265660(&outbuf, &tmp, param2);
        func_020aced0(slot, &outbuf);
        slot = (char *) slot + 0x34;
    }
}
