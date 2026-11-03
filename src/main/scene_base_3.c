/* scene_base_3: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020161ac @ 0x020161ac, 0x38 bytes, Thumb
 * func_02016194 @ 0x02016194, 0x18 bytes, Thumb
 * func_02016174 @ 0x02016174, 0x20 bytes, Thumb
 * func_0201615c @ 0x0201615c, 0x18 bytes, Thumb
 */

typedef struct {
    void *unk_00;
    char pad_04[68];
    int unk_48;
    int unk_4C;
    int unk_50;
    char pad_54[8];
    int unk_5C;
    char pad_60[4];
    int unk_64;
    char pad_68[22];
    unsigned short unk_7E;
} UnkStruct_020161ac;

struct UnkStruct_02016194 {
    void *unk_00;
};

struct _Obj {
    void *vtbl;
};

extern void *func_02066a30(void *);
extern void func_020159f0(void *);
extern unsigned char data_020d8bd4[];
extern void *func_02066994(void *);
extern void func_020edb3c(void *);

UnkStruct_020161ac *func_020161ac(UnkStruct_020161ac *r4)
{
    func_02066a30(r4);
    r4->unk_00 = (void *) data_020d8bd4;
    r4->unk_7E = 0xfff1;
    r4->unk_48 = 0;
    r4->unk_4C = 0;
    r4->unk_50 = 0;
    r4->unk_5C = 0;
    r4->unk_64 = 12;
    func_020159f0(r4);
    return r4;
}

void *func_02016194(void *self)
{
    struct UnkStruct_02016194 *obj = self;
    obj->unk_00 = ((unsigned char *) data_020d8bd4);
    func_02066994(obj);
    return obj;
}

void *func_02016174(struct _Obj *obj)
{
    obj->vtbl = ((char *) data_020d8bd4);
    func_02066994(obj);
    func_020edb3c(obj);
    return obj;
}

void *func_0201615c(void *arg)
{
    *((void **) arg) = ((int *) data_020d8bd4);
    func_02066994(arg);
    return arg;
}
