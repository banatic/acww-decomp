/* message_receiver: 12 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a8228 @ 0x020a8228, 0x20 bytes, Thumb
 * func_020a8210 @ 0x020a8210, 0x18 bytes, Thumb
 * func_020a81f0 @ 0x020a81f0, 0x20 bytes, Thumb
 * func_020a81ec @ 0x020a81ec, 0x4 bytes, Thumb
 * func_020a81e8 @ 0x020a81e8, 0x4 bytes, Thumb
 * func_020a81e0 @ 0x020a81e0, 0x8 bytes, Thumb
 * func_020a81b8 @ 0x020a81b8, 0x28 bytes, Thumb
 * func_020a81ac @ 0x020a81ac, 0xc bytes, Thumb
 * func_020a8194 @ 0x020a8194, 0x18 bytes, Thumb
 * func_020a8188 @ 0x020a8188, 0xc bytes, Thumb
 * func_020a8170 @ 0x020a8170, 0x18 bytes, Thumb
 * func_020a8164 @ 0x020a8164, 0xc bytes, Thumb
 */

struct UnkStruct_020a8228 {
    void *vtable;
};

struct UnkStruct_020a81f0 {
    char *unk_00;
};

struct UnkStruct_020a81b8 {
    char *ptr;
    char unk_04[26];
    unsigned char byte;
};

struct UnkStruct_020a8194 {
    void *vtable;
};

extern void *func_020a8cac(void *self);
extern char data_020e3d64;
extern void *func_020a8c38(void *param);
extern void func_020edb3c(void *);
extern void func_020a8c1c(void *);
extern char data_020e3d4c[];
extern unsigned char data_021f43ec;
void MI_CpuFill8(void *, int, unsigned int);
extern char *strncpy(int, int, int);

void func_020a81e0(void *argument0);

struct UnkStruct_020a8228 *func_020a8228(struct UnkStruct_020a8228 *self)
{
    func_020a8cac(self);
    self->vtable = &data_020e3d64;
    func_020a81e0(self);
    return self;
}

void *func_020a8210(void *param)
{
    *(void **) param = (void *) &data_020e3d64;
    func_020a8c38(param);
    return param;
}

struct UnkStruct_020a81f0 *func_020a81f0(struct UnkStruct_020a81f0 *self)
{
    self->unk_00 = &data_020e3d64;
    func_020a8c38(self);
    func_020edb3c(self);
    return self;
}

int func_020a81ec(void)
{
    return 72;
}

int func_020a81e8(int p0)
{
    return ((int) (p0) + (18));
}

void func_020a81e0(void *argument0)
{
    func_020a8c1c((void *) argument0);
}

struct UnkStruct_020a81b8 *func_020a81b8(struct UnkStruct_020a81b8 *self)
{
    self->ptr = data_020e3d4c;
    self->byte = data_021f43ec;
    MI_CpuFill8(self->unk_04, 0, 26);
    return self;
}

void func_020a81ac(char **ptr)
{
    *ptr = ((char *) data_020e3d4c);
}

struct UnkStruct_020a8194 *func_020a8194(struct UnkStruct_020a8194 *obj)
{
    obj->vtable = (void *) ((unsigned char *) data_020e3d4c);
    func_020edb3c((void *) obj);
    return obj;
}

void func_020a8188(unsigned int **arg0)
{
    *arg0 = ((unsigned int *) data_020e3d4c);
}

void func_020a8170(void *arg0)
{
    unsigned char val;
    val = data_021f43ec;
    *(unsigned char *) ((char *) arg0 + 0x1e) = val;
    MI_CpuFill8((char *) arg0 + 4, 0, 0x1a);
}

void func_020a8164(int a, int b)
{
    strncpy(a + 4, b, 25);
}
