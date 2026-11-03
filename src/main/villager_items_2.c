/* villager_items_2: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0207dfec @ 0x0207dfec, 0x1c bytes, Thumb
 * func_0207dfd4 @ 0x0207dfd4, 0x18 bytes, Thumb
 * func_0207df88 @ 0x0207df88, 0x4c bytes, Thumb
 * func_0207df18 @ 0x0207df18, 0x70 bytes, Thumb
 */

struct UnkStruct_0207dfd4 {
    char pad_00[0x7b0];
    unsigned short arr[4];
};

typedef struct {
    char pad_00[0x7b0];
    unsigned short arr[4];
} UnkStruct_0207df88;

typedef struct {
    unsigned char pad_00[0x7b0];
    unsigned short arr[4];
} UnkStruct_0207df18;

extern int func_0207deb4(void *a, unsigned short *v);
extern void func_020782d8(void *a, int x);

void func_0207dfec(unsigned short *base)
{
    unsigned short *p;
    int i;
    unsigned short v;
    p = (unsigned short *) ((unsigned char *) base + 0x7b0);
    v = 0xfff1;
    for (i = 0; i < 4; i++) {
        *p++ = v;
    }
}

unsigned short *func_0207dfd4(struct UnkStruct_0207dfd4 *s, unsigned int index)
{
    if (index < 4) {
        return &s->arr[index];
    }
    return 0;
}

void func_0207df88(UnkStruct_0207df88 *self)
{
    int i, j;
    i = 0;
    while (i < 3) {
        if (self->arr[i] == 0xfff1) {
            j = i + 1;
            while (j < 4) {
                if (self->arr[j] != 0xfff1) {
                    self->arr[i] = self->arr[j];
                    self->arr[j] = 0xfff1;
                    break;
                }
                ++j;
            }
            if (j == 4) {
                return;
            }
        }
        ++i;
    }
}

void func_0207df18(UnkStruct_0207df18 *a, unsigned short *newVal)
{
    int idx;
    int i;
    unsigned short empty;

    func_0207df88((UnkStruct_0207df88 *) a);
    empty = 0xfff1;
    idx = func_0207deb4(a, &empty);
    if (idx != -1) {
        a->arr[idx] = *newVal;
    } else {
        for (i = 0; i < 3; i++) {
            a->arr[i] = a->arr[i + 1];
        }
        a->arr[3] = *newVal;
    }
    func_020782d8(a, (int) func_0207dfd4((struct UnkStruct_0207dfd4 *) a, 0));
}
