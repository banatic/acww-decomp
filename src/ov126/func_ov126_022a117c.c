/* func_ov126_022a117c @ 0x022a117c, 0x5c bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_ov095_0229bf0c(void *p);
extern int func_ov095_0229c548(void *p);
extern int func_ov095_0229c448(void *p, int a, int b);
extern void func_ov095_0229c8e4(void *p, int a);
extern int func_ov126_022a03dc(void *p, int arg);

typedef struct {
    unsigned char pad_00[0x19c];
    int unk_19C;
} UnkStruct_022a117c;

void func_ov126_022a117c(UnkStruct_022a117c *self)
{
    if (data_021fbdd8 == 0) {
        func_ov002_02208098((void *) (self), 0);
    } else {
        if (func_ov095_0229bf0c((void *) &self->unk_19C) != 0) {
            int ret;
            int tmp;
            ret = func_ov095_0229c548((void *) &self->unk_19C);
            tmp = func_ov095_0229c448((void *) &self->unk_19C, ret, 9);
            func_ov126_022a03dc(self, tmp);
            func_ov095_0229c8e4((void *) &self->unk_19C, ret);
        }
    }
}
