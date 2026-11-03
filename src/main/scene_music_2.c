/* scene_music_2: 11 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02036870 @ 0x02036870, 0x24 bytes, Thumb
 * func_02036864 @ 0x02036864, 0xc bytes, Thumb
 * func_0203684c @ 0x0203684c, 0x18 bytes, Thumb
 * func_02036830 @ 0x02036830, 0x1c bytes, Thumb
 * func_02036828 @ 0x02036828, 0x8 bytes, Thumb
 * func_0203680c @ 0x0203680c, 0x1a bytes, Thumb
 * func_020367ec @ 0x020367ec, 0x1e bytes, Thumb
 * func_020367e4 @ 0x020367e4, 0x6 bytes, Thumb
 * func_020367cc @ 0x020367cc, 0x18 bytes, Thumb
 * func_02036788 @ 0x02036788, 0x42 bytes, Thumb
 * func_02036784 @ 0x02036784, 0x4 bytes, Thumb
 */

#include "types.h"

typedef struct {
    void *unk_00;
    int unk_04;
    unsigned char unk_08;
    unsigned short unk_0A;
    unsigned char unk_0C;
    unsigned char unk_0D;
    unsigned char unk_0E;
    unsigned char unk_0F;
    unsigned char unk_10;
} UnkStruct_02036870;

typedef struct {
    void *vtable;
} UnkStruct_0203684c;

struct Object {
    unsigned char pad_00[0xF];
    unsigned char flag;
};

typedef struct {
    unsigned char pad_00[14];
    unsigned char unk_0E;
} UnkStruct_020367e4;

struct UnkStruct_020367cc {
    unsigned char pad_00[0xF];
    unsigned char flag;
};

typedef struct UnkStruct_02036788 UnkStruct_02036788;

struct UnkStruct_02036788 {
    u8 pad_00[8];
    u8 unk_08;
    u8 pad_09[4];
    u8 unk_0D;
    u8 unk_0E;
    u8 unk_0F;
    u8 unk_10;
};

extern unsigned char data_020da2f4[];
extern void func_020edb3c(UnkStruct_0203684c *);
extern void func_0203668c(struct Object *obj);
extern void func_02036584(struct Object *obj);
extern void func_020366c0(void *param1);
extern void func_0203665c(void *param1);
extern int func_02035ae8(void);
extern int func_02035bdc(int);

void func_020367ec(void *param1);

void func_02036870(UnkStruct_02036870 *obj, int value)
{
    obj->unk_00 = &data_020da2f4;
    obj->unk_04 = value;
    obj->unk_08 = 0x3f;
    obj->unk_0A = 0xffff;
    obj->unk_0C = 0;
    obj->unk_0D = 0;
    obj->unk_0E = 0;
    obj->unk_0F = 0;
    obj->unk_10 = 0;
}

void func_02036864(void **p)
{
    *p = (void *) data_020da2f4;
}

UnkStruct_0203684c *func_0203684c(UnkStruct_0203684c *self)
{
    self->vtable = ((char *) data_020da2f4);
    func_020edb3c(self);
    return self;
}

void func_02036830(void *param)
{
    unsigned char *p = (unsigned char *) param;
    unsigned short *s = (unsigned short *) ((unsigned char *) param + 0xa);

    p[8] = 0x3f;
    *s = 0xffff;
    p[0xc] = 0;
    p[0xd] = 0;
    p[0xe] = 0;
    p[0xf] = 0;
    p[0x10] = 0;
}

void func_02036828(void *argument0)
{
    func_020367ec((void *) argument0);
}

void func_0203680c(struct Object *obj)
{
    if (obj->flag) {
        func_0203668c(obj);
        func_02036584(obj);
    }
}

void func_020367ec(void *param1)
{
    void *r4 = param1;
    func_020366c0(r4);
    *(unsigned char *) ((char *) r4 + 8) = 0x3f;
    func_0203665c(r4);
    *(unsigned char *) ((char *) r4 + 0x10) = 0;
    *(unsigned char *) ((char *) r4 + 0xf) = 0;
}

void func_020367e4(UnkStruct_020367e4 *p)
{
    p->unk_0E = 1;
}

void func_020367cc(struct UnkStruct_020367cc *obj)
{
    obj->flag = 1;
    func_0203668c((struct Object *) obj);
    func_02036584((struct Object *) obj);
}

void func_02036788(UnkStruct_02036788 *s)
{
    int flag;

    if (s->unk_10 != 0) {
        goto end;
    }
    if (s->unk_0D != 0 && func_02035bdc(func_02035ae8()) != 0) {
        flag = 1;
    } else {
        flag = 0;
    }
    func_020366c0((void *) s);
    s->unk_08 = 0x3f;
    func_0203665c((void *) s);
    s->unk_0E = flag;
end:
    s->unk_0F = 0;
}

void func_02036784(unsigned char *p0, int p1)
{
    p0[16] = p1;
}
