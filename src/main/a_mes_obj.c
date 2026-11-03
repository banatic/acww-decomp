/* a_mes_obj: 23 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02011d90 @ 0x02011d90, 0x40 bytes, Thumb
 * func_02011d60 @ 0x02011d60, 0x30 bytes, Thumb
 * func_02011d30 @ 0x02011d30, 0x30 bytes, Thumb
 * func_02011d28 @ 0x02011d28, 0x8 bytes, Thumb
 * func_02011cd8 @ 0x02011cd8, 0x50 bytes, Thumb
 * func_02011c88 @ 0x02011c88, 0x50 bytes, Thumb
 * func_02011c28 @ 0x02011c28, 0x60 bytes, Thumb
 * func_02011bc8 @ 0x02011bc8, 0x60 bytes, Thumb
 * func_02011bb0 @ 0x02011bb0, 0x18 bytes, Thumb
 * func_02011b98 @ 0x02011b98, 0x18 bytes, Thumb
 * func_02011b38 @ 0x02011b38, 0x60 bytes, Thumb
 * func_02011af8 @ 0x02011af8, 0x40 bytes, Thumb
 * func_02011a58 @ 0x02011a58, 0xa0 bytes, Thumb
 * func_02011a50 @ 0x02011a50, 0x8 bytes, Thumb
 * func_020119c4 @ 0x020119c4, 0x8c bytes, Thumb
 * func_02011924 @ 0x02011924, 0xa0 bytes, Thumb
 * func_020118a0 @ 0x020118a0, 0x84 bytes, Thumb
 * func_020117f8 @ 0x020117f8, 0xa8 bytes, Thumb
 * func_020117a8 @ 0x020117a8, 0x50 bytes, Thumb
 * func_020117a0 @ 0x020117a0, 0x8 bytes, Thumb
 * func_02011704 @ 0x02011704, 0x9c bytes, Thumb
 * func_020116bc @ 0x020116bc, 0x48 bytes, Thumb
 * func_020116b4 @ 0x020116b4, 0x8 bytes, Thumb
 */

struct UnkStruct_02011d90 {
    char pad_00[0x250];
    int unk_250;
};

struct UnkStruct_02011c28 {
    char pad_00[0x48];
    void *unk_48;
};

struct UnkStruct_02011bc8 {
    char pad_00[0x4c];
    int unk_4C;
};

typedef struct {
    unsigned char pad_00[0x48];
    unsigned char *data;
} UnkStruct_02011b38;

struct Func02011A_F8 {
    unsigned char pad_00[0x4c];
    unsigned int unk_4C;
};

struct UnkStruct_02011a58 {
    char pad_00[0x4c];
    int unk_4C;
};

struct UnkStruct_020119c4 {
    unsigned char pad_00[0x4c];
    char *unk_4C;
};

struct UnkStruct_020118a0 {
    unsigned char pad_00[0x50];
};

struct UnkStruct_020117f8 {
    char pad_00[0x4c];
    int unk_4C;
};

typedef struct {
    unsigned char pad_00[0x4c];
    char *unk_4C;
} UnkStruct_020117a8;

struct UnkStruct_02011704 {
    char pad_00[0x4c];
    int unk_4C;
};

struct Unk020116bc {
    unsigned char pad_00[0x4c];
    void *buf;
};

extern char data_021c1284;
extern void FS_InitFile(void *file);
extern const unsigned char data_020d84b8[];
extern const unsigned char data_020d84d8[];
extern const unsigned char data_020d84f8[];
extern const unsigned char data_020d8518[];
extern int func_02011ed4(void);
extern const unsigned char data_020d843c[];
extern const unsigned char data_020d845c[];
extern const unsigned char data_020d847c[];
extern const unsigned char data_020d849c[];
extern int FS_OpenFile(void *p, int val);
extern int FS_CloseFile(void *p);
extern int func_020e98d4(int);
extern int FS_ReadFile(void *, int, int);
extern void func_020e9898(int);
extern void GX_LoadOBJPltt(unsigned char *p, int a, int b);
extern void GXS_LoadOBJPltt(unsigned char *p, int a, int b);
extern int FS_SeekFile(void *self, int ptr, int a3);
extern void DC_FlushRange(void *, unsigned int);
extern void GX_LoadOBJ(void *, const void *, unsigned int);
extern void GXS_LoadOBJ(void *, const void *, unsigned int);
extern int data_020c8098;
extern int data_020d8428[];

