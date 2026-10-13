/* func_020aa420 @ 0x020aa420, 0x9e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ab278(void *p);
extern int func_020ab270(void *p);
extern void func_020ac11c(void *p, int a, int b);
extern void *func_020ab344(void *p);
extern void func_020ac1cc(void *p, void *q);
extern int func_020ab338(void *p);
extern int func_020ac240(void *p);
extern void func_020ac1d0(void *p);
extern void func_020ac1c4(void *p);
extern int func_020ac218(void *p);
extern int func_020ac198(void *p, int a);
extern void func_020ac1dc(void *p);
extern void func_020ab2fc(void *p);
extern void func_020aa3f4(void *p);

typedef struct UnkStruct_020aa420 {
    unsigned char pad_00[0xc];
    unsigned char unk_0C;
    unsigned char pad_0D[0x77];
    unsigned char unk_84;
} UnkStruct_020aa420;

void func_020aa420(UnkStruct_020aa420 *self)
{
    int cond;
    int k;
    void *q;

    func_020ab278(&self->unk_84);
    cond = (func_020ab270(&self->unk_84) == 0) ? 1 : 0;
    func_020ac11c(&self->unk_0C, cond, 1);
    q = func_020ab344(&self->unk_84);
    func_020ac1cc(&self->unk_0C, q);
    k = func_020ab338(&self->unk_84);
    if (k < 0) {
        return;
    }
    if (func_020ac240(&self->unk_0C) != 0) {
        func_020ac1d0(&self->unk_0C);
        func_020ac1c4(&self->unk_0C);
        return;
    }
    if (func_020ac218(&self->unk_0C) != 0) {
        if (func_020ac198(&self->unk_0C, k) != 0) {
            func_020ac1dc(&self->unk_0C);
            func_020ab2fc(&self->unk_84);
            func_020aa3f4(self);
        }
    }
}
