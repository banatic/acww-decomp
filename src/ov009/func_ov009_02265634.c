/* func_ov009_02265634 @ 0x02265634, 0x2a bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
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
