/* music_queue_2: 27 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020355e0 @ 0x020355e0, 0x30 bytes, Thumb
 * func_020355cc @ 0x020355cc, 0x14 bytes, Thumb
 * func_020355b8 @ 0x020355b8, 0x14 bytes, Thumb
 * func_02035510 @ 0x02035510, 0xa8 bytes, Thumb
 * func_02035494 @ 0x02035494, 0x7c bytes, Thumb
 * func_02035404 @ 0x02035404, 0x90 bytes, Thumb
 * func_0203539c @ 0x0203539c, 0x68 bytes, Thumb
 * func_02035344 @ 0x02035344, 0x58 bytes, Thumb
 * func_02035294 @ 0x02035294, 0xb0 bytes, Thumb
 * func_02035240 @ 0x02035240, 0x54 bytes, Thumb
 * func_020351ec @ 0x020351ec, 0x54 bytes, Thumb
 * func_020351c4 @ 0x020351c4, 0x28 bytes, Thumb
 * func_02035198 @ 0x02035198, 0x2a bytes, Thumb
 * func_02035170 @ 0x02035170, 0x28 bytes, Thumb
 * func_02035148 @ 0x02035148, 0x28 bytes, Thumb
 * func_02035104 @ 0x02035104, 0x44 bytes, Thumb
 * func_020350a4 @ 0x020350a4, 0x60 bytes, Thumb
 * func_02035040 @ 0x02035040, 0x64 bytes, Thumb
 * func_02035038 @ 0x02035038, 0x6 bytes, Thumb
 * func_02034fec @ 0x02034fec, 0x4c bytes, Thumb
 * func_02034fac @ 0x02034fac, 0x40 bytes, Thumb
 * func_02034f78 @ 0x02034f78, 0x34 bytes, Thumb
 * func_02034f44 @ 0x02034f44, 0x34 bytes, Thumb
 * func_02034f14 @ 0x02034f14, 0x30 bytes, Thumb
 * func_02034ee4 @ 0x02034ee4, 0x30 bytes, Thumb
 * func_02034ebc @ 0x02034ebc, 0x28 bytes, Thumb
 * func_02034e78 @ 0x02034e78, 0x44 bytes, Thumb
 */

typedef struct UnkStruct_020355e0 {
    unsigned char pad_00[4];
    unsigned short unk_04;
    unsigned char pad_06[22];
} UnkStruct_020355e0;

typedef struct {
    unsigned char pad_00[0x1c0];
    unsigned int unk_1C0;
    unsigned char unk_1C4[0x24c - 0x1c4];
    unsigned char unk_24C[0x264 - 0x24c];
    unsigned char unk_264[0x2a0 - 0x264];
    unsigned char unk_2A0[0x2b4 - 0x2a0];
    unsigned char unk_2B4[0x2d0 - 0x2b4];
    unsigned char unk_2D0[0x2e4 - 0x2d0];
    unsigned char unk_2E4[0x2f0 - 0x2e4];
    unsigned char unk_2F0[0x2f4 - 0x2f0];
    unsigned char unk_2F4;
} UnkStruct_02035510;

typedef struct {
    char data[28];
} Elem;

typedef struct {
    char pad_00[28];
} UnkStruct_020351c4;

typedef struct {
    char data[28];
} UnkStruct_02035198;

typedef struct {
    unsigned char pad_00[0x13];
    unsigned char flag;
    unsigned char pad_14[0x08];
} Entry;

typedef struct {
    Entry array[16];
    int count;
} Container;

typedef struct {
    int pad_00;
    unsigned short unk_04;
    unsigned char pad_06[2];
    int unk_08;
    unsigned char pad_0C[7];
    unsigned char unk_13;
    unsigned char pad_14[8];
} UnkStruct_020350a4;

typedef struct {
    int pad_00[2];
    int unk_08;
} UnkStruct_020350a4_2;

typedef struct {
    UnkStruct_020350a4 arr[0x18];
    unsigned char pad_2A0[0x14];
    int unk_2B4;
} UnkStruct_020350a4_3;