void func_02011d28(void *file);
int func_02011924(void *self, int count);
void func_020118a0(struct UnkStruct_020118a0 *self, int mode);
int func_020117f8(struct UnkStruct_020117f8 *self, int count);
void func_020117a8(UnkStruct_020117a8 *self);
void func_020117a0(void *argument0);
int func_02011704(struct UnkStruct_02011704 *self, int count);
void func_020116bc(struct Unk020116bc *self);
void func_020116b4(void *argument0);

void func_02011d90(struct UnkStruct_02011d90 *p0, int p1, int p2, int p3)
{
    int res;
    func_02011d28((void *) (((int *) &data_021c1284)));
    res = func_02011924((void *) (((int *) &data_021c1284)), p1);
    if (p2 != 0) {
        p0->unk_250 = p3;
    } else if (res != 0) {
        func_020118a0((struct UnkStruct_020118a0 *) (((int *) &data_021c1284)), p3);
    }
}

void func_02011d60(void *param1, void *param2)
{
    void *ptr = &data_021c1284;
    func_02011d28(ptr);
    if (func_020117f8((struct UnkStruct_020117f8 *) (&data_021c1284), (int) param2)) {
        func_020117a8((UnkStruct_020117a8 *) ptr);
    }
    func_020117a0(param1);
}

void func_02011d30(void *param1, void *param2)
{
    void *p = &data_021c1284;

    func_02011d28(p);
    if (func_02011704((struct UnkStruct_02011704 *) (&data_021c1284), (int) param2) != 0) {
        func_020116bc((struct Unk020116bc *) p);
    }
    func_020116b4(param1);
}

void func_02011d28(void *file)
{
    FS_InitFile(file);
}

const unsigned char *func_02011cd8(const unsigned char *p, int n)
{
    const unsigned char *a;
    const unsigned char *b;
    const unsigned char *c;
    const unsigned char *d;
    const unsigned char *result;

    if (n >= 4) {
        n = func_02011ed4();
    }

    a = data_020d84b8;
    b = data_020d84d8;
    c = data_020d84f8;
    d = data_020d8518;
    result = d;

    if (n == 2) {
        result = b;
    } else if (n == 3) {
        result = a;
    } else if (p[0x255] != 0) {
        result = c;
    }

    return result;
}

const unsigned char *func_02011c88(const unsigned char *p, int n)
{
    const unsigned char *a;
    const unsigned char *b;
    const unsigned char *c;
    const unsigned char *d;
    const unsigned char *result;

    if (n >= 4) {
        n = func_02011ed4();
    }

    a = data_020d843c;
    b = data_020d845c;
    c = data_020d847c;
    d = data_020d849c;
    result = d;

    if (n == 2) {
        result = b;
    } else if (n == 3) {
        result = a;
    } else if (p[0x255] != 0) {
        result = c;
    }

    return result;
}

int func_02011c28(struct UnkStruct_02011c28 *p, int flag)
{
    int ret;
    int last;

    ret = FS_OpenFile(p, (int) func_02011cd8((const unsigned char *) p, flag));
    p->unk_48 = (void *) func_020e98d4(0x180);

    if (p->unk_48 != 0) {
        flag = (FS_ReadFile(p, (int) p->unk_48, 0x180) != -1);
    } else {
        flag = 0;
    }

    last = FS_CloseFile(p);

    if (ret && flag && last && p->unk_48 != 0) {
        return 1;
    } else {
        return 0;
    }
}

int func_02011bc8(struct UnkStruct_02011bc8 *self)
{
    int b, flag, d;
    b = FS_OpenFile(self, (int) func_02011c88((const unsigned char *) self, 4));
    self->unk_4C = func_020e98d4(0x3000);
    if (self->unk_4C != 0) {
        flag = FS_ReadFile(self, self->unk_4C, 0x3000) != -1;
    } else {
        flag = 0;
    }
    d = FS_CloseFile(self);
    if (b != 0 && flag != 0 && d != 0 && self->unk_4C != 0) {
        return 1;
    } else {
        return 0;
    }
}

void func_02011bb0(void *arg0)
{
    int condition_value0;
    void *r4 = arg0;
    if ((condition_value0 = (int) (*(unsigned int *) ((char *) r4 + 0x48))) != 0) {
        func_020e9898(condition_value0);
        *(unsigned int *) ((char *) r4 + 0x48) = 0;
    }
}

