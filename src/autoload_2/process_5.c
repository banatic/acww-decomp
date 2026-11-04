/* process_5: 5 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020ee660 @ 0x020ee660, 0x144 bytes, ARM
 * func_020ee63c @ 0x020ee63c, 0x24 bytes, ARM
 * func_020ee62c @ 0x020ee62c, 0x10 bytes, ARM
 * func_020ee624 @ 0x020ee624, 0x8 bytes, ARM
 * func_020ee61c @ 0x020ee61c, 0x8 bytes, ARM
 */

typedef struct Entry Entry;

struct Entry {
    unsigned int pad_00;
    unsigned short unk_04;
    unsigned short unk_06;
};

typedef struct {
    unsigned int a;
    unsigned int b;
    void *owner;
    unsigned short value;
    unsigned short limit;
} Group;

typedef struct UnkStruct_020ee660 UnkStruct_020ee660;

struct UnkStruct_020ee660 {
    void *vtbl;              // 0x00
    int unk_04;              // 0x04
    unsigned int unk_08;     // 0x08
    unsigned short unk_0C;   // 0x0c
    unsigned char pad_0E[4]; // 0x0e - 0x11
    unsigned char unk_12;    // 0x12
    unsigned char flags;     // 0x13
    unsigned char sub[0x10]; // 0x14 - 0x23
    void *unk_24;
    Group first;
    Group second;
};

extern char data_0213e7b4;
extern unsigned int data_0213e778;
extern unsigned int data_021fcff0;
extern unsigned short data_021fcfe0;
extern unsigned char data_021fcfd8;
extern void *data_021fcfe4;
extern void *data_021fcff8;
extern Entry **data_021fd044;
extern void *func_020e8ec0(void *);
extern int func_020e8e34(void *, void *, void *);
extern UnkStruct_020ee660 *func_020ee45c(UnkStruct_020ee660 *);
extern void func_020edf54(void *self);

UnkStruct_020ee660 *func_020ee660(UnkStruct_020ee660 *self)
{
    Group *p;
    Group *q;
    unsigned short v4, v6;
    Entry *ent;
    UnkStruct_020ee660 *other;

    self->vtbl = &data_0213e7b4;
    func_020e8ec0(&self->sub);

    self->unk_24 = self;
    self->first.a = 0;
    self->first.b = 0;
    self->first.owner = self;
    self->first.value = 0;
    self->first.limit = 0;
    self->second.a = 0;
    self->second.b = 0;
    self->second.owner = self;
    self->second.value = 0;
    self->second.limit = 0;

    self->unk_04 = data_0213e778;
    data_0213e778++;
    self->unk_08 = data_021fcff0;
    self->unk_0C = data_021fcfe0;
    self->unk_12 = data_021fcfd8;

    func_020e8e34(&data_021fcff8, &self->sub, data_021fcfe4);

    ent = data_021fd044[self->unk_0C];

    v4 = ent->unk_04;
    p = &self->first;
    p->value = v4;
    p->limit = v4;

    v6 = ent->unk_06;
    q = &self->second;
    q->value = v6;
    q->limit = v6;

    other = func_020ee45c(self);
    if (other != 0) {
        if ((other->flags & 1) || (other->flags & 2)) {
            self->flags |= 2;
        }
        if ((other->flags & 4) || (other->flags & 8)) {
            self->flags |= 8;
        }
    }

    return self;
}

void *func_020ee63c(void *self)
{
    *(void **) self = (void *) ((unsigned char *) &data_0213e7b4);
    func_020edf54(self);
    return self;
}

void func_020ee62c(int **p)
{
    *p = ((int *) &data_0213e7b4);
}

int func_020ee624(void *object)
{
    return 1;
}

int func_020ee61c(void)
{
    return 1;
}
