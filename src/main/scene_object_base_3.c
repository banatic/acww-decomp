/* scene_object_base_3: 13 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0203f130 @ 0x0203f130, 0x2c bytes, Thumb
 * func_0203f0f8 @ 0x0203f0f8, 0x38 bytes, Thumb
 * func_0203f0b8 @ 0x0203f0b8, 0x40 bytes, Thumb
 * func_0203f080 @ 0x0203f080, 0x38 bytes, Thumb
 * func_0203f070 @ 0x0203f070, 0x10 bytes, Thumb
 * func_0203f030 @ 0x0203f030, 0x40 bytes, Thumb
 * func_0203f004 @ 0x0203f004, 0x2c bytes, Thumb
 * func_0203efdc @ 0x0203efdc, 0x28 bytes, Thumb
 * func_0203efc4 @ 0x0203efc4, 0x18 bytes, Thumb
 * func_0203efbc @ 0x0203efbc, 0x6 bytes, Thumb
 * func_0203efb0 @ 0x0203efb0, 0xc bytes, Thumb
 * func_0203ef90 @ 0x0203ef90, 0x20 bytes, Thumb
 * func_0203ef5c @ 0x0203ef5c, 0x34 bytes, Thumb
 */

typedef struct {
    void *unk_00;
    unsigned char pad_04[0xD0];
    int unk_D4;
    int unk_D8;
    int unk_DC;
} UnkStruct_0203f130;

typedef struct {
    unsigned int unk_00;
    char pad_04[0x4c];
    char sub;
} UnkStruct_0203f0f8;

struct UnkStruct_0203f030 {
    unsigned char pad_00[0xdc];
    int unk_DC;
    void *unk_E0;
    unsigned char pad_E4[4];
    short unk_E8;
};

typedef struct {
    unsigned char pad_00[220];
    unsigned long unk_DC;
} UnkStruct_0203efbc;

struct UnkStruct_0203efb0 {
    char pad_00[0xc];
    unsigned short unk_0C;
    char pad_0E[0xce];
    unsigned int unk_DC;
};

struct UnkStruct_0203ef90 {
    int pad_00[3];
    int unk_0C;
};

struct Node {
    int unk_00;
    struct Node *next;
    int unk_08;
    void *key;
};

extern void *func_02003564(void *);
extern void func_020ee62c(void *);
extern unsigned char data_020d7244[];
extern unsigned char data_020da13c[];
extern unsigned char data_020dab34[];
extern unsigned char data_0213ff78[];
extern void func_020edf54(void *);
extern int func_020e8ce0(void *a, void *b);
extern void func_02065c68(void *arg0);
extern unsigned char data_021c72cc[];
extern int func_0200354c(void);
extern void func_0203edf4(void *p, unsigned int val);
extern void func_0203eddc(void *p);
extern int func_02065c1c(void *a, void *b);
extern void func_02003530(void *a, int b);
extern int func_02003518(void *object);
extern int func_02003428(void *);
extern struct UnkStruct_0203ef90 *func_02065c00(void *a, int b);
extern int func_0203ee34(void *a, void *b);

UnkStruct_0203f130 *func_0203f130(UnkStruct_0203f130 *obj)
{
    func_02003564(obj);
    obj->unk_00 = ((int *) data_020dab34);
    obj->unk_D4 = 0;
    obj->unk_D8 = 0;
    obj->unk_DC = 0;
    return obj;
}

void *func_0203f0f8(UnkStruct_0203f0f8 *obj)
{
    obj->unk_00 = (unsigned int) data_020dab34;
    obj->unk_00 = (unsigned int) data_020d7244;
    func_020e8ce0((void *) ((unsigned int) data_0213ff78), &obj->sub);
    obj->unk_00 = (unsigned int) data_020da13c;
    func_020ee62c(obj);
    return obj;
}

void *func_0203f0b8(void *p)
{
    *(volatile unsigned int *) p = (unsigned int) data_020dab34;
    *(volatile unsigned int *) p = (unsigned int) data_020d7244;
    func_020e8ce0((void *) ((unsigned int) data_0213ff78), (char *) p + 0x50);
    *(volatile unsigned int *) p = (unsigned int) data_020da13c;
    func_020ee62c(p);
    func_020edf54(p);
    return p;
}

void *func_0203f080(void *obj)
{
    volatile unsigned int *p = (volatile unsigned int *) obj;
    *p = (unsigned int) data_020dab34;
    *p = (unsigned int) data_020d7244;
    func_020e8ce0((void *) data_0213ff78, (char *) obj + 0x50);
    *p = (unsigned int) data_020da13c;
    func_020ee62c(obj);
    return obj;
}

void func_0203f070(void)
{
    func_02065c68((void *) data_021c72cc);
}

int func_0203f030(void *p)
{
    struct UnkStruct_0203f030 *s = (struct UnkStruct_0203f030 *) p;
    if (func_0200354c() == 0) {
        return 0;
    }
    s->unk_DC = 0;
    s->unk_E0 = p;
    func_0203edf4(p, 0x3000);
    s->unk_E8 = 0;
    func_0203eddc(p);
    return 1;
}

void func_0203f004(void *r0, int r1)
{
    void *r5 = r0;
    int r4 = r1;

    if (r4 == 2) {
        func_02065c1c((void *) data_021c72cc, (char *) r5 + 0xd4);
    }
    func_02003530(r5, r4);
}

int func_0203efdc(char *param)
{
    if (func_02003518(param) == 0) {
        return 0;
    }
    param += 0xd4;
    func_020e8ce0(((int *) data_021c72cc), param);
    return 1;
}

int func_0203efc4(void *argument0)
{
    int result;
    if (func_02003428((void *) argument0) != 0) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

unsigned long func_0203efbc(UnkStruct_0203efbc *p)
{
    return p->unk_DC;
}

void func_0203efb0(struct UnkStruct_0203efb0 *arg0, unsigned int arg1)
{
    arg0->unk_DC = arg1 | ((unsigned int) arg0->unk_0C << 16);
}

int func_0203ef90(int param)
{
    struct UnkStruct_0203ef90 *result = func_02065c00(((char *) data_021c72cc), param);
    return result ? result->unk_0C : 0;
}

void *func_0203ef5c(void *arg)
{
    struct Node *node;
    void *key;

    node = (*(struct Node * *) data_021c72cc);
    while (node) {
        key = node->key;
        if (key != arg && func_0203ee34(key, arg) != 0) {
            return key;
        }
        node = node->next;
    }
    return 0;
}
