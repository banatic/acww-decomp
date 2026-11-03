/* keyboard_entry_input_2: 4 functions, module ov126
 * mwccarm 1.2/base -O4,s
 * func_ov126_0229ff68 @ 0x0229ff68, 0x74 bytes, Thumb
 * func_ov126_0229ff0c @ 0x0229ff0c, 0x5c bytes, Thumb
 * func_ov126_0229feec @ 0x0229feec, 0x20 bytes, Thumb
 * func_ov126_0229fec0 @ 0x0229fec0, 0x2c bytes, Thumb
 */

typedef struct Vtable {
    void (*func[4])(void *);
} Vtable;

typedef struct UnkStruct_0229ff0c_2 {
    Vtable *vtable;
} UnkStruct_0229ff0c_2;

typedef struct {
    char pad_00[0x98];
    void *src_ptr;
    char pad_9C[0x100];
    int val;
    char pad_1A0[0x3df0];
    UnkStruct_0229ff0c_2 obj;
} UnkStruct_0229ff0c;

extern int func_ov126_0229f7c8(void *p, int a);
extern void func_ov002_0220a000(void *p, int a, int b, int c, int d);
extern int func_ov095_02299b7c(void *p);
extern int func_ov095_02299b38(void *p);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov002_0220a0b4(void *dst, void *src, int size);
extern void func_ov002_0220a1dc(void *);
extern void func_ov095_0229cce0(void *);
extern void func_ov002_0220a164(void *);

void func_ov126_0229ff68(void *param)
{
    if (func_ov126_0229f7c8(param, 0x80)) {
        func_ov002_0220a000((char *) param + 0x3f90, *(int *) ((char *) param + 0x98), 0x28, 3, 2);
        *(char *) ((char *) param + 0xae) = 6;
    } else {
        int a, b;
        a = func_ov095_02299b7c((char *) param + 0x19c);
        b = func_ov095_02299b38((char *) param + 0x19c);
        func_ov002_0220a000((char *) param + 0x3f90, a, b, 3, 2);
        *(char *) ((char *) param + 0xae) = 4;
    }
    func_ov002_02208098((void *) (param), 8);
}

void func_ov126_0229ff0c(UnkStruct_0229ff0c *self)
{
    if (func_ov126_0229f7c8((void *) self, 0x80) != 0) {
        func_ov002_0220a0b4(&self->obj, self->src_ptr, 0x28);
    } else {
        int a = func_ov095_02299b7c((void *) (&self->val));
        int b = func_ov095_02299b38((void *) (&self->val));
        func_ov002_0220a0b4(&self->obj, (void *) a, b);
    }
    self->obj.vtable->func[3](&self->obj);
}

void func_ov126_0229feec(void *self)
{
    func_ov002_0220a1dc((char *) self + 0x3f90);
    func_ov002_02208098((void *) (self), 9);
}

void func_ov126_0229fec0(void *self)
{
    func_ov095_0229cce0((char *) self + 0x19c);
    func_ov002_0220a164((char *) self + 0x3f90);
    func_ov002_02208098((void *) (self), 0xb);
}