typedef struct {
    unsigned char pad_00[18];
    unsigned char unk_12;
} UnkStruct_02035038;

typedef struct {
    int a;
    int b;
} Pair;

typedef struct {
    char pad_00[4];
    unsigned short unk_04;
    char pad_06[12];
    unsigned char unk_12;
    unsigned char unk_13;
    unsigned char unk_14;
    char pad_15[0x1c0 - 0x15];
    int unk_1C0;
    char pad_1C4[0x2b4 - 0x1c4];
    char unk_2B4;
} UnkStruct_02034fec;

typedef struct UnkStruct_02034fac {
    unsigned char unk_00[0x11];
    unsigned char unk_11;
    unsigned char pad_12;
    unsigned char flag_0x13;
    unsigned char rest[0x08];
} UnkStruct_02034fac;

typedef struct {
    UnkStruct_02034fac elements[16];
    int count;
} Container_02034fac;

typedef struct {
    unsigned char pad_00[0x12];
    unsigned char flag;
    unsigned char pad_13[0x9];
} Elem_02034f44;

typedef struct {
    Elem_02034f44 arr[16];
    int count;
} UnkStruct_02034f44;

typedef struct {
    int key;
    unsigned char pad_04[0x18];
} UnkStruct_02034f14;

typedef struct {
    char pad_00[0x13];
    unsigned char flag;
    char pad_14[0x08];
} UnkStruct_02034ebc;

