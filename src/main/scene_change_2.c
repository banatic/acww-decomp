/* scene_change_2: 10 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b5d04 @ 0x020b5d04, 0x28 bytes, Thumb
 * func_020b5cd4 @ 0x020b5cd4, 0x30 bytes, Thumb
 * func_020b5cac @ 0x020b5cac, 0x28 bytes, Thumb
 * func_020b5c68 @ 0x020b5c68, 0x44 bytes, Thumb
 * func_020b5c24 @ 0x020b5c24, 0x44 bytes, Thumb
 * func_020b5c04 @ 0x020b5c04, 0x1e bytes, Thumb
 * func_020b5be4 @ 0x020b5be4, 0x1e bytes, Thumb
 * func_020b5be0 @ 0x020b5be0, 0x2 bytes, Thumb
 * func_020b5ba8 @ 0x020b5ba8, 0x38 bytes, Thumb
 * func_020b5b8c @ 0x020b5b8c, 0x1c bytes, Thumb
 */

typedef struct {
    volatile unsigned int unk_00;
    volatile unsigned char pad_04[15];
    volatile unsigned char flags;
} UnkStruct_020b5c24;

struct UnkStruct_020b5be4 {
    char pad_00[0x50];
    int unk_50;
};

typedef struct {
    char pad_00[0x64];
    int unk_64;
} ObjType;

typedef struct {
    char pad_00[0x50];
    int unk_50;
} ParamType;

extern char data_020e5574;
extern void func_020ee62c(void *);
extern void func_020edf54(void *p);
extern unsigned char data_020da13c[];
extern unsigned char data_020e3c94[];
extern unsigned char data_020e5460[];
extern void *func_020edf70(int);
extern void *func_020ee660(void *);
extern unsigned char data_020e5408[];
extern int func_020a6ea0(void);
extern void func_020a6eb0(int);
extern int func_0209d068(void);
extern void func_020a53ec(int, int, int, int);
extern ObjType *data_020ccf94;
extern int func_02073dd4(ObjType *obj, int val);
extern void func_0200471c(void);
extern void func_020b68f8(void);
extern void func_02003108(void);
extern void func_0208f930(void);
extern int data_021c8ca0;
extern void func_020b68e4(void);

void func_020b5be4(struct UnkStruct_020b5be4 *param);

void *func_020b5d04(void *p)
{
    *(void **) p = &data_020e5574;
    *(void **) p = ((char *) data_020e3c94);
    *(void **) p = ((char *) data_020da13c);
    func_020ee62c(p);
    return p;
}

void *func_020b5cd4(void *obj)
{
    *(void **) obj = (void *) data_020e5460;
    *(void **) obj = (void *) data_020e3c94;
    *(void **) obj = (void *) data_020da13c;
    func_020ee62c(obj);
    func_020edf54(obj);
    return obj;
}

void *func_020b5cac(void *self)
{
    *(volatile unsigned int *) self = (unsigned int) data_020e5460;
    *(volatile unsigned int *) self = (unsigned int) data_020e3c94;
    *(volatile unsigned int *) self = (unsigned int) data_020da13c;
    func_020ee62c(self);
    return self;
}

void *func_020b5c68(void)
{
    void *r4;
    unsigned char r1;

    r4 = func_020edf70(0x50);
    if (r4 != 0) {
        func_020ee660(r4);
        *(int *) r4 = (int) ((int *) data_020da13c);
        *(int *) r4 = (int) ((int *) data_020e3c94);
        r1 = *(unsigned char *) ((char *) r4 + 0x13);
        r1 |= 1;
        *(unsigned char *) ((char *) r4 + 0x13) = r1;
        r1 = *(unsigned char *) ((char *) r4 + 0x13);
        r1 |= 4;
        *(unsigned char *) ((char *) r4 + 0x13) = r1;
        *(int *) r4 = (int) ((int *) data_020e5460);
    }
    return r4;
}

void *func_020b5c24(void)
{
    UnkStruct_020b5c24 *p = (UnkStruct_020b5c24 *) func_020edf70(0x54);
    if (p != 0) {
        func_020ee660(p);
        p->unk_00 = (unsigned int) data_020da13c;
        p->unk_00 = (unsigned int) data_020e3c94;
        p->flags |= 1;
        p->flags |= 4;
        p->unk_00 = (unsigned int) data_020e5408;
    }
    return p;
}

void func_020b5c04(int param)
{
    if (func_020a6ea0() == 0xb) {
        func_020a6eb0(0xc);
        func_020b5be4((struct UnkStruct_020b5be4 *) param);
    }
}

void func_020b5be4(struct UnkStruct_020b5be4 *param)
{
    int result;
    result = func_0209d068();
    func_020a53ec(6, 3, result, 1);
    param->unk_50 = 2;
}

void func_020b5be0(void *object) {}

int func_020b5ba8(ParamType *param)
{
    ObjType *obj = data_020ccf94;

    if (func_02073dd4(obj, obj->unk_64) != 0) {
        param->unk_50 = 0;
    } else {
        param->unk_50 = 1;
    }

    func_0200471c();
    func_020b68f8();
    func_02003108();
    func_0208f930();

    return 1;
}

int func_020b5b8c(void)
{
    data_021c8ca0 = 0;
    func_020b68e4();
    return 1;
}
