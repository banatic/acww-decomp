/* quick_message_4: 21 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0203990c @ 0x0203990c, 0x1c bytes, Thumb
 * func_020398e8 @ 0x020398e8, 0x24 bytes, Thumb
 * func_020398d4 @ 0x020398d4, 0x14 bytes, Thumb
 * func_020398b0 @ 0x020398b0, 0x24 bytes, Thumb
 * func_02039860 @ 0x02039860, 0x50 bytes, Thumb
 * func_02039810 @ 0x02039810, 0x50 bytes, Thumb
 * func_02039800 @ 0x02039800, 0x10 bytes, Thumb
 * func_020397f0 @ 0x020397f0, 0x10 bytes, Thumb
 * func_020397a0 @ 0x020397a0, 0x50 bytes, Thumb
 * func_0203977c @ 0x0203977c, 0x24 bytes, Thumb
 * func_02039750 @ 0x02039750, 0x2c bytes, Thumb
 * func_020396fc @ 0x020396fc, 0x52 bytes, Thumb
 * func_020396dc @ 0x020396dc, 0x20 bytes, Thumb
 * func_020396d0 @ 0x020396d0, 0xa bytes, Thumb
 * func_02039668 @ 0x02039668, 0x68 bytes, Thumb
 * func_02039628 @ 0x02039628, 0x40 bytes, Thumb
 * func_020395a8 @ 0x020395a8, 0x80 bytes, Thumb
 * func_02039540 @ 0x02039540, 0x68 bytes, Thumb
 * func_02039510 @ 0x02039510, 0x30 bytes, Thumb
 * func_020394a4 @ 0x020394a4, 0x6c bytes, Thumb
 * func_02039474 @ 0x02039474, 0x30 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0xa0];
    void *unk_A0;
} UnkStruct_0203990c;

typedef struct {
    unsigned char pad_00[0xc];
    int unk_0C;
    unsigned char pad_10[0x94];
    int unk_A4;
    int pad_A8;
    int unk_AC;
    int pad_B0[2];
} UnkStruct_02039860;

typedef struct {
    unsigned char pad_00[4];
    UnkStruct_02039860 arr[4];
} UnkStruct_02039860_2;

typedef struct {
    unsigned char pad_00[0xc];
    int unk_0C;
    unsigned char pad_10[0x94];
    int unk_A4;
    int pad_A8;
    int unk_AC;
    int pad_B0[2];
} UnkStruct_02039810;

typedef struct {
    unsigned char pad_00[4];
    UnkStruct_02039810 arr[4];
} UnkStruct_02039810_2;

typedef struct {
    void *unk_00;
    char data[0x2e0];
    int arr_one[4];
    int arr_two[4];
} UnkStruct_020397a0;

struct UnkStruct_02039750 {
    void *unk_00;
    int unk_04;
};

typedef struct UnkStruct_020396fc {
    char pad_00[0xC];
    int unk_0C;
    char pad_10[0xA8];
} UnkStruct_020396fc;

struct UnkStruct_020396dc {
    char pad_00[0x64];
    int unk_64;
};

struct Node;

struct UnkStruct_02039668;

typedef struct Node {
    unsigned char pad_00[0xc];
    void *owner;
} Node;

typedef struct UnkStruct_02039668 {
    unsigned char pad_00[0x2e4];
    Node *array1[4];
    Node *array2[4];
} UnkStruct_02039668;

typedef struct {
    char pad_00[0x2e4];
    int array[4];
} UnkStruct_02039628;

typedef struct UnkStruct_02039540 {
    unsigned char pad_00[0x2e4];
    void *arr[4];
} UnkStruct_02039540;

typedef struct El El;

struct El {
    char pad_00[0xc];
    void *unk_0C;
    char pad_10[0x34];
    int unk_44;
};

typedef struct UnkStruct_02039510 UnkStruct_02039510;

struct UnkStruct_02039510 {
    char pad_00[0x2f4];
    El *array[4];
};

typedef struct Node_020394a4 Node_020394a4;

typedef struct Container Container;

struct Node_020394a4 {
    unsigned char pad_00[0xa4];
    int unk_A4;
    unsigned char pad_A8[8];
    int unk_B0;
};

struct Container {
    unsigned char pad_00[0x2f4];
    Node_020394a4 *arr[4];
};

typedef struct {
    char pad_00[0x2e4];
    int arr[4];
} Matcher;

extern void func_020a8fb8(void *);
extern unsigned char data_021c6738[];
extern void func_02039358(void *ptr);
extern void func_0203931c(int arg);
extern void *func_0203a1f8(void *);
extern void *func_0203a23c(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void func_020edb3c(void *self);
extern unsigned char data_020da5d8[];
extern void func_02039f0c(void *a, int b, int c, int d);
extern void func_020392a0(int a, void *b);
extern struct UnkStruct_020396dc *data_020ccf94;
extern int func_02039ebc(Node *node);
extern int func_02039444(void *, int);
extern void func_02039f30(void *p);
extern int func_02039edc(void *p);

void func_020396fc(void *arg0, int arg1, int arg2, int arg3);
int func_020396dc(int unused, int value);
int func_020396d0(int a, int b);
void func_02039668(struct UnkStruct_02039668 *self, int param);
int func_02039628(UnkStruct_02039628 *s, int val);
int func_02039474(Matcher *s, int value);

void func_0203990c(UnkStruct_0203990c *self)
{
    if (self->unk_A0 != 0) {
        func_020a8fb8(self->unk_A0);
        self->unk_A0 = 0;
    }
}

void func_020398e8(int a, int b, int c)
{
    func_020396fc((*(void **) data_021c6738), a, b, c);
}

void func_020398d4(unsigned int arg)
{
    func_02039668((struct UnkStruct_02039668 *) ((*(unsigned int *) data_021c6738)), arg);
}

void func_020398b0(void)
{
    int i;
    void *ptr;

    for (i = 0; i < 4; i++) {
        ptr = *(void **) data_021c6738;
        func_02039668((struct UnkStruct_02039668 *) ptr, i);
    }
}

int func_02039860(void)
{
    int ret = 0;
    int i;
    UnkStruct_02039860 *e;
    unsigned int flag;
    for (i = 0; i < 4; i++) {
        e = &(*(UnkStruct_02039860_2 **) data_021c6738)->arr[i];
        if (e->unk_0C != 0) {
            if (e->unk_A4 != 0) {
                goto set;
            }
        }
        if (e->unk_AC > 0) {
            flag = 1;
        } else {
            flag = 0;
        }
        if (flag > 0) {
        set:
            ret = 1;
            break;
        }
    }
    return ret;
}

int func_02039810(void)
{
    int ret = 0;
    int i;
    UnkStruct_02039810 *e;
    unsigned int flag;
    for (i = 0; i < 4; i++) {
        e = &(*(UnkStruct_02039810_2 **) data_021c6738)->arr[i];
        if (e->unk_0C == 0) {
            if (e->unk_A4 != 0) {
                goto set;
            }
        }
        if (e->unk_AC > 0) {
            flag = 1;
        } else {
            flag = 0;
        }
        if (flag > 0) {
        set:
            ret = 1;
            break;
        }
    }
    return ret;
}

void func_02039800(void)
{
    func_02039358(*(void **) data_021c6738);
}

void func_020397f0(void)
{
    func_0203931c((*(int *) data_021c6738));
}

UnkStruct_020397a0 *func_020397a0(UnkStruct_020397a0 *obj)
{
    int i;
    obj->unk_00 = (void *) ((char *) data_020da5d8);
    __cxa_vec_ctor((void *) (obj->data), 4, 0xb8, (((void (*)(void *)) func_0203a23c)), (((void (*)(void *)) func_0203a1f8)));
    for (i = 0; i < 4; i++) {
        obj->arr_one[i] = 0;
        obj->arr_two[i] = 0;
    }
    return obj;
}

void *func_0203977c(void *p)
{
    *(unsigned int *) p = (unsigned int) ((unsigned int *) data_020da5d8);
    __cxa_vec_cleanup((void *) ((char *) p + 4), 4, 0xb8, (((void (*)(void *)) func_0203a1f8)));
    return p;
}

struct UnkStruct_02039750 *func_02039750(struct UnkStruct_02039750 *self)
{
    self->unk_00 = (void *) data_020da5d8;
    __cxa_vec_cleanup((void *) (&self->unk_04), 4, 0xb8, (((void (*)(void *)) func_0203a1f8)));
    func_020edb3c(self);
    return self;
}

void func_020396fc(void *arg0, int arg1, int arg2, int arg3)
{
    int idx;
    UnkStruct_020396fc *r6;
    int ret;

    if (arg1 > 4) {
        return;
    }
    idx = func_020396dc((int) arg0, arg1);
    r6 = (UnkStruct_020396fc *) ((char *) arg0 + 4 + idx * 184);
    if (func_02039628((UnkStruct_02039628 *) arg0, (int) r6) == 0) {
        return;
    }
    ret = func_020396d0((int) arg0, arg1);
    func_02039f0c(r6, arg2, arg3, ret);
    if (r6->unk_0C != 0) {
        return;
    }
    func_020392a0(arg1, r6);
}

int func_020396dc(int unused, int value)
{
    return (value - data_020ccf94->unk_64 + 4) % 4;
}

int func_020396d0(int a, int b)
{
    if (b == 4) {
        b = 0;
    }
    return b;
}

void func_02039668(struct UnkStruct_02039668 *self, int param)
{
    void *key;
    int i;
    Node *node;

    if (param > 4) {
        return;
    }
    key = (void *) func_020396dc((int) self, param);

    for (i = 0; i < 4; i++) {
        node = self->array1[i];
        if (node != 0 && key == node->owner) {
            self->array1[i] = 0;
            break;
        }
    }

    for (i = 0; i < 4; i++) {
        node = self->array2[i];
        if (node != 0 && key == node->owner) {
            func_02039ebc(node);
            break;
        }
    }
}

int func_02039628(UnkStruct_02039628 *s, int val)
{
    int result = 0;
    if (func_02039474((Matcher *) s, val)) {
        result = 1;
    } else {
        int i;
        for (i = 0; i < 4; i++) {
            if (s->array[i] == 0) {
                s->array[i] = val;
                result = 1;
                break;
            }
        }
    }
    return result;
}

int func_020395a8(void *param0, void *param1)
{
    unsigned int result = 0;
    void *p;
    if (func_02039444((void *) param0, (int) param1) != 0) {
        func_02039ebc((Node *) param1);
    } else {
        unsigned int v = *(int *) ((char *) param1 + 0xac) > 0 ? 1 : result;
        if (v == 0) {
            unsigned int count;
            int i = 3;
            count = 0;
            for (; i >= 0; i--) {
                p = *(void **) ((char *) param0 + i * 4 + 0x2f4);
                if (p != 0) {
                    if (*(int *) ((char *) p + 0xc) != 0) {
                        count += 0x10;
                    }
                } else {
                    *(void **) ((char *) param0 + i * 4 + 0x2f4) = param1;
                    if (*(int *) ((char *) param1 + 0xc) == 0) {
                        count = 0;
                    }
                    *(int *) ((char *) param1 + 0x48) = count;
                    *(int *) ((char *) param1 + 0x44) = count;
                    func_02039f30(param1);
                    func_02039edc(param1);
                    result = 1;
                    break;
                }
            }
        }
    }
    return result;
}

void func_02039540(UnkStruct_02039540 *self)
{
    int i;
    int j;
    int k;

    for (i = 0; i < 4; i++) {
        if (self->arr[i] != 0 && func_020395a8((void *) self, self->arr[i]) != 0) {
            self->arr[i] = 0;
        }
    }
    for (j = 0; j < 4; j++) {
        if (self->arr[j] == 0) {
            for (k = j + 1; k < 4; k++) {
                if (self->arr[k] != 0) {
                    self->arr[j] = self->arr[k];
                    self->arr[k] = 0;
                    break;
                }
            }
        }
    }
}

void func_02039510(UnkStruct_02039510 *param)
{
    int idx;
    int val;
    El *el;

    idx = 3;
    val = 0;

    do {
        el = param->array[idx];
        if (el != 0 && el->unk_0C != 0) {
            el->unk_44 = val;
            val += 0x10;
        }
    } while (--idx >= 0);
}

void func_020394a4(Container *p)
{
    int i;
    for (i = 0; i < 4; i++) {
        Node_020394a4 *n = p->arr[i];
        if (n != 0) {
            if (n->unk_A4 == 0) {
                if (n->unk_B0 == 0) {
                    p->arr[i] = 0;
                }
            }
        }
    }
    {
        int a;
        for (a = 0; a < 4; a++) {
            if (p->arr[a] == 0) {
                int b;
                for (b = a + 1; b < 4; b++) {
                    if (p->arr[b] != 0) {
                        p->arr[a] = p->arr[b];
                        p->arr[b] = 0;
                        break;
                    }
                }
            }
        }
    }
}

int func_02039474(Matcher *s, int value)
{
    int found = 0;
    int i;
    int v;

    for (i = found; i < 4; i++) {
        v = s->arr[i];
        if (v == value) {
            found = 1;
            break;
        }
    }
    return found;
}
