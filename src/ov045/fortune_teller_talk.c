/* fortune_teller_talk: 10 functions, module ov045
 * mwccarm 1.2/base -O4,s
 * func_ov045_0226050c @ 0x0226050c, 0x18 bytes, Thumb
 * func_ov045_022604f4 @ 0x022604f4, 0x18 bytes, Thumb
 * func_ov045_022604d4 @ 0x022604d4, 0x20 bytes, Thumb
 * func_ov045_022604d0 @ 0x022604d0, 0x4 bytes, Thumb
 * func_ov045_022604cc @ 0x022604cc, 0x4 bytes, Thumb
 * func_ov045_022604b4 @ 0x022604b4, 0x18 bytes, Thumb
 * func_ov045_0226049c @ 0x0226049c, 0x18 bytes, Thumb
 * func_ov045_0226047c @ 0x0226047c, 0x20 bytes, Thumb
 * func_ov045_02260478 @ 0x02260478, 0x4 bytes, Thumb
 * func_ov045_02260474 @ 0x02260474, 0x4 bytes, Thumb
 */

typedef struct {
    unsigned int unk_00;
} UnkStruct_022604d4;

typedef struct {
    void *p;
} UnkStruct_0226049c;

extern void *func_020a8cac(void *);
extern void *func_020a8c38(void *);
extern void func_020edb3c(void *self);
extern unsigned char data_ov045_02261414[];
extern void *func_020a88ec(void *p);
extern void *func_020a887c(void *self);
extern char data_ov045_0226142c[];

void *func_ov045_0226050c(void *obj)
{
    func_020a8cac(obj);
    *(void **) obj = ((void * *) data_ov045_02261414);
    return obj;
}

void *func_ov045_022604f4(void *p)
{
    *(void **) p = ((int *) data_ov045_02261414);
    func_020a8c38(p);
    return p;
}

void *func_ov045_022604d4(UnkStruct_022604d4 *self)
{
    self->unk_00 = (unsigned int) data_ov045_02261414;
    func_020a8c38(self);
    func_020edb3c(self);
    return self;
}

int func_ov045_022604d0(void)
{
    return 22;
}

int func_ov045_022604cc(int p0)
{
    return ((int) (p0) + (18));
}

void *func_ov045_022604b4(void *self)
{
    func_020a88ec(self);
    *(void **) self = ((char *) data_ov045_0226142c);
    return self;
}

UnkStruct_0226049c *func_ov045_0226049c(UnkStruct_0226049c *self)
{
    self->p = ((int *) data_ov045_0226142c);
    func_020a887c(self);
    return self;
}

void *func_ov045_0226047c(void *obj)
{
    *(void **) obj = data_ov045_0226142c;
    func_020a887c(obj);
    func_020edb3c(obj);
    return obj;
}

int func_ov045_02260478(void)
{
    return 10;
}

int func_ov045_02260474(int p0)
{
    return ((int) (p0) + (14));
}
