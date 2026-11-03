/* mail_text: 12 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0203d540 @ 0x0203d540, 0x24 bytes, Thumb
 * func_0203d528 @ 0x0203d528, 0x18 bytes, Thumb
 * func_0203d508 @ 0x0203d508, 0x20 bytes, Thumb
 * func_0203d4f8 @ 0x0203d4f8, 0x10 bytes, Thumb
 * func_0203d4e8 @ 0x0203d4e8, 0xe bytes, Thumb
 * func_0203d4d8 @ 0x0203d4d8, 0x10 bytes, Thumb
 * func_0203d4d4 @ 0x0203d4d4, 0x4 bytes, Thumb
 * func_0203d4d0 @ 0x0203d4d0, 0x4 bytes, Thumb
 * func_0203d4cc @ 0x0203d4cc, 0x4 bytes, Thumb
 * func_0203d4c8 @ 0x0203d4c8, 0x4 bytes, Thumb
 * func_0203d4c4 @ 0x0203d4c4, 0x4 bytes, Thumb
 * func_0203d4c0 @ 0x0203d4c0, 0x4 bytes, Thumb
 */

typedef struct {
    void *vtable;
    char pad_04[0x1c];
    unsigned int unk_20;
    unsigned int unk_24;
    unsigned int unk_28;
    unsigned int unk_2C;
} UnkStruct_0203d540;

struct UnkStruct_0203d528 {
    void *unk_00;
};

typedef struct {
    unsigned char pad_00[0x20];
    unsigned int index;
} UnkStruct_0203d4f8;

struct Struct0203d4d8 {
    char pad_00[0x24];
    int unk_24;
};

extern void *func_020a81b8(void *obj);
extern char data_020da97c;
extern void func_020a8188(void *self);
extern void func_020edb3c(void *);
extern unsigned int data_020ca4a0[];
extern int data_020ca4ac[];

UnkStruct_0203d540 *func_0203d540(UnkStruct_0203d540 *obj)
{
    func_020a81b8(obj);
    obj->vtable = &data_020da97c;
    obj->unk_20 = 0;
    obj->unk_24 = 0;
    obj->unk_28 = 0;
    obj->unk_2C = 0;
    return obj;
}

struct UnkStruct_0203d528 *func_0203d528(struct UnkStruct_0203d528 *self)
{
    self->unk_00 = (void *) &data_020da97c;
    func_020a8188(self);
    return self;
}

void *func_0203d508(void *param)
{
    *(void **) param = (void *) &data_020da97c;
    func_020a8188(param);
    func_020edb3c(param);
    return param;
}

unsigned int func_0203d4f8(UnkStruct_0203d4f8 *obj)
{
    return data_020ca4a0[obj->index];
}

int func_0203d4e8(void *arg0)
{
    if (*(unsigned int *) ((char *) arg0 + 0x24) == 6) {
        return 1;
    }
    return 0;
}

int func_0203d4d8(struct Struct0203d4d8 *arg0)
{
    return data_020ca4ac[arg0->unk_24];
}

void func_0203d4d4(int *p0, int p1)
{
    p0[8] = p1;
}

void func_0203d4d0(int *p0, int p1)
{
    p0[9] = p1;
}

void func_0203d4cc(int *p0, int p1)
{
    p0[10] = p1;
}

void func_0203d4c8(int *p0, int p1)
{
    p0[11] = p1;
}

int func_0203d4c4(int *p0)
{
    return p0[10];
}

int func_0203d4c0(int *p0)
{
    return p0[11];
}
