/* scene_actor_files_6: 3 functions, module ov009
 * mwccarm 1.2/base -O4,s
 * func_ov009_02265634 @ 0x02265634, 0x2a bytes, Thumb
 * func_ov009_02265630 @ 0x02265630, 0x2 bytes, Thumb
 * func_ov009_022655f8 @ 0x022655f8, 0x38 bytes, Thumb
 */

struct UnkStruct_02265634 {
    int a;         // 0x00
    int b;         // 0x04
    int c;         // 0x08
    int d;         // 0x0c
    int e;         // 0x10
    int unk_14;    // 0x14
    int g;         // 0x18
    int h;         // 0x1c
    int arr[4];    // 0x20
    int pad_30[4]; // 0x30
    int i;         // 0x40
    int j;         // 0x44
    int k;         // 0x48
    int l;         // 0x4c
};

struct UnkStruct_022655f8 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1C;
};

void func_ov009_02265634(struct UnkStruct_02265634 *p)
{
    int zero = 0;
    unsigned int idx;

    p->a = zero;
    p->b = zero;
    p->unk_14 = zero;
    p->g = zero;
    p->h = zero;
    p->c = zero;
    p->d = zero;
    p->e = zero;
    p->i = zero;
    p->j = zero;
    p->k = zero;
    p->l = zero;

    for (idx = 0; idx < 4; idx++) {
        p->arr[idx] = zero;
    }
}

void func_ov009_02265630(void *element) {}

int func_ov009_022655f8(struct UnkStruct_022655f8 *self)
{
    if (self->unk_00 != 0 || self->unk_04 != 0 || self->unk_14 != 0 || self->unk_18 != 0 || self->unk_1C != 0 ||
        self->unk_08 != 0 || self->unk_0C != 0 || self->unk_10 != 0) {
        return 1;
    }
    return 0;
}
