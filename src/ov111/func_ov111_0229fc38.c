/* func_ov111_0229fc38 @ 0x0229fc38, 0x64 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x9e];
    char unk_9E;
    char pad_9F[0x0d];
    char unk_AC;
    char pad_AD[0x3c69];
    char unk_3D16;
} UnkStruct_0229fc38;

extern int func_ov111_0229f4dc(UnkStruct_0229fc38 *self);
extern void func_ov111_0229fb48(UnkStruct_0229fc38 *self);
extern void func_ov095_0229b3ec(void *p);
extern int func_ov095_0229bcec(void *a, void *b, int c, void *d, int e, int f, int g, int h);
extern void func_ov111_0229f524(UnkStruct_0229fc38 *self);
extern void func_ov111_0229fd08(UnkStruct_0229fc38 *self);

int func_ov111_0229fc38(UnkStruct_0229fc38 *self, int param)
{
    if (func_ov111_0229f4dc(self)) {
        func_ov111_0229fb48(self);
        func_ov095_0229b3ec(&self->unk_AC);
    }
    if (func_ov095_0229bcec(&self->unk_AC, &self->unk_3D16, param, &self->unk_9E, 0x10, 0xa0, 0, 1)) {
        func_ov111_0229f524(self);
        func_ov111_0229fd08(self);
    } else {
        return 0;
    }
    return 1;
}