extern unsigned char *data_021c526c;
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern int *func_0203652c(void *a, void *b);
extern void func_02037454(void *a);
extern void *func_020369fc(void *a, void *b);
extern void func_02036870(void *a, void *b);
extern void *func_02035ff8(void *a, void *b);
extern void func_02035f50(void *a, void *b);
extern void func_02035b20(void *a, void *b);
extern void func_02035a24(void *a);
extern void func_020374cc(void *);
extern int func_020374fc(void *);
extern void func_02035a18(void *);
extern void func_02035b14(void *);
extern void func_02035f44(void *);
extern void func_02035ff4(void *);
extern void func_02036864(void *);
extern void *func_020369d0(void *);
extern void func_02037450(void *);
extern void *func_02036510(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void func_020374ac(void *p);
extern void func_020364ec(void *p);
extern void func_0203743c(void *p);
extern void func_02036980(void *p);
extern void func_02036830(void *p);
extern void func_02035fc0(void *p);
extern void func_02035dc8(void *p);
extern void func_02035a6c(void *p);
extern void func_02035a64(void *ptr);
extern void func_02035dc0(void *ptr);
extern void func_02036828(void *ptr);
extern void func_02036960(void *ptr);
extern void func_02037438(void *ptr);
extern void func_020364e8(void *ptr);
extern void func_02035a60(void *);
extern void func_02035db8(void *);
extern void func_02037430(void *);
extern void func_02036940(void *);
extern void func_0203680c(void *);
extern void func_02034dcc(void *);
extern void func_02034dc8(void *receiver);
extern void func_02035a30(void *);
extern void func_02035d8c(void *);
extern void func_020367ec(void *);
extern void func_02036920(void *);
extern void func_0203741c(void *);
extern void func_02036490(void *);
extern unsigned char data_020e54a8;
extern void func_020368f0(unsigned int);
extern void func_020367cc(unsigned int);
extern void func_020368c0(unsigned int);
extern void func_02036788(unsigned int);
extern void func_020364c0(void *);
extern void func_02035f6c(void *);
extern void func_02035800(void *);
extern void func_02035fe4(int *, int);
extern void func_02037470(void *a, void *b);
extern void func_02035fec(void *p, int value);
extern Pair data_020da26c;
extern void func_02034e28(void *self, Pair p);
extern int func_02037458(void *);

void func_02035104(void *p);
void func_020350a4(UnkStruct_020350a4_3 *self);
void func_02035040(void *self);
void func_02034fec(UnkStruct_02034fec *self);
void func_02034fac(Container_02034fac *c);
int func_02034f78(unsigned char *ptr, int *value);
int func_02034f44(UnkStruct_02034f44 *p);
int func_02034f14(unsigned char *p, int key);
int func_02034ee4(char *base, unsigned short key);
UnkStruct_02034ebc *func_02034ebc(UnkStruct_02034ebc *array, int count);
void func_02034e78(void *self, int start);

unsigned short func_020355e0(void)
{
    int index;
    unsigned short result;

    index = func_02034f44((UnkStruct_02034f44 *) ((*(UnkStruct_020355e0 **) &data_021c526c)));
    result = 0xffff;
    if (index >= 0) {
        result = (*(UnkStruct_020355e0 **) &data_021c526c)[index].unk_04;
    }
    return result;
}

void func_020355cc(void)
{
    unsigned char *ptr;
    unsigned char value;

    value = 0;
    ptr = data_021c526c;
    ptr[0x2f4] = value;
}

void func_020355b8(void)
{
    data_021c526c[0x2f4] = 1;
}

UnkStruct_02035510 *func_02035510(UnkStruct_02035510 *self)
{
    __cxa_vec_ctor((void *) (self), 0x10, 0x1c, (((void (*)(void *)) func_020374fc)), (void (*)(void *)) func_020374cc);
    self->unk_1C0 = 0;
    func_0203652c(self->unk_1C4, self);
    func_02037454(self->unk_24C);
    func_020369fc(self->unk_264, self);
    func_02036870(self->unk_2A0, self);
    func_02035ff8(self->unk_2B4, self);
    func_02035f50(self->unk_2D0, self);
    func_02035b20(self->unk_2E4, self);
    func_02035a24(self->unk_2F0);
    self->unk_2F4 = 0;
    return self;
}

void *func_02035494(void *param)
{
    func_02035a18((char *) param + 0x2F0);
    func_02035b14((char *) param + 0x2E4);
    func_02035f44((char *) param + 0x2D0);
    func_02035ff4((char *) param + 0x2B4);
    func_02036864((char *) param + 0x2A0);
    func_020369d0((char *) param + 0x264);
    func_02037450((char *) param + 0x24C);
    func_02036510((char *) param + 0x1C4);
    __cxa_vec_cleanup((void *) (param), 0x10, 0x1C, (void (*)(void *)) func_020374cc);
    return param;
}

void func_02035404(void *self)
{
    char *end;
    Elem *p;

    (*(void **) &data_021c526c) = self;
    end = (char *) self + 0x1c0;
    p = (Elem *) self;
    while ((char *) p < end) {
        func_020374ac(p);
        p++;
    }
    *(int *) ((char *) self + 0x1c0) = 0;
    func_020364ec((char *) self + 0x1c4);
    func_0203743c((char *) self + 0x24c);
    func_02036980((char *) self + 0x264);
    func_02036830((char *) self + 0x2a0);
    func_02035fc0((char *) self + 0x2b4);
    func_02035dc8((char *) self + 0x2d0);
    func_02035a6c((char *) self + 0x2e4);
    *(char *) ((char *) self + 0x2f4) = 0;
}

void func_0203539c(void *base)
{
    func_02035a64((char *) base + 0x2e4);
    func_02035dc0((char *) base + 0x2d0);
    func_02035fc0((char *) base + 0x2b4);
    func_02036828((char *) base + 0x2a0);
    func_02036960((char *) base + 0x264);
    func_02037438((char *) base + 0x24c);
    func_020364e8((char *) base + 0x1c4);
    (*(int *) &data_021c526c) = 0;
}

void func_02035344(void *p)
{
    func_02035a60((char *) p + 0x2e4);
    func_02035db8((char *) p + 0x2d0);
    func_02037430((char *) p + 0x24c);
    func_02036940((char *) p + 0x264);
    func_0203680c((char *) p + 0x2a0);
    func_02035104(p);
    func_02034dcc(p);
    func_02034dc8(p);
}

void func_02035294(void)
{
    unsigned char *p;
    unsigned char *end;

    func_02035a30(data_021c526c + 0x2e4);
    func_02035d8c(data_021c526c + 0x2d0);
    func_02035fc0(data_021c526c + 0x2b4);
    func_020367ec(data_021c526c + 0x2a0);
    func_02036920(data_021c526c + 0x264);
    func_0203741c(data_021c526c + 0x24c);
    func_02036490(data_021c526c + 0x1c4);

    p = data_021c526c;
    end = data_021c526c + 0x1c0;
    while (p < end) {
        func_020374ac(p);
        p += 0x1c;
    }

    *(unsigned int *) (data_021c526c + 0x1c0) = 0;
    *(unsigned char *) (data_021c526c + 0x2f4) = 0;
}

void func_02035240(void)
{
    unsigned int tmp;
    unsigned int cond;
    unsigned int cond2;

    tmp = data_020e54a8;
    if (tmp == 0) {
        cond = 1;
    } else {
        cond = 0;
    }

    if (cond != 0) {
        func_020368f0((*(unsigned int *) &data_021c526c) + 0x264);
    } else {
        if (tmp == 1) {
            cond2 = 1;
        } else {
            cond2 = 0;
        }

        if (cond2 != 0) {
            func_020367cc((*(unsigned int *) &data_021c526c) + 0x2a0);
        }
    }
}

void func_020351ec(void)
{
    unsigned int tmp;
    unsigned int cond;
    unsigned int cond2;

    tmp = data_020e54a8;
    if (tmp == 0) {
        cond = 1;
    } else {
        cond = 0;
    }

    if (cond != 0) {
        func_020368c0((*(unsigned int *) &data_021c526c) + 0x264);
    } else {
        if (tmp == 1) {
            cond2 = 1;
        } else {
            cond2 = 0;
        }

        if (cond2 != 0) {
            func_02036788((*(unsigned int *) &data_021c526c) + 0x2a0);
        }
    }
}

UnkStruct_020351c4 *func_020351c4(void)
{
    int idx = func_02034f44((UnkStruct_02034f44 *) ((*(UnkStruct_020351c4 **) &data_021c526c)));
    UnkStruct_020351c4 *result = 0;
    if (idx >= 0) {
        result = &(*(UnkStruct_020351c4 **) &data_021c526c)[idx];
    }
    return result;
}

void func_02035198(UnkStruct_02035198 *p, int arg1)
{
    int idx = func_02034f78((unsigned char *) p, (int *) arg1);
    if (idx < 0) {
        return;
    }
    func_02034e78((void *) p, idx);
    func_02037470((void *) (p + idx), (void *) arg1);
}

void func_02035170(void *arg0, int key)
{
    int val;
    int val2;
    char val3;

    val = func_02034f14(arg0, key);
    if (val >= 0) {
        val2 = *(int *) ((char *) arg0 + 0x1c0);
        if (val < val2) {
            val3 = 1;
            *(char *) ((char *) arg0 + val * 0x1c + 0x13) = val3;
        }
    }
    return;
}

void func_02035148(Container *param, unsigned short argument1, int flag)
{
    int ret = func_02034ee4((char *) param, (unsigned short) argument1);
    if (ret >= 0 && ret < param->count) {
        param->array[ret].flag = 1;
    }
}

void func_02035104(void *p)
{
    func_020350a4((UnkStruct_020350a4_3 *) p);
    func_02035040(p);
    func_02034fec((UnkStruct_02034fec *) p);
    func_020364c0((char *) p + 0x1c4);
    func_02035f6c((char *) p + 0x2b4);
    func_02035800((char *) p + 0x2f0);
    func_02034fac((Container_02034fac *) p);
}

void func_020350a4(UnkStruct_020350a4_3 *self)
{
    int idx;
    UnkStruct_020350a4 *e;
    UnkStruct_020350a4_2 *r;
    int done;

    idx = func_02034f44((UnkStruct_02034f44 *) self);
    if (idx < 0) {
        return;
    }
    e = &self->arr[idx];
    if (e->unk_04 == 0xffff) {
        return;
    }
    done = 0;
    if (idx > 0) {
        r = (UnkStruct_020350a4_2 *) func_02034ebc((UnkStruct_02034ebc *) self, idx);
        if (r != 0) {
            func_02035fe4(&self->unk_2B4, r->unk_08);
            done = 1;
        }
    }
    if (done == 0) {
        if (e->unk_13 != 0) {
            func_02035fe4(&self->unk_2B4, e->unk_08);
        }
    }
}

void func_02035040(void *self)
{
    int i, j;
    int count;
    int last;

    count = *(int *) ((char *) self + 0x1c0);
    for (i = count - 1; i >= 0; i--) {
        if (*(unsigned char *) ((char *) self + i * 0x1c + 0x13) != 0) {
            last = *(int *) ((char *) self + 0x1c0) - 1;
            for (j = i; j < last; j++) {
                func_02037470((char *) self + j * 0x1c, (char *) self + (j + 1) * 0x1c);
            }
            func_020374ac((char *) self + last * 0x1c);
            *(int *) ((char *) self + 0x1c0) = last;
        }
    }
}

void func_02035038(UnkStruct_02035038 *p)
{
    p->unk_12 = 0;
}

void func_02034fec(UnkStruct_02034fec *self)
{
    if (self->unk_1C0 <= 0) {
        return;
    }
    if (self->unk_12 != 0) {
        return;
    }
    if (self->unk_04 != 0xffff) {
        func_02035fec(&self->unk_2B4, self->unk_04);
        self->unk_14 = 1;
    }
    func_02034e28(self, data_020da26c);
    self->unk_12 = 1;
}

void func_02034fac(Container_02034fac *c)
{
    int n = c->count;
    UnkStruct_02034fac *end = (UnkStruct_02034fac *) ((char *) c + n * sizeof(UnkStruct_02034fac));
    UnkStruct_02034fac *e;

    for (e = (UnkStruct_02034fac *) c; e < end; e++) {
        if (func_02037458(e) != 0) {
            e->flag_0x13 = 1;
        }
        if (e != (UnkStruct_02034fac *) c && e->unk_11 != 0) {
            e->flag_0x13 = 1;
        }
    }
}

int func_02034f78(unsigned char *ptr, int *value)
{
    int i = -1;
    int n = *(int *) (ptr + 0x1c0);
    if (n < 16) {
        for (i = 0; i < n; i++) {
            if (*(int *) (ptr + i * 28) > *value) {
                break;
            }
        }
    }
    return i;
}

int func_02034f44(UnkStruct_02034f44 *p)
{
    int result = -1;
    int i;
    for (i = 0; i < p->count; i++) {
        if (p->arr[i].flag != 0) {
            result = i;
            break;
        }
    }
    return result;
}

int func_02034f14(unsigned char *p, int key)
{
    int r = -1;
    int i;
    int v;
    UnkStruct_02034f14 *arr = (UnkStruct_02034f14 *) p;
    int n = *(int *) (p + 0x1c0);
    for (i = 0; i < n; i++) {
        v = arr[i].key;
        if (v == key) {
            r = i;
            break;
        }
    }
    return r;
}

int func_02034ee4(char *base, unsigned short key)
{
    unsigned short *id;
    int result;
    int i;
    int count;

    result = -1;
    count = *(int *) (base + 0x1c0);
    for (i = 0; i < count; i++) {
        id = (unsigned short *) (base + i * 0x1c + 4);
        if (*id == key) {
            result = i;
            break;
        }
    }
    return result;
}

UnkStruct_02034ebc *func_02034ebc(UnkStruct_02034ebc *array, int count)
{
    UnkStruct_02034ebc *result = 0;
    int i = 0;
    while (i < count) {
        if (array[i].flag == 0) {
            result = &array[i];
            break;
        }
        i++;
    }
    return result;
}

void func_02034e78(void *self, int start)
{
    int count;
    int i;
    int *p;

    count = *(int *) ((char *) self + 0x1c0);
    if (count > 0) {
        i = count - 1;
        while (i >= start) {
            func_02037470((char *) self + 0x1c * (i + 1), (char *) self + 0x1c * i);
            i--;
        }
    }
    p = (int *) ((char *) self + 0x1c0);
    (*p)++;
}
