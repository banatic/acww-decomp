/* func_0209d238 @ 0x0209d238, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0209d238 {
    unsigned char unk_00;
    char pad_01[3];
    void *unk_04;
    char pad2[20];
};

struct UnkStruct_0209d238_2 {
    unsigned short unk_00;
    unsigned short pad2;
    unsigned int unk_04;
    int unk_08;
    struct UnkStruct_0209d238 *unk_0C;
};

struct UnkStruct_0209d238 *func_0209d238(struct UnkStruct_0209d238_2 *self, unsigned short *out)
{
    unsigned short v;
    struct UnkStruct_0209d238 *p;
    unsigned short i;
    unsigned int count;
    struct UnkStruct_0209d238 *base;
    struct UnkStruct_0209d238 *q;

    v = *out;
    if (v == 0xffff) {
        base = self->unk_0C;
        p = base;
        i = 0;
        count = self->unk_04;
        while (i < count) {
            if (p->unk_00 == 0 && i != self->unk_00) {
                p->unk_00 = 1;
                *out = i;
                self->unk_08++;
                return p;
            }
            p++;
            i = (unsigned short) (i + 1);
        }
        q = base + self->unk_00;
        if (q->unk_00 == 0) {
            q->unk_00 = 1;
            *out = self->unk_00;
            self->unk_08++;
            return q;
        }
        goto ret0;
    }
    if (v < self->unk_04) {
        return self->unk_0C + v;
    }
    *out = 0xffff;
ret0:
    return 0;
}
