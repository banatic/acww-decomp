/* talk_receiver_2: 10 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02066a9c @ 0x02066a9c, 0x20 bytes, Thumb
 * func_02066a84 @ 0x02066a84, 0x18 bytes, Thumb
 * func_02066a64 @ 0x02066a64, 0x20 bytes, Thumb
 * func_02066a60 @ 0x02066a60, 0x4 bytes, Thumb
 * func_02066a5c @ 0x02066a5c, 0x4 bytes, Thumb
 * func_02066a30 @ 0x02066a30, 0x2c bytes, Thumb
 * func_02066a04 @ 0x02066a04, 0x2c bytes, Thumb
 * func_020669e0 @ 0x020669e0, 0x24 bytes, Thumb
 * func_020669b8 @ 0x020669b8, 0x28 bytes, Thumb
 * func_02066994 @ 0x02066994, 0x24 bytes, Thumb
 */

struct UnkStruct_02066a64 {
    void *vtbl;
};

struct UnkStruct_02066a30 {
    void *unk_00;
    char pad_04[0x1c];
    char sub[0x20];
    int unk_40;
    char unk_44;
};

struct Func02066a04Sub {
    char data[0x20];
};

struct Func02066a04Obj {
    void *unk_00;
    char pad_04[0x1c];
    struct Func02066a04Sub sub;
    int unk_40;
    unsigned char unk_44;
};

struct UnkStruct_02066994 {
    void *unk_00;
    unsigned char pad_04[0x1c];
    void *unk_20;
};

extern void *func_020a8cac(void *obj);
extern void func_020a8c1c(void *obj);
extern void *func_020a8c38(void *obj);
extern char data_020def4c;
extern void func_020edb3c(void *);
extern void *func_020a81b8(void *obj);
extern char data_020df008[];
extern void func_020a8188(void *p);

void *func_02066a9c(void *obj)
{
    func_020a8cac(obj);
    *(unsigned int *) obj = (unsigned int) ((unsigned int *) &data_020def4c);
    func_020a8c1c(obj);
    return obj;
}

void *func_02066a84(void *obj)
{
    *(void **) obj = (void *) &data_020def4c;
    func_020a8c38(obj);
    return obj;
}

struct UnkStruct_02066a64 *func_02066a64(struct UnkStruct_02066a64 *self)
{
    self->vtbl = &data_020def4c;
    func_020a8c38(self);
    func_020edb3c(self);
    return self;
}

int func_02066a60(void)
{
    return 14;
}

int func_02066a5c(int p0)
{
    return ((int) (p0) + (18));
}

struct UnkStruct_02066a30 *func_02066a30(struct UnkStruct_02066a30 *obj)
{
    func_020a81b8(obj);
    obj->unk_00 = ((char *) data_020df008);
    func_02066a9c(obj->sub);
    obj->unk_40 = 0;
    *((char *) obj + 0x44) = 0;
    return obj;
}

struct Func02066a04Obj *func_02066a04(struct Func02066a04Obj *obj)
{
    func_020a81b8(obj);
    obj->unk_00 = ((char *) data_020df008);
    func_02066a9c(&obj->sub);
    obj->unk_40 = 0;
    obj->unk_44 = 0;
    return obj;
}

void *func_020669e0(void *obj)
{
    *(void **) obj = data_020df008;
    func_02066a84((char *) obj + 0x20);
    func_020a8188(obj);
    return obj;
}

void *func_020669b8(void *p)
{
    *(unsigned int *) p = (unsigned int) ((unsigned char *) data_020df008);
    func_02066a84((char *) p + 0x20);
    func_020a8188(p);
    func_020edb3c(p);
    return p;
}

void *func_02066994(struct UnkStruct_02066994 *p)
{
    p->unk_00 = ((int *) data_020df008);
    func_02066a84(&p->unk_20);
    func_020a8188(p);
    return p;
}
