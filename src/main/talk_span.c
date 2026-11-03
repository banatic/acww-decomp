/* talk_span: 13 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206bffc @ 0x0206bffc, 0x3c bytes, Thumb
 * func_0206bfdc @ 0x0206bfdc, 0x20 bytes, Thumb
 * func_0206bfb4 @ 0x0206bfb4, 0x28 bytes, Thumb
 * func_0206bf78 @ 0x0206bf78, 0x3a bytes, Thumb
 * func_0206bf3c @ 0x0206bf3c, 0x3a bytes, Thumb
 * func_0206bf08 @ 0x0206bf08, 0x32 bytes, Thumb
 * func_0206bef8 @ 0x0206bef8, 0xe bytes, Thumb
 * func_0206bef4 @ 0x0206bef4, 0x2 bytes, Thumb
 * func_0206bee0 @ 0x0206bee0, 0x14 bytes, Thumb
 * func_0206be94 @ 0x0206be94, 0x4c bytes, Thumb
 * func_0206be90 @ 0x0206be90, 0x2 bytes, Thumb
 * func_0206be88 @ 0x0206be88, 0x6 bytes, Thumb
 * func_0206be6c @ 0x0206be6c, 0x1c bytes, Thumb
 */

typedef struct UnkStruct_0206bffc {
    void *unk_00;
    char pad_04[0x20];
    int unk_24;
    int unk_28;
    int unk_2C;
    int unk_30;
    int unk_34;
    char byte1;
    char byte2;
} UnkStruct_0206bffc;

typedef struct UnkStruct_0206bf78 {
    char pad_00[0x2c];
    int unk_2C;
    int unk_30;
    int unk_34;
    unsigned char unk_38;
    unsigned char unk_39;
} UnkStruct_0206bf78;

typedef struct {
    unsigned char pad_00[0x2c];
    int unk_2C;
    unsigned int unk_30;
    int unk_34;
    unsigned char unk_38;
    unsigned char unk_39;
} UnkStruct_0206bf3c;

struct UnkStruct_0206bf08 {
    char pad_00[0x2c];
    int unk_2C;
    int unk_30;
    char pad_34[0x4];
    unsigned char unk_38;
};

typedef struct {
    char pad_00[0x24];
    int unk_24;
    int unk_28;
    int unk_2C;
    char pad_30[4];
    int unk_34;
    unsigned char unk_38;
    unsigned char unk_39;
} UnkStruct_0206be94;

typedef struct {
    unsigned char pad_00[56];
    unsigned char unk_38;
} UnkStruct_0206be88;

struct UnkStruct_0206be6c {
    char pad_00[0x2c];
    int unk_2C;
    int unk_30;
    int unk_34;
    char unk_38;
    char unk_39;
};

extern void *func_020a9484(void *);
extern unsigned char data_020def9c[];
extern unsigned char data_020e3e68[];
extern void *func_020a941c(void *p);
extern void func_020edb3c(void *);
extern void func_020a94a4(UnkStruct_0206bf78 *param0);
extern void func_020a9354(UnkStruct_0206bf78 *param0, int param1);
extern int func_020a92d8(void *obj, int arg);
extern int func_0206c234(int, int);
extern void func_02068104(int, int);

void func_0206be6c(struct UnkStruct_0206be6c *s);

UnkStruct_0206bffc *func_0206bffc(UnkStruct_0206bffc *this, int a, int b)
{
    func_020a9484(this);
    this->unk_00 = (void *) data_020e3e68;
    this->unk_00 = (void *) data_020def9c;
    this->unk_24 = a;
    this->unk_28 = b;
    this->unk_2C = 0;
    this->unk_30 = 0;
    this->unk_34 = 0;
    this->byte1 = 0;
    this->byte2 = 0;
    return this;
}

void *func_0206bfdc(void *p)
{
    volatile unsigned int *vp = (volatile unsigned int *) p;
    *vp = (unsigned int) ((char *) data_020def9c);
    *vp = (unsigned int) ((char *) data_020e3e68);
    func_020a941c(p);
    return p;
}

void *func_0206bfb4(void *obj)
{
    *(volatile unsigned int *) obj = (unsigned int) data_020def9c;
    *(volatile unsigned int *) obj = (unsigned int) data_020e3e68;
    func_020a941c(obj);
    func_020edb3c(obj);
    return obj;
}

void func_0206bf78(UnkStruct_0206bf78 *param0, int param1, int param2, unsigned char param3)
{
    if (param2 > 0) {
        func_020a94a4(param0);
        func_020a9354(param0, param1);
        param0->unk_30 = 0;
        param0->unk_34 = param2;
        param0->unk_39 = param3;
        param0->unk_38 = 0;
        param0->unk_2C = 1;
    }
}

void func_0206bf3c(UnkStruct_0206bf3c *a, unsigned int b, unsigned int c, int d)
{
    if (c > b) {
        func_020a94a4((UnkStruct_0206bf78 *) a);
        func_020a9354((UnkStruct_0206bf78 *) a, b);
        a->unk_30 = c;
        a->unk_34 = 0;
        a->unk_39 = (unsigned char) d;
        a->unk_38 = 0;
        a->unk_2C = 2;
    }
}

void func_0206bf08(struct UnkStruct_0206bf08 *obj)
{
    int v = obj->unk_2C;
    if (v == 1) {
        obj->unk_38 = 1;
        func_020a92d8(obj, 0);
    } else if (v == 2) {
        obj->unk_38 = 1;
        func_020a92d8(obj, obj->unk_30);
    }
}

int func_0206bef8(void *r0)
{
    if (*(unsigned int *) ((char *) r0 + 0x2c) == 0) {
        return 1;
    } else {
        return 0;
    }
}

void func_0206bef4(void) {}

void func_0206bee0(void *ptr)
{
    if (*(int *) ((char *) ptr + 0x2c) == 2) {
        func_0206be6c((struct UnkStruct_0206be6c *) ptr);
    }
}

void func_0206be94(UnkStruct_0206be94 *s, int arg)
{
    if (*(unsigned char *) ((char *) s + 0x39)) {
        func_0206c234(s->unk_28, arg);
    }
    s->unk_38 = 0;
    if (s->unk_2C == 1) {
        s->unk_34--;
        if (s->unk_34 <= 0) {
            func_0206be6c((struct UnkStruct_0206be6c *) s);
        }
    } else if (s->unk_2C == 2) {
        func_02068104(s->unk_24, arg);
    }
}

void func_0206be90(void) {}

unsigned char func_0206be88(UnkStruct_0206be88 *p)
{
    return p->unk_38;
}

void func_0206be6c(struct UnkStruct_0206be6c *s)
{
    s->unk_2C = 0;
    s->unk_30 = 0;
    s->unk_34 = 0;
    s->unk_38 = 0;
    s->unk_39 = 0;
    func_020a94a4((UnkStruct_0206bf78 *) s);
}
