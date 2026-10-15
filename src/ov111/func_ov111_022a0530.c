/* func_ov111_022a0530 @ 0x022a0530, 0x80 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_022a0530 {
    unsigned char pad_00[0xac];
    unsigned char unk_AC[1];
    unsigned char pad_AD[0x3d38 - 0xac - 1];
    unsigned char unk_3D38;
} UnkStruct_022a0530;

extern int func_0208e484(void *);
extern void *func_ov095_02299a00(void *);
extern int func_ov095_0229c448(void *, void *, int);
extern int func_ov111_0229f730(void *, int);
extern void func_ov095_0229bf3c(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov095_0229c8e4(void *, void *);
extern void func_ov095_0229cce0(void *);
extern void func_ov111_0229f0cc(void *);

extern unsigned short data_021fbe40;

void func_ov111_022a0530(UnkStruct_022a0530 *self)
{
    void *ptr;
    int val;

    if (func_0208e484(&self->unk_3D38) == 0) {
        return;
    }

    ptr = func_ov095_02299a00(&self->unk_AC);
    val = func_ov111_0229f730(self, func_ov095_0229c448(&self->unk_AC, ptr, 9));

    if (val == 3) {
        return;
    }
    if (val == 1) {
        if (data_021fbe40 & 1) {
            func_ov095_0229bf3c(&self->unk_AC);
            func_ov002_02208098((void *) (self), 6);
            self = (UnkStruct_022a0530 *) ((char *) self + 0xac);
            func_ov095_0229c8e4(self, ptr);
            return;
        }
    }
    func_ov095_0229cce0(&self->unk_AC);
    if (val != 4) {
        func_ov111_0229f0cc(self);
    }
}