void func_02011b98(void *arg0)
{
    int condition_value0;
    if ((condition_value0 = (int) (*(unsigned int *) ((char *) arg0 + 0x4c))) != 0) {
        func_020e9898(condition_value0);
        *(unsigned int *) ((char *) arg0 + 0x4c) = 0;
    }
}

void func_02011b38(UnkStruct_02011b38 *s, unsigned int mode)
{
    unsigned char *p;
    unsigned char *q;
    DC_FlushRange((void *) s->data, 0x180);
    p = s->data;
    q = p + 0x160;
    if (mode <= 1) {
        GX_LoadOBJPltt(p, 0x80, 0x100);
        GX_LoadOBJPltt(q, 0x1e0, 0x20);
    }
    if (mode == 0 || mode == 2) {
        GXS_LoadOBJPltt(p, 0x80, 0x100);
        GXS_LoadOBJPltt(q, 0x1e0, 0x20);
    }
}

void func_02011af8(struct Func02011A_F8 *p, unsigned int a)
{
    DC_FlushRange((void *) p->unk_4C, 0x3000);
    if (a <= 1) {
        GX_LoadOBJ((void *) p->unk_4C, (const void *) 0x1000, 0x3000);
    }
    if (a == 0 || a == 2) {
        GXS_LoadOBJ((void *) p->unk_4C, (const void *) 0x1000, 0x3000);
    }
}

int func_02011a58(struct UnkStruct_02011a58 *self, int a)
{
    int id;
    int b;
    int flag;
    int local8 = 0, local4 = 0, localC = 0, local10 = 0;
    int ptr;
    unsigned int i;
    int d;

    id = (int) func_02011c88((const unsigned char *) self, a);
    b = FS_OpenFile(self, id);
    self->unk_4C = func_020e98d4(0x500);

    flag = 1;
    if (self->unk_4C != 0) {
        ptr = 0;
        i = 0;
        goto loop_test;

    loop_body:
        if (FS_SeekFile(self, ptr, local4) == 0) {
            flag = local8;
        }
        if (FS_ReadFile(self, self->unk_4C + i * 0x280, 0x280) == ~local10) {
            flag = localC;
        }
        i++;
        ptr = ptr + 0x400;

    loop_test:
        if (i < 2) {
            goto loop_body;
        }
    }

    d = FS_CloseFile(self);

    return (b != 0 && flag != 0 && d != 0 && self->unk_4C != 0) ? 1 : 0;
}

void func_02011a50(void *argument0)
{
    func_02011b98((void *) argument0);
}

void func_020119c4(struct UnkStruct_020119c4 *self, int mode)
{
    char *src;
    int all, doA, doB;
    char *dst;
    unsigned int i;

    DC_FlushRange(self->unk_4C, 0x500);

    all = (mode == 0);
    if (all || mode == 1) {
        doA = 1;
    } else {
        doA = 0;
    }
    if (all || mode == 2) {
        doB = 1;
    } else {
        doB = 0;
    }

    src = (char *) 0x1000;
    i = 0;
    goto loop_test;

loop_body:
    dst = self->unk_4C + i * 0x280;
    if (doA) {
        GX_LoadOBJ(dst, src, 0x280);
    }
    if (doB) {
        GXS_LoadOBJ(dst, src, 0x280);
    }
    i++;
    src += 0x400;

loop_test:
    if (i < 2) {
        goto loop_body;
    }
}

int func_02011924(void *self, int count)
{
    int id;
    int b;
    int flag;
    int local8 = 0, local4 = 0, localC = 0, local10 = 0;
    int ptr;
    unsigned int i;
    int d;

    if (count != 0) {
        id = (int) &data_020c8098;
    } else {
        id = (int) func_02011c88((const unsigned char *) self, 2);
    }

    b = FS_OpenFile(self, id);

    flag = 1;
    if (count != 0) {
        ptr = 0;
    } else {
        ptr = 0x180;
    }
    i = 0;
    goto loop_test;

loop_body:
    if (FS_SeekFile(self, ptr, local4) == 0) {
        flag = local8;
    }
    if (FS_ReadFile(self, (int) ((char *) self + 0x50 + (i << 8)), 0x100) == ~local10) {
        flag = localC;
    }
    i++;
    ptr = ptr + 0x400;

loop_test:
    if (i < 2) {
        goto loop_body;
    }

    d = FS_CloseFile(self);

    return (b != 0 && flag != 0 && d != 0) ? 1 : 0;
}

