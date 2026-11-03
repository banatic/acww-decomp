/* message_cursor: 19 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b4c24 @ 0x020b4c24, 0x4 bytes, Thumb
 * func_020b4c0c @ 0x020b4c0c, 0x16 bytes, Thumb
 * func_020b4bf0 @ 0x020b4bf0, 0x1a bytes, Thumb
 * func_020b4bd4 @ 0x020b4bd4, 0x1a bytes, Thumb
 * func_020b4bb4 @ 0x020b4bb4, 0x20 bytes, Thumb
 * func_020b4bb0 @ 0x020b4bb0, 0x2 bytes, Thumb
 * func_020b4ba0 @ 0x020b4ba0, 0x10 bytes, Thumb
 * func_020b4b48 @ 0x020b4b48, 0x58 bytes, Thumb
 * func_020b4b44 @ 0x020b4b44, 0x2 bytes, Thumb
 * func_020b4b24 @ 0x020b4b24, 0x20 bytes, Thumb
 * func_020b4afc @ 0x020b4afc, 0x28 bytes, Thumb
 * func_020b4ad4 @ 0x020b4ad4, 0x28 bytes, Thumb
 * func_020b4ab4 @ 0x020b4ab4, 0x20 bytes, Thumb
 * func_020b4a8c @ 0x020b4a8c, 0x28 bytes, Thumb
 * func_020b4a88 @ 0x020b4a88, 0x2 bytes, Thumb
 * func_020b4a84 @ 0x020b4a84, 0x2 bytes, Thumb
 * func_020b4a78 @ 0x020b4a78, 0xa bytes, Thumb
 * func_020b4a74 @ 0x020b4a74, 0x2 bytes, Thumb
 * func_020b4a64 @ 0x020b4a64, 0xe bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x24];
    int unk_24;
    unsigned char pad_28[0x14];
    int unk_3C;
} UnkStruct_020b4bf0;

typedef struct UnkStruct_020b4bd4 {
    unsigned char pad_00[0x24];
    unsigned int unk_24;
    unsigned char pad_28[0x14];
    unsigned int unk_3C;
} UnkStruct_020b4bd4;

typedef struct {
    char pad_00[0x24];
    int unk_24;
    char pad_28[0x10];
    int unk_38;
    int unk_3C;
} UnkStruct_020b4bb4;

struct UnkStruct_020b4b48 {
    unsigned char pad_00[0x24];
    int unk_24;
    unsigned char pad_28[0x10];
    int unk_38;
    int unk_3C;
};

struct UnkStruct_020b4afc {
    char pad_00[0x2c];
    void *unk_2C;
};

typedef struct UnkStruct_020b4ad4 {
    void *unk_00;
    unsigned char pad_04[0x20];
    unsigned int unk_24;
    unsigned int unk_28;
    unsigned int unk_2C;
} UnkStruct_020b4ad4;

struct UnkStruct_020b4a8c {
    volatile void *unk_00;
};

typedef struct {
    unsigned char pad_00[0x28];
    int unk_28;
    int unk_2C;
} UnkStruct_020b4a78;

extern void func_020a94a4(void *p);
extern void func_020a9354(void *p, void *q);
extern int func_020a92d8(void *ptr, int arg);
extern char *func_02137550(void *dest, unsigned int size);
extern int func_020a89f8(void *ptr, void *data);
extern void *func_020a9484(void *obj);
extern void *func_020a941c(void *);
extern unsigned char data_020e3e68[];
extern unsigned char data_020e5230[];
extern void func_020edb3c(struct UnkStruct_020b4a8c *this);

void func_020b4afc(struct UnkStruct_020b4afc *s, int value);

void func_020b4c24(int *p0, int p1)
{
    p0[11] = p1;
}

void func_020b4c0c(void *p)
{
    func_020a94a4(p);
    func_020a9354(p, *(void **) ((char *) p + 0x30));
}

void func_020b4bf0(UnkStruct_020b4bf0 *ptr, int value)
{
    ptr->unk_24 = 2;
    ptr->unk_3C = value;
    func_020a92d8(ptr, 0);
    ptr->unk_24 = 0;
}

void func_020b4bd4(UnkStruct_020b4bd4 *p)
{
    p->unk_24 = 1;
    p->unk_3C = 1;
    func_020a92d8((void *) p, 0);
    p->unk_24 = 0;
}

int func_020b4bb4(UnkStruct_020b4bb4 *p)
{
    p->unk_24 = 3;
    p->unk_3C = 1;
    p->unk_38 = 0;
    func_020a92d8(p, 0);
    p->unk_24 = 0;
    return p->unk_38;
}

void func_020b4bb0(void) {}

void func_020b4ba0(void *arg0)
{
    unsigned int val;
    unsigned char *puVar2;

    val = *(unsigned int *) ((char *) arg0 + 0x24);
    if (val - 1 <= 1) {
        puVar2 = (unsigned char *) ((char *) arg0 + 0x34);
        *puVar2 = 1;
    }
    return;
}

void func_020b4b48(struct UnkStruct_020b4b48 *self, int arg)
{
    int state;
    self->unk_38 = arg;
    state = self->unk_24;
    if (state == 1) {
        func_020b4afc((struct UnkStruct_020b4afc *) self, arg);
        if (arg != 10) {
            self->unk_3C--;
        }
    } else if (state == 2) {
        if (arg == 10) {
            func_020b4afc((struct UnkStruct_020b4afc *) self, 10);
        } else {
            func_020b4afc((struct UnkStruct_020b4afc *) self, 0x3000);
            self->unk_3C--;
        }
    } else if (state == 3) {
        if (arg != 10) {
            self->unk_3C--;
        }
    }
}

void func_020b4b44(void) {}

int func_020b4b24(void *arg0)
{
    int val;
    int val2;
    int val3;

    val = *(int *) ((char *) arg0 + 0x3c);
    if (val > 0) {
        val2 = 1;
    } else {
        val2 = 0;
    }
    val3 = *(int *) ((char *) arg0 + 0x24) - 1;
    if ((unsigned int) val3 <= 1 && val2 == 0) {
        *(int *) ((char *) arg0 + 0x30) = *(int *) ((char *) arg0 + 4);
    }
    return val2;
}

void func_020b4afc(struct UnkStruct_020b4afc *s, int value)
{
    unsigned char buf[4];
    func_02137550(buf, 4);
    buf[0] = (unsigned char) value;
    buf[1] = (unsigned char) (value >> 8);
    func_020a89f8(s->unk_2C, buf);
}

UnkStruct_020b4ad4 *func_020b4ad4(UnkStruct_020b4ad4 *obj)
{
    func_020a9484(obj);
    obj->unk_00 = (void *) ((char *) data_020e3e68);
    obj->unk_00 = (void *) ((char *) data_020e5230);
    obj->unk_24 = 0;
    obj->unk_28 = 0;
    obj->unk_2C = 0;
    return obj;
}

void *func_020b4ab4(void *p)
{
    volatile unsigned int *vp;
    vp = (volatile unsigned int *) p;
    *vp = (unsigned int) (unsigned int) data_020e5230;
    *vp = (unsigned int) (unsigned int) data_020e3e68;
    func_020a941c(p);
    return p;
}

struct UnkStruct_020b4a8c *func_020b4a8c(struct UnkStruct_020b4a8c *this)
{
    this->unk_00 = (void *) data_020e5230;
    this->unk_00 = (void *) data_020e3e68;
    func_020a941c((void *) this);
    func_020edb3c(this);
    return this;
}

void func_020b4a88(void) {}

void func_020b4a84(void) {}

void func_020b4a78(UnkStruct_020b4a78 *p, int v)
{
    p->unk_2C = v;
    p->unk_28 = p->unk_28 - 1;
}

void func_020b4a74(void) {}

int func_020b4a64(void *self)
{
    if (*(int *) ((char *) self + 0x28) > 0) {
        return 1;
    }
    return 0;
}
