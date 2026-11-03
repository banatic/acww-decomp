/* message_walker_4: 14 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a9524 @ 0x020a9524, 0xa bytes, Thumb
 * func_020a9520 @ 0x020a9520, 0x2 bytes, Thumb
 * func_020a9508 @ 0x020a9508, 0x16 bytes, Thumb
 * func_020a94d8 @ 0x020a94d8, 0x30 bytes, Thumb
 * func_020a94c8 @ 0x020a94c8, 0x10 bytes, Thumb
 * func_020a94a4 @ 0x020a94a4, 0x22 bytes, Thumb
 * func_020a9484 @ 0x020a9484, 0x20 bytes, Thumb
 * func_020a9464 @ 0x020a9464, 0x20 bytes, Thumb
 * func_020a943c @ 0x020a943c, 0x28 bytes, Thumb
 * func_020a941c @ 0x020a941c, 0x20 bytes, Thumb
 * func_020a9418 @ 0x020a9418, 0x2 bytes, Thumb
 * func_020a9414 @ 0x020a9414, 0x2 bytes, Thumb
 * func_020a9410 @ 0x020a9410, 0x2 bytes, Thumb
 * func_020a940c @ 0x020a940c, 0x2 bytes, Thumb
 */

struct UnkStruct_020a94d8 {
    int a;
    int b;
    int c;
};

struct Unk020a94c8 {
    void *unk_00;
    int unk_04;
    int unk_08;
};

typedef struct {
    int pad_00;
    int unk_04;
    void *unk_08;
} UnkStruct_020a94a4;

typedef struct {
    char *data;
    int value;
    char sub;
} UnkStruct_020a9484;

struct UnkStruct_020a9464 {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
};

struct UnkStruct_020a943c {
    void *unk_00;
    char unk_04[4];
    char unk_08[4];
};

extern int func_020a92d8(int a, int b);
extern void func_020a9354(void *param, int);
extern int func_020a9c9c(void *p);
extern void func_020a9ccc(void *p);
extern void func_020a9c84(void *);
extern void func_020a9c98(void *);
extern unsigned char data_020e3e24[];
extern void func_020edb3c(struct UnkStruct_020a943c *obj);

void func_020a94a4(UnkStruct_020a94a4 *s);

void func_020a9524(int *p, int a)
{
    p[0] = a;
    p[1] = 0;
    p[2] = 0;
}

void func_020a9520(void *receiver) {}

void func_020a9508(void *r4)
{
    func_020a94a4((UnkStruct_020a94a4 *) (*(void **) r4));
    *(int *) ((char *) r4 + 4) = 0;
    *(int *) ((char *) r4 + 8) = 0;
}

int func_020a94d8(struct UnkStruct_020a94d8 *p)
{
    int result = 0;
    if (p->b != 0) {
        p->c = func_020a92d8(p->a, result);
        if (p->c != 0) {
            result = 1;
        } else {
            p->b = result;
        }
    }
    return result;
}

void func_020a94c8(struct Unk020a94c8 *obj, int value)
{
    obj->unk_04 = value;
    obj->unk_08 = value;
    func_020a9354(obj->unk_00, value);
}

void func_020a94a4(UnkStruct_020a94a4 *s)
{
    s->unk_04 = 0;
    while (func_020a9c9c((void *) &s->unk_08) == 0) {
        func_020a9ccc((void *) &s->unk_08);
    }
}

UnkStruct_020a9484 *func_020a9484(UnkStruct_020a9484 *self)
{
    self->data = ((char *) data_020e3e24);
    self->value = 0;
    func_020a9c84(&self->sub);
    return self;
}

struct UnkStruct_020a9464 *func_020a9464(struct UnkStruct_020a9464 *self)
{
    self->unk_00 = (unsigned int) data_020e3e24;
    func_020a94a4((UnkStruct_020a94a4 *) self);
    func_020a9c98(&self->unk_08);
    return self;
}

struct UnkStruct_020a943c *func_020a943c(struct UnkStruct_020a943c *obj)
{
    obj->unk_00 = ((int *) data_020e3e24);
    func_020a94a4((UnkStruct_020a94a4 *) obj);
    func_020a9c98(obj->unk_08);
    func_020edb3c(obj);
    return obj;
}

void *func_020a941c(void *p)
{
    *(void **) p = (void *) ((int *) data_020e3e24);
    func_020a94a4((UnkStruct_020a94a4 *) p);
    func_020a9c98((char *) p + 8);
    return p;
}

void func_020a9418(void) {}

void func_020a9414(void) {}

void func_020a9410(void) {}

void func_020a940c(void) {}