void func_020118a0(struct UnkStruct_020118a0 *self, int mode)
{
    char *src;
    char *dst;
    unsigned int i;
    int all, doB, doA;

    DC_FlushRange((char *) self + 0x50, 0x200);

    all = (mode == 0);
    if (all || mode == 1) {
        doA = 1;
    } else {
        doA = 0;
    }
    if (all || mode == 2) {
        doB = 1;
    } else {
        doB = 0;
    }

    src = (char *) 0x1180;
    i = 0;
    goto loop_test;

loop_body:
    dst = (char *) self + 0x50 + (i << 8);
    if (doA) {
        GX_LoadOBJ(dst, src, 0x100);
    }
    if (doB) {
        GXS_LoadOBJ(dst, src, 0x100);
    }
    i++;
    src += 0x400;

loop_test:
    if (i < 2) {
        goto loop_body;
    }
}

int func_020117f8(struct UnkStruct_020117f8 *self, int count)
{
    int id;
    int b;
    int flag;
    int local8 = 0, local4 = 0, localC = 0, local10 = 0;
    int ptr;
    unsigned int i;
    int d;

    if (count != 0) {
        id = (int) &data_020c8098;
    } else {
        id = (int) func_02011c88((const unsigned char *) self, 4);
    }

    b = FS_OpenFile(self, id);
    self->unk_4C = func_020e98d4(0x200);

    flag = 1;
    if (count != 0) {
        ptr = 0x200;
    } else {
        ptr = 0x2300;
    }
    i = 0;
    goto loop_test;

loop_body:
    if (FS_SeekFile(self, ptr, local4) == 0) {
        flag = local8;
    }
    if (FS_ReadFile(self, self->unk_4C + (i << 8), 0x100) == ~local10) {
        flag = localC;
    }
    i++;
    ptr = ptr + 0x400;

loop_test:
    if (i < 2) {
        goto loop_body;
    }

    d = FS_CloseFile(self);

    return (b != 0 && flag != 0 && d != 0) ? 1 : 0;
}

void func_020117a8(UnkStruct_020117a8 *self)
{
    unsigned int offset;
    unsigned int i;

    DC_FlushRange(self->unk_4C, 0x200);
    offset = 0x3300;
    i = 0;
    goto check;
loop: {
    char *src = self->unk_4C + (i << 8);
    GX_LoadOBJ((void *) src, (const void *) offset, 0x100);
    GXS_LoadOBJ((void *) src, (const void *) offset, 0x100);
}
    i++;
    offset += 0x400;
check:
    if (i < 2) {
        goto loop;
    }
}

void func_020117a0(void *argument0)
{
    func_02011b98((void *) argument0);
}

int func_02011704(struct UnkStruct_02011704 *self, int count)
{
    int id;
    int b;
    int flag;
    int local8 = 0, local4 = 0, localC = 0, local10 = 0;
    int ptr;
    unsigned int i;
    int d;

    if (count == 0) {
        id = (int) func_02011c88((const unsigned char *) self, 1);
    } else {
        id = (int) &data_020c8098;
    }

    b = FS_OpenFile(self, id);
    self->unk_4C = func_020e98d4(0x80);

    flag = 1;
    ptr = data_020d8428[count];
    i = 0;
    goto loop_test;

loop_body:
    if (FS_SeekFile(self, ptr, local4) == 0) {
        flag = local8;
    }
    if (FS_ReadFile(self, self->unk_4C + (i << 6), 0x40) == ~local10) {
        flag = localC;
    }
    i++;
    ptr = ptr + 0x400;

loop_test:
    if (i < 2) {
        goto loop_body;
    }

    d = FS_CloseFile(self);

    return (b != 0 && flag != 0 && d != 0) ? 1 : 0;
}

void func_020116bc(struct Unk020116bc *self)
{
    char *src;
    unsigned int i;
    char *dst;

    DC_FlushRange(self->buf, 0x80);
    src = (char *) 0x38c0;
    i = 0;
    goto loop_test;

loop_body:
    dst = (char *) self->buf + (i << 6);
    GX_LoadOBJ(dst, src, 0x40);
    GXS_LoadOBJ(dst, src, 0x40);
    i++;
    src += 0x400;

loop_test:
    if (i < 2) {
        goto loop_body;
    }
}

void func_020116b4(void *argument0)
{
    func_02011b98((void *) argument0);
}
