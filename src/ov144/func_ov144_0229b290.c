/* func_ov144_0229b290 @ 0x0229b290, 0x8c bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_02207f80(unsigned int size);
extern void func_ov002_0220830c(void *ptr);
extern void func_ov002_02209ccc(void *ptr);
extern void func_ov002_0220a5fc(void *ptr);
extern void func_ov002_0220b008(void *ptr);
extern void __cxa_vec_ctor(void *ptr, int a, int b, void *c, void *d);
extern void func_020b9cfc(void *ptr);
extern void func_ov002_0220ba24(void *ptr);

extern char data_ov144_0229b3f8[];
void func_02070c08(void);
void func_02070be8(void);

typedef struct {
    char data[0x24];
} Elem;

typedef struct {
    void *vtable;
    char pad_04[0xc4 - 4];
    char obj_c4[0x128 - 0xc4];
    char obj_128[0x170 - 0x128];
    char obj_170[0x33c - 0x170];
    char obj_33c[0x708 - 0x33c];
    Elem arr[2];
} MyObj;

void *func_ov144_0229b290(void)
{
    void *obj;
    MyObj *self;
    Elem *p, *end;

    obj = func_ov002_02207f80(0x210c);
    if (obj) {
        self = (MyObj *) obj;
        func_ov002_0220830c(obj);
        self->vtable = data_ov144_0229b3f8;
        func_ov002_02209ccc(&self->obj_c4);
        func_ov002_0220a5fc(&self->obj_128);
        func_ov002_0220b008(&self->obj_170);
        __cxa_vec_ctor(&self->obj_33c, 9, 0x6c, func_02070c08, func_02070be8);
        p = self->arr;
        end = &self->arr[2];
        do {
            func_020b9cfc(p);
            p++;
        } while (p != end);
        func_ov002_0220ba24(end);
    }
    return obj;
}
