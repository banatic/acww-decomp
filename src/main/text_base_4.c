/* text_base_4: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a8cac @ 0x020a8cac, 0x28 bytes, Thumb
 * func_020a8c88 @ 0x020a8c88, 0x24 bytes, Thumb
 * func_020a8c5c @ 0x020a8c5c, 0x2c bytes, Thumb
 * func_020a8c38 @ 0x020a8c38, 0x24 bytes, Thumb
 * func_020a8c1c @ 0x020a8c1c, 0x1a bytes, Thumb
 * func_020a8be4 @ 0x020a8be4, 0x38 bytes, Thumb
 */

typedef struct {
    void *unk_00;
    int pad_04;
    int unk_08;
} UnkStruct_020a8c88;

struct SomeObject {
    void *vtable;
    int unk_04;
    char unk_08;
};

extern void func_020a9b50(void *arg);
extern unsigned char data_020da6dc[];
extern unsigned char data_020e3d94[];
extern void func_020a9b44(void *);
extern void func_020edb3c(void *ptr);
extern void func_02051ad8(void *);
extern void func_020a9b04(void *);
extern int data_021f450c;
extern void func_020a8d20(void *, int, int, int, int);
extern int func_020a922c(void *, int);
extern int func_020a8d08(void *);
extern void func_020a8d10(void *);

void *func_020a8cac(void *arg)
{
    volatile unsigned int *p = (volatile unsigned int *) arg;
    p[0] = (unsigned int) data_020da6dc;
    p[0] = (unsigned int) data_020e3d94;
    p[1] = 0;
    func_020a9b50((char *) arg + 8);
    return arg;
}

UnkStruct_020a8c88 *func_020a8c88(UnkStruct_020a8c88 *obj)
{
    obj->unk_00 = ((char *) data_020e3d94);
    func_020a9b44(&obj->unk_08);
    obj->unk_00 = ((char *) data_020da6dc);
    return obj;
}

void *func_020a8c5c(void *obj)
{
    char *self = (char *) obj;
    *(void **) self = ((char *) data_020e3d94);
    func_020a9b44(self + 8);
    *(void **) self = ((char *) data_020da6dc);
    func_020edb3c(self);
    return obj;
}

struct SomeObject *func_020a8c38(struct SomeObject *this)
{
    this->vtable = (void *) ((int *) data_020e3d94);
    func_020a9b44(&this->unk_08);
    this->vtable = (void *) ((int *) data_020da6dc);
    return this;
}

void func_020a8c1c(void *arg0)
{
    void *r4;
    r4 = arg0;
    func_02051ad8(r4);
    *(unsigned int *) ((char *) r4 + 4) = 0;
    func_020a9b04((char *) r4 + 8);
}

int func_020a8be4(int arg1, int arg2)
{
    int ret;
    func_020a8d20(&data_021f450c, arg1, arg2, 0, 0);
    func_020a922c(&data_021f450c, 0);
    ret = func_020a8d08(&data_021f450c);
    func_020a8d10(&data_021f450c);
    return ret;
}
