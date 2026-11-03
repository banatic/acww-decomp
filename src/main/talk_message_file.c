/* talk_message_file: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206d688 @ 0x0206d688, 0x1c bytes, Thumb
 * func_0206d670 @ 0x0206d670, 0x18 bytes, Thumb
 * func_0206d650 @ 0x0206d650, 0x20 bytes, Thumb
 * func_0206d63c @ 0x0206d63c, 0x14 bytes, Thumb
 * func_0206d638 @ 0x0206d638, 0x4 bytes, Thumb
 * func_0206d630 @ 0x0206d630, 0x8 bytes, Thumb
 */

struct UnkStruct_0206d688 {
    void *unk_00;
};

typedef struct Vtbl Vtbl;

typedef struct Object Object;

struct Object {
    Vtbl *vtable;
};

extern void *func_020a9a90(void *obj, int arg);
extern int data_020def64;
extern void *func_020a9a40(void *obj);
extern void func_020edb3c(Object *this);
extern void MI_CpuFill8(void *param1, int param2, int param3);

struct UnkStruct_0206d688 *func_0206d688(struct UnkStruct_0206d688 *obj)
{
    func_020a9a90(obj, 1);
    obj->unk_00 = &data_020def64;
    return obj;
}

void *func_0206d670(void *obj)
{
    *(void **) obj = ((char *) &data_020def64);
    func_020a9a40(obj);
    return obj;
}

Object *func_0206d650(Object *this)
{
    this->vtable = ((Vtbl *) &data_020def64);
    func_020a9a40((void *) this);
    func_020edb3c(this);
    return this;
}

void func_0206d63c(void *param0)
{
    MI_CpuFill8((char *) param0 + 0xa4, 0, 0x800);
}

int func_0206d638(int p0)
{
    return ((int) (p0) + (164));
}

int func_0206d630(void)
{
    return 2048;
}
