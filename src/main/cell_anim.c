/* cell_anim: 15 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208a1f8 @ 0x0208a1f8, 0x14 bytes, Thumb
 * func_0208a1f4 @ 0x0208a1f4, 0x2 bytes, Thumb
 * func_0208a1f0 @ 0x0208a1f0, 0x4 bytes, Thumb
 * func_0208a1ec @ 0x0208a1ec, 0x4 bytes, Thumb
 * func_0208a1e8 @ 0x0208a1e8, 0x4 bytes, Thumb
 * func_0208a1e0 @ 0x0208a1e0, 0x6 bytes, Thumb
 * func_0208a1d0 @ 0x0208a1d0, 0xe bytes, Thumb
 * func_0208a1cc @ 0x0208a1cc, 0x4 bytes, Thumb
 * func_0208a1c8 @ 0x0208a1c8, 0x4 bytes, Thumb
 * func_0208a1b0 @ 0x0208a1b0, 0x16 bytes, Thumb
 * func_0208a198 @ 0x0208a198, 0x16 bytes, Thumb
 * func_0208a160 @ 0x0208a160, 0x38 bytes, Thumb
 * func_0208a158 @ 0x0208a158, 0x6 bytes, Thumb
 * func_0208a144 @ 0x0208a144, 0x14 bytes, Thumb
 * func_0208a0c8 @ 0x0208a0c8, 0x7a bytes, Thumb
 */

struct UnkStruct_0208a1f8 {
    unsigned int a;
    unsigned int b;
    unsigned int c;
    unsigned int d;
    unsigned int e;
};

struct UnkStruct_0208a1d0 {
    int value;
    char pad_04[8];
};

struct UnkStruct_0208a1d0_2 {
    struct UnkStruct_0208a1d0 *array;
};

struct UnkStruct_0208a1d0_3 {
    struct UnkStruct_0208a1d0_2 *inner;
    int index;
};

typedef struct Elem {
    char pad_00[8];
    short value;
    char pad_0A[2];
} Elem;

typedef struct UnkStruct_0208a1b0_2 {
    void *array;
} UnkStruct_0208a1b0_2;

typedef struct UnkStruct_0208a1b0 {
    void *b;
    int default_index;
} UnkStruct_0208a1b0;

typedef struct {
    char pad_00[10];
    short value;
} Elem_0208a198;

typedef struct {
    Elem_0208a198 *array;
} UnkStruct_0208a198;

typedef struct {
    UnkStruct_0208a198 *a;
    int default_index;
} Param;

typedef struct Elem_0208a160 {
    int a;
    int b;
    int c;
} Elem_0208a160;

typedef struct UnkStruct_0208a160 {
    Elem_0208a160 *arr;
    int count;
} UnkStruct_0208a160;

typedef struct UnkStruct_0208a160_2 {
    UnkStruct_0208a160 *inner;
    int index;
    int value;
    int pad_0C;
    int type;
} UnkStruct_0208a160_2;

typedef struct {
    unsigned char pad_00[12];
    unsigned long unk_0C;
} UnkStruct_0208a158;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
} Frame;

typedef struct {
    Frame *frames;
    int count;
} Res;

typedef struct {
    Res *res;
    int idx;
    int acc;
    int step;
    int flag;
} UnkStruct_0208a0c8;

void func_0208a1f8(struct UnkStruct_0208a1f8 *s)
{
    s->a = 0;
    s->b = 0;
    s->c = 0;
    s->d = 0x1000;
    s->e = 0;
}

void func_0208a1f4(void *object) {}

void func_0208a1f0(int *p0, int p1)
{
    p0[0] = p1;
}

void func_0208a1ec(int *p0, int p1)
{
    p0[4] = p1;
}

void *func_0208a1e8(int *p0, int p1)
{
    p0[3] = p1;
    return p0;
}

void *func_0208a1e0(int *p, int a, int b)
{
    p[1] = a;
    p[2] = b;
    return p;
}

int func_0208a1d0(struct UnkStruct_0208a1d0_3 *arg)
{
    return arg->inner->array[arg->index].value;
}

int func_0208a1cc(int *p0)
{
    return p0[1];
}

int func_0208a1c8(int *p0)
{
    return p0[0];
}

short func_0208a1b0(UnkStruct_0208a1b0 *a0, int index)
{
    UnkStruct_0208a1b0_2 *b;
    Elem *arr;
    if (index < 0) {
        index = a0->default_index;
    }
    b = a0->b;
    arr = b->array;
    return arr[index].value;
}

short func_0208a198(Param *param, int index)
{
    int idx = index;
    if (idx < 0) {
        idx = param->default_index;
    }
    return (param->a->array + idx)->value;
}

int func_0208a160(UnkStruct_0208a160_2 *self)
{
    int result = 0;
    UnkStruct_0208a160 *inner;
    int idx;
    int val;
    int shifted;
    Elem_0208a160 *arr;

    if (self->type == 1) {
        inner = self->inner;
        idx = self->index;
        if (idx >= inner->count - 1) {
            val = self->value;
            shifted = val >> 12;
            arr = inner->arr;
            if (shifted >= arr[idx].b - 1) {
                result = 1;
            }
        }
    }
    return result;
}

void func_0208a158(UnkStruct_0208a158 *p)
{
    p->unk_0C = 0;
}

void *func_0208a144(void *param0)
{
    int local;

    *(unsigned int *) ((char *) param0 + 0xc) = 0x1000;
    local = 0;
    return func_0208a1e0((int *) param0, local, 0);
}

void func_0208a0c8(UnkStruct_0208a0c8 *s)
{
    int n;

    if (s->flag == 0) {
        s->acc = s->acc + s->step;
        if ((s->acc >> 12) >= s->res->frames[s->idx].unk_04) {
            s->acc = 0;
            n = s->res->count;
            s->idx = s->idx + 1;
            if (s->idx >= n) {
                s->idx = 0;
            }
        }
    } else {
        s->acc = s->acc + s->step;
        if ((s->acc >> 12) >= s->res->frames[s->idx].unk_04) {
            n = s->res->count;
            s->idx = s->idx + 1;
            if (s->idx < n) {
                s->acc = 0;
            } else {
                s->idx = n - 1;
            }
        }
    }
}
