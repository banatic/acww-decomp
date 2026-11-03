/* touch_pick_shapes_3: 12 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b8038 @ 0x020b8038, 0x28 bytes, Thumb
 * func_020b8020 @ 0x020b8020, 0x18 bytes, Thumb
 * func_020b7fe0 @ 0x020b7fe0, 0x3e bytes, Thumb
 * func_020b7fa0 @ 0x020b7fa0, 0x40 bytes, Thumb
 * func_020b7f88 @ 0x020b7f88, 0x18 bytes, Thumb
 * func_020b7f70 @ 0x020b7f70, 0x18 bytes, Thumb
 * func_020b7f60 @ 0x020b7f60, 0x10 bytes, Thumb
 * func_020b7f50 @ 0x020b7f50, 0x10 bytes, Thumb
 * func_020b7f24 @ 0x020b7f24, 0x2a bytes, Thumb
 * func_020b7f04 @ 0x020b7f04, 0x20 bytes, Thumb
 * func_020b7ee8 @ 0x020b7ee8, 0x1a bytes, Thumb
 * func_020b7ed8 @ 0x020b7ed8, 0x10 bytes, Thumb
 */

struct UnkStruct_020b8038 {
    unsigned int unk_00;
    unsigned char pad_04[0x34];
    unsigned int unk_38;
    unsigned int unk_3C;
    unsigned char unk_40;
};

typedef struct {
    void *vtbl;
} Object;

typedef struct {
    int data[3];
} UnkStruct_020b7fe0;

typedef struct UnkStruct_020b7fa0 {
    unsigned int data[4];
} UnkStruct_020b7fa0;

typedef struct St {
    char pad_00[0x3c];
    unsigned int unk_3C;
    unsigned char unk_40;
} St;

typedef struct {
    char pad_00[0x10];
    unsigned char unk_10;
    int unk_14;
    int unk_18;
} UnkStruct_020b7f88;

typedef struct {
    unsigned char pad_00[0x10];
    unsigned char unk_10;
    unsigned int unk_14;
    unsigned int unk_18;
} UnkStruct_020b7f70;

typedef struct {
    unsigned char pad_00[0x10];
    unsigned char unk_10;
    unsigned char pad_11[3];
    unsigned int unk_14;
} UnkStruct_020b7f04;

typedef struct {
    unsigned char pad_00[0x14];
    unsigned int unk_14;
    unsigned char unk_18;
    unsigned char pad_19[3];
    unsigned int unk_1C;
} UnkStruct_020b7ee8;

extern void func_0202ff00(void *ptr);
extern unsigned char data_020e5810[];
extern void func_0202fed4(void *);
extern int func_0203f844(void *dst, int src);
extern int func_0202fc5c(UnkStruct_020b7fa0 *local, int, int, int);
extern int func_0202fc18(St *arg0, int arg1, int arg2, int arg3, UnkStruct_020b7fa0 *local);
extern void func_0202f27c(void *obj);
extern void func_0202f278(void);
extern void func_0202f268(UnkStruct_020b7f04 *s, int a, int b);
extern void *func_02030690(void *ptr);
extern int func_02030658(int);

int func_020b7fa0(St *arg0, int arg1, int arg2, int arg3, int arg4, unsigned char arg5);
int func_020b7f04(UnkStruct_020b7f04 *s, int a, int b, int c, unsigned char d);

void *func_020b8038(struct UnkStruct_020b8038 *ptr)
{
    func_0202ff00(ptr);
    ptr->unk_00 = (unsigned int) data_020e5810;
    ptr->unk_3C = 0;
    ptr->unk_38 = 0;
    ptr->unk_40 = 0xFF;
    return ptr;
}

Object *func_020b8020(Object *self)
{
    self->vtbl = ((char *) data_020e5810);
    func_0202fed4(self);
    return self;
}

int func_020b7fe0(void *param0, int param1, int param2, int param3, int arg4, unsigned char arg5)
{
    UnkStruct_020b7fe0 local0;
    UnkStruct_020b7fe0 local1;
    UnkStruct_020b7fe0 local2;

    func_0203f844(&local0, param1);
    func_0203f844(&local1, param2);
    func_0203f844(&local2, param3);
    return func_020b7fa0((St *) param0, (int) (&local0), (int) (&local1), (int) (&local2), arg4, arg5);
}

int func_020b7fa0(St *arg0, int arg1, int arg2, int arg3, int arg4, unsigned char arg5)
{
    UnkStruct_020b7fa0 local;
    if (func_0202fc5c(&local, arg1, arg2, arg3)) {
        arg0->unk_3C = arg4;
        arg0->unk_40 = arg5;
        return func_0202fc18(arg0, arg1, arg2, arg3, &local);
    }
    return 0;
}

UnkStruct_020b7f88 *func_020b7f88(UnkStruct_020b7f88 *obj)
{
    func_0202f27c(obj);
    obj->unk_14 = 0;
    obj->unk_10 = 0;
    obj->unk_18 = 0;
    return obj;
}

UnkStruct_020b7f70 *func_020b7f70(UnkStruct_020b7f70 *ptr)
{
    func_0202f27c((void *) ptr);
    ptr->unk_14 = 0;
    ptr->unk_10 = 0;
    ptr->unk_18 = 0;
    return ptr;
}

int func_020b7f60(int arg)
{
    func_0202f278();
    return arg;
}

int func_020b7f50(int arg)
{
    func_0202f278();
    return arg;
}

void func_020b7f24(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned char e)
{
    unsigned char local[12];
    func_0203f844(local, (int) ((void *) b));
    func_020b7f04((UnkStruct_020b7f04 *) a, (int) local, c, d, e);
}

int func_020b7f04(UnkStruct_020b7f04 *s, int a, int b, int c, unsigned char d)
{
    s->unk_14 = c;
    s->unk_10 = d;
    func_0202f268(s, a, b);
    return 1;
}

UnkStruct_020b7ee8 *func_020b7ee8(UnkStruct_020b7ee8 *ptr)
{
    func_02030690(ptr);
    ptr->unk_14 = 0;
    ptr->unk_1C = 0;
    ptr->unk_18 = 0xff;
    return ptr;
}

int func_020b7ed8(int arg)
{
    func_02030658(arg);
    return arg;
}
