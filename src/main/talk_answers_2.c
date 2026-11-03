/* talk_answers_2: 32 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020ab790 @ 0x020ab790, 0x4 bytes, Thumb
 * func_020ab78c @ 0x020ab78c, 0x4 bytes, Thumb
 * func_020ab788 @ 0x020ab788, 0x4 bytes, Thumb
 * func_020ab780 @ 0x020ab780, 0x6 bytes, Thumb
 * func_020ab778 @ 0x020ab778, 0x6 bytes, Thumb
 * func_020ab774 @ 0x020ab774, 0x4 bytes, Thumb
 * func_020ab76c @ 0x020ab76c, 0x8 bytes, Thumb
 * func_020ab758 @ 0x020ab758, 0x14 bytes, Thumb
 * func_020ab750 @ 0x020ab750, 0x6 bytes, Thumb
 * func_020ab71c @ 0x020ab71c, 0x34 bytes, Thumb
 * func_020ab6c8 @ 0x020ab6c8, 0x54 bytes, Thumb
 * func_020ab694 @ 0x020ab694, 0x34 bytes, Thumb
 * func_020ab670 @ 0x020ab670, 0x24 bytes, Thumb
 * func_020ab628 @ 0x020ab628, 0x46 bytes, Thumb
 * func_020ab5f8 @ 0x020ab5f8, 0x30 bytes, Thumb
 * func_020ab5e4 @ 0x020ab5e4, 0x14 bytes, Thumb
 * func_020ab58c @ 0x020ab58c, 0x58 bytes, Thumb
 * func_020ab558 @ 0x020ab558, 0x34 bytes, Thumb
 * func_020ab550 @ 0x020ab550, 0x8 bytes, Thumb
 * func_020ab53c @ 0x020ab53c, 0x14 bytes, Thumb
 * func_020ab528 @ 0x020ab528, 0x14 bytes, Thumb
 * func_020ab51c @ 0x020ab51c, 0xc bytes, Thumb
 * func_020ab510 @ 0x020ab510, 0xc bytes, Thumb
 * func_020ab504 @ 0x020ab504, 0xc bytes, Thumb
 * func_020ab4f8 @ 0x020ab4f8, 0xc bytes, Thumb
 * func_020ab4ec @ 0x020ab4ec, 0xc bytes, Thumb
 * func_020ab4e0 @ 0x020ab4e0, 0xc bytes, Thumb
 * func_020ab4d4 @ 0x020ab4d4, 0xc bytes, Thumb
 * func_020ab4c8 @ 0x020ab4c8, 0xc bytes, Thumb
 * func_020ab4bc @ 0x020ab4bc, 0xc bytes, Thumb
 * func_020ab4a8 @ 0x020ab4a8, 0x14 bytes, Thumb
 * func_020ab42c @ 0x020ab42c, 0x7c bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[140];
    unsigned long unk_8C;
} UnkStruct_020ab780;

typedef struct {
    unsigned char pad_00[140];
    unsigned long unk_8C;
} UnkStruct_020ab750;

typedef struct {
    int unk_00;
    const char *name;
    char unk_08[0x5c];
    char unk_64;
} UnkStruct_020ab71c;

typedef struct {
    unsigned char data[0x90];
} UnkStruct_020ab628;

typedef struct {
    char data[0x90];
} UnkStruct_020ab5f8_2;

typedef struct {
    UnkStruct_020ab5f8_2 elements[5];
    int count;
} UnkStruct_020ab5f8;

struct UnkStruct_020ab58c {
    char pad_00[0x2d8];
    int unk_2D8;
    unsigned char unk_2DC;
    unsigned char unk_2DD[0x1a];
    char pad_2F7;
    unsigned char unk_2F8[0x5c];
    unsigned char unk_354[0xc];
    int unk_360;
};

typedef struct {
    char data[0x90];
} Elem;

typedef struct {
    Elem arr[5];
    int unk_2D0;
    int unk_2D4;
} Big;

struct UnkStruct_020ab4bc {
    unsigned char pad_00[0x2d0];
    int unk_2D0;
};

typedef struct {
    char data[0x90];
} UnkStruct_020ab42c;

typedef struct {
    UnkStruct_020ab42c arr[1];
    char pad_90[0x2d8 - 0x90];
    int unk_2D8;
    char unk_2DC;
    char unk_2DD;
    char pad_2DE[0x2f6 - 0x2de];
    char unk_2F6;
    char pad_2F7[1];
    char unk_2F8[1];
    char pad_2F9[0x354 - 0x2f9];
    char unk_354[1];
} LargeStruct;

extern char *strncpy(void *arg0, int arg1, int arg2);
extern int func_02064328(char *dest, const char *fmt, ...);
extern int func_020ab83c(void *a, void *b, void *c, void *d);
extern __arm void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void *func_020ab804(void *);
extern void *func_020ab7e8(void *);
extern void *func_020ab8dc(void *);
extern int func_020a82e8(void *);
extern unsigned char data_021f43ec;
extern void func_020a82e4(void *);
extern void *func_020ab8c4(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern int func_020ab39c(int a);
extern void MI_CpuFill8(void *dest, int value, int size);
extern void func_020a8c1c(void *ptr);
extern void func_020a82b0(void *ptr);
extern void func_020ab79c(Elem *e);
extern int func_020ab798(int);
extern unsigned char *func_020ab794(void *);
extern void *func_020a8bb8(char *, const char *);
extern void *func_020a82ac(void *object);
extern void func_020a82bc(char *, const void *);

void func_020ab5e4(int arg);
void func_020ab58c(struct UnkStruct_020ab58c *obj);
void func_020ab558(Big *p);

int func_020ab790(int p0)
{
    return ((int) (p0) + (113));
}

int func_020ab78c(int p0)
{
    return ((int) (p0) + (100));
}

int func_020ab788(int p0)
{
    return ((int) (p0) + (139));
}

unsigned long func_020ab780(UnkStruct_020ab780 *p)
{
    return p->unk_8C;
}

void func_020ab778(unsigned char *d, unsigned char *s)
{
    *d = *s;
}

void func_020ab774(int *p0, int p1)
{
    p0[1] = p1;
}

void func_020ab76c(int p0, unsigned char *p1)
{
    *(unsigned char *) ((char *) (((int) (p0) + (112))) + (0)) = p1[0];
}

void func_020ab758(void *arg0, int arg1)
{
    ((unsigned char *) arg0)[0x8a] = 0;
    strncpy((unsigned char *) arg0 + 0x71, arg1, 0x19);
}

void func_020ab750(UnkStruct_020ab750 *p, unsigned long v)
{
    p->unk_8C = v;
}

void func_020ab71c(UnkStruct_020ab71c *p)
{
    char path[0x40];
    const char *lang = "KOR";
    func_02064328(path, "/script/%s/select/%s.bmg", lang, p->name);
    func_020ab83c(&p->unk_08, path, p, &p->unk_64);
}

void *func_020ab6c8(void *obj)
{
    __cxa_vec_ctor((void *) (obj), 5, 0x90, (((void (*)(void *)) func_020ab804)), (((void (*)(void *)) func_020ab7e8)));
    ((unsigned char *) obj)[0x2dc] = data_021f43ec;
    func_020ab8dc((char *) obj + 0x2f8);
    func_020a82e8((char *) obj + 0x354);
    func_020ab5e4((int) obj);
    return obj;
}

void *func_020ab694(void *p)
{
    func_020a82e4((char *) p + 0x354);
    func_020ab8c4((char *) p + 0x2f8);
    __cxa_vec_cleanup((void *) (p), 5, 0x90, (((void (*)(void *)) func_020ab7e8)));
    return p;
}

void func_020ab670(void *param1, int param2, int param3)
{
    func_020ab5e4((int) param1);
    *(int *) ((char *) param1 + 0x2d0) = param2;
    *(int *) ((char *) param1 + 0x2d4) = param3;
}

void func_020ab628(UnkStruct_020ab628 *base, int index, int arg3, int arg4, int arg5, int arg6, int arg7)
{
    UnkStruct_020ab628 *p;
    int tmp;

    p = &base[index];

    func_020ab778((unsigned char *) p, (unsigned char *) arg3);
    tmp = func_020ab39c(arg4);
    func_020ab774((int *) p, tmp);
    func_020ab76c((int) p, (unsigned char *) arg5);
    func_020ab750((UnkStruct_020ab750 *) p, arg7);
    if (arg6 != 0) {
        func_020ab758((void *) p, arg6);
    }
}

void func_020ab5f8(UnkStruct_020ab5f8 *arg)
{
    int i;
    for (i = 0; i < arg->count; i++) {
        func_020ab71c((UnkStruct_020ab71c *) (&arg->elements[i]));
    }
}

void func_020ab5e4(int arg)
{
    func_020ab58c((struct UnkStruct_020ab58c *) arg);
    func_020ab558((Big *) arg);
}

void func_020ab58c(struct UnkStruct_020ab58c *obj)
{
    obj->unk_2D8 = -1;
    obj->unk_2DC = data_021f43ec;
    MI_CpuFill8(obj->unk_2DD, 0, 0x1a);
    func_020a8c1c(obj->unk_2F8);
    func_020a82b0(obj->unk_354);
    obj->unk_360 = 0;
}

void func_020ab558(Big *p)
{
    unsigned int i = 0;
    goto test;
loop:
    func_020ab79c(&p->arr[i]);
    i++;
test:
    if (i < 5) {
        goto loop;
    }
    p->unk_2D0 = 0;
    p->unk_2D4 = -1;
}

void *func_020ab550(unsigned char *p, int i)
{
    return (p) + i * 144;
}

int func_020ab53c(void *arg)
{
    return func_020ab798((int) func_020ab550((unsigned char *) arg, 0));
}

int func_020ab528(int a)
{
    return func_020ab798((int) func_020ab550((unsigned char *) a, 4));
}

unsigned int func_020ab51c(unsigned int *r0)
{
    return r0[0x2d0 / 4];
}

int func_020ab510(void *arg0)
{
    return *(int *) ((char *) arg0 + 0x2d4);
}

unsigned int func_020ab504(void *arg0)
{
    return *(unsigned int *) ((char *) arg0 + 0x2d8);
}

unsigned int func_020ab4f8(unsigned int *r0)
{
    return r0[0x360 / 4];
}

unsigned int func_020ab4ec(unsigned int r0)
{
    return r0 + 0x2dc;
}

int func_020ab4e0(int a)
{
    return a + 0x2dd;
}

int func_020ab4d4(int arg0)
{
    return arg0 + 0x2f8;
}

int func_020ab4c8(int a)
{
    return a + 0x354;
}

void func_020ab4bc(struct UnkStruct_020ab4bc *obj, int value)
{
    obj->unk_2D0 = value;
}

void func_020ab4a8(void *r0)
{
    unsigned int *base = (unsigned int *) r0;
    unsigned int value;
    unsigned int result;

    value = *(unsigned int *) ((unsigned char *) base + 0x2d0);
    result = value - 1;
    *(unsigned int *) ((unsigned char *) base + 0x2d4) = result;
}

void func_020ab42c(LargeStruct *obj, int index)
{
    UnkStruct_020ab42c *elem;
    const char *name;
    void *temp;

    elem = &obj->arr[index];
    obj->unk_2D8 = index;
    obj->unk_2DC = *func_020ab794(elem);
    func_020a8bb8(obj->unk_2F8, (const char *) func_020ab798((int) elem));
    name = (const char *) func_020ab790((int) elem);
    obj->unk_2F6 = 0;
    strncpy((void *) ((char *) obj + 0x2dd), (int) name, 0x19);
    temp = func_020a82ac((void *) func_020ab78c((int) elem));
    func_020a82bc((char *) obj + 0x354, temp);
}
