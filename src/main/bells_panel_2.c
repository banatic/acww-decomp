/* bells_panel_2: 13 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208b9d8 @ 0x0208b9d8, 0x8 bytes, Thumb
 * func_0208b9d0 @ 0x0208b9d0, 0x8 bytes, Thumb
 * func_0208b9c0 @ 0x0208b9c0, 0xe bytes, Thumb
 * func_0208b9b8 @ 0x0208b9b8, 0x8 bytes, Thumb
 * func_0208b9b0 @ 0x0208b9b0, 0x8 bytes, Thumb
 * func_0208b9a8 @ 0x0208b9a8, 0x6 bytes, Thumb
 * func_0208b990 @ 0x0208b990, 0x18 bytes, Thumb
 * func_0208b954 @ 0x0208b954, 0x3c bytes, Thumb
 * func_0208b930 @ 0x0208b930, 0x22 bytes, Thumb
 * func_0208b928 @ 0x0208b928, 0x6 bytes, Thumb
 * func_0208b900 @ 0x0208b900, 0x28 bytes, Thumb
 * func_0208b8d0 @ 0x0208b8d0, 0x30 bytes, Thumb
 * func_0208b8a8 @ 0x0208b8a8, 0x28 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[32];
    unsigned long unk_20;
} UnkStruct_0208b9a8;

struct UnkStruct_0208b990 {
    unsigned char pad_00[0x80];
    unsigned char flag;
};

typedef struct {
    char pad_00[0xc];
    char sub[0x14];
    int unk_20;
} UnkStruct_0208b954;

typedef struct {
    unsigned char pad_00[32];
    unsigned long unk_20;
} UnkStruct_0208b928;

struct UnkStruct_0208b900 {
    unsigned char pad_00[0x80];
    unsigned char unk_80;
};

typedef struct {
    char pad_00[0xC];
    void *unk_0C;
} UnkStruct_0208b8a8;

extern void func_0208a1f0(void *sub, void *data);
extern void func_0208a1ec(void *sub, int value);
extern void *func_0208a144(void *sub);
extern void func_0208b800(void *obj);
extern void func_0208b83c(void *obj);
extern int data_020d5c54;
extern void func_0208a0c8(void *);
extern int func_0208a160(void *);
extern int func_0208b79c(struct UnkStruct_0208b900 *p);
extern void func_0208b748(struct UnkStruct_0208b900 *p, int value);
extern char data_020d5c5c;
extern void func_0208b824(UnkStruct_0208b8a8 *);

void func_0208b954(UnkStruct_0208b954 *obj);
void func_0208b928(UnkStruct_0208b928 *p);
void func_0208b8d0(char *param);

void func_0208b9d8(int p0)
{
    *(unsigned char *) ((char *) (((int) (p0) + (128))) + (0)) = 1;
}

void func_0208b9d0(int p0)
{
    *(unsigned char *) ((char *) (((int) (p0) + (128))) + (0)) = 0;
}

int func_0208b9c0(void *param)
{
    if (*(unsigned int *) ((char *) param + 0x20) == 0) {
        return 1;
    } else {
        return 0;
    }
}

void func_0208b9b8(int p0)
{
    *(unsigned char *) ((char *) (((int) (p0) + (130))) + (0)) = 1;
}

void func_0208b9b0(int p0)
{
    *(unsigned char *) ((char *) (((int) (p0) + (130))) + (0)) = 0;
}

void func_0208b9a8(UnkStruct_0208b9a8 *p)
{
    p->unk_20 = 0;
}

void func_0208b990(struct UnkStruct_0208b990 *p)
{
    if (p->flag != 0) {
        func_0208b954((UnkStruct_0208b954 *) p);
    }
}

void func_0208b954(UnkStruct_0208b954 *obj)
{
    obj->unk_20 = 1;
    func_0208a1f0(obj->sub, &data_020d5c54);
    func_0208a1ec(obj->sub, 1);
    func_0208a144(obj->sub);
    func_0208b800(obj);
    func_0208b83c(obj);
}

void func_0208b930(void *param)
{
    void *ptr;
    int result;

    ptr = (void *) ((char *) param + 0xc);
    func_0208a0c8(ptr);
    ptr = (void *) ((char *) param + 0xc);
    result = func_0208a160(ptr);
    if (result != 0) {
        func_0208b928((UnkStruct_0208b928 *) param);
    }
}

void func_0208b928(UnkStruct_0208b928 *p)
{
    p->unk_20 = 2;
}

void func_0208b900(struct UnkStruct_0208b900 *p)
{
    int value;

    value = func_0208b79c(p);
    if (p->unk_80 == 0) {
        func_0208b8d0((char *) p);
        value = 0;
    }
    func_0208b748(p, value);
}

void func_0208b8d0(char *param)
{
    *(int *) (param + 0x20) = 3;
    func_0208a1f0(param + 0xc, &data_020d5c5c);
    func_0208a1ec(param + 0xc, 1);
    func_0208a144(param + 0xc);
}

void func_0208b8a8(UnkStruct_0208b8a8 *ptr)
{
    func_0208a0c8((void *) (&ptr->unk_0C));
    if (func_0208a160((void *) (&ptr->unk_0C))) {
        func_0208b824(ptr);
        func_0208b9a8((UnkStruct_0208b9a8 *) ptr);
    }
}
