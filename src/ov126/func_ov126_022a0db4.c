/* func_ov126_022a0db4 @ 0x022a0db4, 0x5c bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40;

typedef struct {
    unsigned char pad_00[0x19c];
    unsigned char sub;
} Obj_ov126_022a20c8;

extern void func_ov126_0229fec0(void *);
extern int func_ov095_0229bf0c(void *);
extern void *func_ov095_0229c548(void *);
extern void *func_ov095_0229c448(void *, void *, int);
extern int func_ov126_022a03dc(void *, void *);
extern void func_ov095_0229c8e4(void *, void *);

void func_ov126_022a0db4(Obj_ov126_022a20c8 *self)
{
    void *r4;
    void *ret;

    if (!(data_021fbe40 & 1)) {
        func_ov126_0229fec0(self);
    } else {
        if (func_ov095_0229bf0c(&self->sub) == 0) {
            return;
        }
        r4 = func_ov095_0229c548(&self->sub);
        ret = func_ov095_0229c448(&self->sub, r4, 9);
        func_ov126_022a03dc(self, ret);
        func_ov095_0229c8e4(&self->sub, r4);
    }
}
