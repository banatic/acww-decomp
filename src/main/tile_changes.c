/* tile_changes: 19 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02045f08 @ 0x02045f08, 0x1c bytes, Thumb
 * func_02045eec @ 0x02045eec, 0x1c bytes, Thumb
 * func_02045ea8 @ 0x02045ea8, 0x44 bytes, Thumb
 * func_02045e24 @ 0x02045e24, 0x84 bytes, Thumb
 * func_02045df8 @ 0x02045df8, 0x2c bytes, Thumb
 * func_02045db8 @ 0x02045db8, 0x40 bytes, Thumb
 * func_02045d98 @ 0x02045d98, 0x20 bytes, Thumb
 * func_02045d80 @ 0x02045d80, 0x18 bytes, Thumb
 * func_02045d74 @ 0x02045d74, 0xc bytes, Thumb
 * func_02045d44 @ 0x02045d44, 0x30 bytes, Thumb
 * func_02045cec @ 0x02045cec, 0x58 bytes, Thumb
 * func_02045c84 @ 0x02045c84, 0x68 bytes, Thumb
 * func_02045c60 @ 0x02045c60, 0x24 bytes, Thumb
 * func_02045c48 @ 0x02045c48, 0x18 bytes, Thumb
 * func_02045c08 @ 0x02045c08, 0x40 bytes, Thumb
 * func_02045bb8 @ 0x02045bb8, 0x50 bytes, Thumb
 * func_02045bac @ 0x02045bac, 0xc bytes, Thumb
 * func_02045b5c @ 0x02045b5c, 0x50 bytes, Thumb
 * func_02045b3c @ 0x02045b3c, 0x1e bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
} Pair;

typedef struct {
    int unk_00, unk_04, unk_08, unk_0C;
} UnkStruct_02045eec;

struct Copy {
    u32 a;
    u32 b;
};

struct Entry {
    unsigned char low : 3;
    unsigned char : 5;
    unsigned char pad_01[15];
};

struct Pt {
    int x;
    int z;
};

struct UnkStruct_02045e24 {
    int x;
    int y;
};

struct Entry_02045e24 {
    u8 b0 : 3;
    u8 code : 5;
    u8 pad_01[7];
    u16 unk_08;
    u8 pad_0A[6];
};

struct UnkStruct_02045df8 {
    int m[4];
};

struct Header {
    unsigned char code : 3;
};

struct Entry_02045db8 {
    unsigned char b0 : 3;
    unsigned char : 5;
    unsigned char : 7;
    unsigned char b1 : 1;
    unsigned char pad_02[14];
};

struct UnkStruct_02045d98 {
    char data[16];
};

typedef struct {
    unsigned char pad_00[2];
    unsigned char b0 : 1;
    unsigned char b1 : 1;
    unsigned char b2 : 6;
    unsigned char pad_03[5];
    unsigned short unk_08;
    unsigned char pad_0A[6];
} UnkStruct_02045cec;

typedef struct {
    int unk_00;
    int unk_04;
} Key;

typedef struct {
    unsigned char a : 3;
    unsigned char : 5;
    unsigned char pad_01;
    unsigned char b0 : 1;
    unsigned char b1 : 1;
    unsigned char b2 : 6;
    unsigned char pad_03[5];
    unsigned short unk_08;
    unsigned char pad_0A[6];
} UnkStruct_02045c84;

typedef struct {
    int unk_00;
    int unk_04;
} Pair_02045c84;

struct Pair {
    unsigned int a;
    unsigned int b;
};

typedef struct {
    unsigned char a : 3;
    unsigned char : 5;
    unsigned char b : 7;
    unsigned char c : 1;
    unsigned char pad_02[14];
} UnkStruct_02045c08;

struct entry_02045bb8 {
    unsigned char a : 3;
    unsigned char : 5;
    unsigned char : 2;
    unsigned char b : 3;
    unsigned char pad_02[14];
};

struct Entry_02045b5c {
    unsigned char type : 3;
    unsigned char : 5;
    unsigned char : 7;
    unsigned char flag : 1;
    unsigned char pad_02[6];
    unsigned char data[8];
};

extern void func_0204629c(void *ptr);
extern UnkStruct_02045eec data_021c7884[];
extern int func_ov003_02221340(int idx, struct UnkStruct_02045e24 *key);
extern struct Entry_02045db8;
extern void func_0204622c(void *);
extern void func_020465b0(struct UnkStruct_02045d98 *p);
extern int data_021c7880;
extern void func_020461e0(char *ptr);
extern unsigned int func_02044858(unsigned int);
extern int func_02073d90(int);
extern int data_020ccf94;
extern void func_02046224(char *);

void func_02045eec(int index);
void func_02045db8(struct Header *h);
int func_02045cec(Key *k, int flag);
int func_02045c08(int key);
int func_02045bac(int index);

void func_02045f08(Pair *src, int arg)
{
    Pair local;

    local.unk_00 = src->unk_00;
    local.unk_04 = src->unk_04;
    func_02045eec((int) func_02045cec((Key *) (&local), arg));
}

void func_02045eec(int index)
{
    if (index >= 0) {
        func_0204629c(&data_021c7884[index]);
    }
}

void func_02045ea8(const struct Copy *src, int mask, int param)
{
    struct Copy local;
    int res;

    local.a = src->a;
    local.b = src->b;
    res = func_02045cec((Key *) (&local), param);
    if (res < 0) {
        return;
    }
    if ((unsigned char) (mask & 3) == ((struct Entry *) data_021c7884)[res].low) {
        func_0204629c((void *) (&((struct Entry *) data_021c7884)[res]));
    }
}

void func_02045e24(struct Pt *pt, int flag)
{
    volatile u16 a;
    volatile u16 b;
    volatile u16 w;
    u16 v;
    struct Pt local;
    struct UnkStruct_02045e24 pair;
    int res;

    local.x = pt->x;
    local.z = pt->z;
    res = func_02045cec((Key *) (&local), flag);
    if (res < 0) {
        return;
    }
    {
        struct Entry_02045e24 *e = &((struct Entry_02045e24 *) data_021c7884)[res];
        w = e->unk_08;
        v = w;
        b = v;
        a = v;
        pair.x = a >> 8;
        pair.y = b & 0xff;
        if (func_ov003_02221340(e->b0, &pair) != 0) {
            return;
        }
        switch (e->code) {
            case 4:
            case 10:
            case 22:
            case 25:
                func_02045db8((struct Header *) e);
                break;
            default:
                func_0204629c(e);
                break;
        }
    }
}

void func_02045df8(int *src, int a)
{
    int tmp[2];
    int r;

    tmp[0] = src[0];
    tmp[1] = src[1];
    r = func_02045cec((Key *) tmp, a);
    if (r >= 0) {
        func_02045db8((struct Header *) (&((struct UnkStruct_02045df8 *) data_021c7884)[r]));
    }
}

void func_02045db8(struct Header *h)
{
    struct Entry_02045db8 *p;
    int i;

    p = ((struct Entry_02045db8 *) data_021c7884);
    i = 0;
    do {
        if (p->b0 == h->code && p->b1) {
            p->b1 = 0;
        }
        p++;
        i++;
    } while (i < 20);

    func_0204622c(h);
}

void func_02045d98(int key)
{
    int idx = func_02045c08(key);
    if (idx >= 0) {
        func_020465b0(&((struct UnkStruct_02045d98 *) data_021c7884)[idx]);
    }
}

int func_02045d80(Pair *src, int arg)
{
    Pair local;

    local.unk_00 = src->unk_00;
    local.unk_04 = src->unk_04;
    return func_02045cec((Key *) (&local), arg);
}

void func_02045d74(void)
{
    data_021c7880 = 1;
}

void func_02045d44(void)
{
    char *p;
    int i;
    p = (char *) func_02045bac(0);
    for (i = 0; i < 20; i++) {
        func_020461e0(p);
        p += 16;
    }
    data_021c7880 = 0;
}

int func_02045cec(Key *k, int flag)
{
    UnkStruct_02045cec *e;
    int i;
    int res;
    volatile unsigned short a;
    volatile unsigned short b;
    volatile unsigned short w;
    unsigned short v;

    res = -1;
    e = ((UnkStruct_02045cec *) data_021c7884);
    for (i = 0; i < 0x14; e++, i++) {
        w = e->unk_08;
        v = w;
        a = v;
        if (k->unk_00 != (a >> 8)) {
            continue;
        }
        b = v;
        if (k->unk_04 != (b & 0xff)) {
            continue;
        }
        if (flag != e->b1) {
            continue;
        }
        res = i;
        break;
    }
    return res;
}

// Twin of func_02045cec with an extra check on the low three bits of byte 0.
int func_02045c84(unsigned int p0, Pair_02045c84 *p1, unsigned int p2)
{
    UnkStruct_02045c84 *e;
    int i;
    int res;
    volatile unsigned short a;
    volatile unsigned short b;
    volatile unsigned short w;
    unsigned short v;

    i = 0;
    res = -1;
    e = ((UnkStruct_02045c84 *) data_021c7884);
    for (; i < 0x14; e++, i++) {
        if (p0 != e->a) {
            continue;
        }
        w = e->unk_08;
        v = w;
        a = v;
        if (p1->unk_00 != (a >> 8)) {
            continue;
        }
        b = v;
        if (p1->unk_04 != (b & 0xff)) {
            continue;
        }
        if (p2 != e->b1) {
            continue;
        }
        res = i;
        break;
    }
    return res;
}

int func_02045c60(unsigned int p0, struct Pair *p1, unsigned int p2)
{
    struct Pair tmp;
    unsigned int d;

    d = func_02044858(p0);
    tmp.a = p1->a;
    tmp.b = p1->b;
    return func_02045c84(d, (Pair_02045c84 *) (&tmp), p2);
}

int func_02045c48(void)
{
    int buffer[3];
    buffer[0] = 0xff;
    buffer[1] = 0xff;
    return func_02045cec((Key *) buffer, 0);
}

int func_02045c08(int key)
{
    UnkStruct_02045c08 *e;
    int i;
    int r;
    i = 0;
    r = -1;
    key = (unsigned char) (key & 3);
    e = ((UnkStruct_02045c08 *) data_021c7884);
    for (; i < 0x14; i++) {
        if (key == e->a && e->c != 0) {
            r = i;
            break;
        }
        e++;
    }
    return r;
}

int func_02045bb8(int a, int b)
{
    struct entry_02045bb8 *p;
    int i;
    int result;

    result = -1;
    if (func_02073d90(data_020ccf94) == 0) {
        a = 0;
    }

    p = ((struct entry_02045bb8 *) data_021c7884);
    for (i = 0; i < 20; p++, i++) {
        if (a == p->a && b == p->b) {
            result = i;
            break;
        }
    }
    return result;
}

int func_02045bac(int index)
{
    return (int) (((char *) data_021c7884) + (index << 4));
}

void *func_02045b5c(int id)
{
    struct Entry_02045b5c *p;
    int i;
    void *result = 0;
    if (func_02073d90((int) ((*(void **) &data_020ccf94))) == 0) {
        id = 0;
    }
    p = ((struct Entry_02045b5c *) data_021c7884);
    for (i = 0; i < 20; i++) {
        if ((id == p->type) && p->flag) {
            result = (void *) p->data;
            break;
        }
        p++;
    }

    return result;
}

void func_02045b3c(char *arg)
{
    char *p;
    int i;

    p = arg + 4;
    for (i = 0; i < 20; i++) {
        func_02046224(p);
        p += 16;
    }
}
