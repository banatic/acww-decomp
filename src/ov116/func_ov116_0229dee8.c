/* func_ov116_0229dee8 @ 0x0229dee8, 0x66 bytes, Thumb, module ov116
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x94];
    void *sub;
    unsigned char pad_98[0x60];
    void *obj;
} UnkStruct_0229dee8;

extern void func_ov114_0229c3ac(void *);
extern int func_ov116_0229dedc(void *);
extern int func_ov116_0229ded0(void *);
extern void func_ov002_0220a0b4(void *, int, int);
extern int func_ov114_0229c60c(void *);
extern int func_ov114_0229c5f4(void *);
extern void func_ov002_0220a374(void *, int);
extern void func_ov116_0229de10(void *);

void func_ov116_0229dee8(UnkStruct_0229dee8 *self)
{
    int r5;
    int r2;

    func_ov114_0229c3ac(&self->obj);
    r5 = func_ov116_0229dedc(self);
    r2 = func_ov116_0229ded0(self);
    func_ov002_0220a0b4(&self->sub, r5, r2);
    if (func_ov114_0229c60c(&self->obj) != -1 || func_ov114_0229c5f4(&self->obj) != 0) {
        func_ov002_0220a374(&self->sub, 0xd);
    } else {
        func_ov002_0220a374(&self->sub, 1);
    }
    func_ov116_0229de10(self);
}
