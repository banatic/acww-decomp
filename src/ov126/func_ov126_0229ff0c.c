/* func_ov126_0229ff0c @ 0x0229ff0c, 0x5c bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
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

extern int func_ov126_0229f7c8(UnkStruct_0229ff0c *self, int a);
extern void func_ov002_0220a0b4(void *dst, void *src, int size);
extern int func_ov095_02299b7c(int *p);
extern int func_ov095_02299b38(int *p);

void func_ov126_0229ff0c(UnkStruct_0229ff0c *self)
{
    if (func_ov126_0229f7c8(self, 0x80) != 0) {
        func_ov002_0220a0b4(&self->obj, self->src_ptr, 0x28);
    } else {
        int a = func_ov095_02299b7c(&self->val);
        int b = func_ov095_02299b38(&self->val);
        func_ov002_0220a0b4(&self->obj, (void *) a, b);
    }
    self->obj.vtable->func[3](&self->obj);
}
