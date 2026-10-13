/* func_02083228 @ 0x02083228, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020e1b00;
extern void func_02083ca8(void *, int);
extern void __arm func_02138d6c(void *, int, int, void (*)(void), void (*)(void));
extern void func_020832ac(void);
extern void func_02083294(void);

typedef struct {
    int *unk_00;
    int unk_04;
    int unk_08;
} SelfType;

SelfType *func_02083228(SelfType *self)
{
    func_02083ca8(self, 5);
    self->unk_00 = &data_020e1b00;
    func_02138d6c(&self->unk_08, 5, 0x6c, func_020832ac, func_02083294);
    return self;
}
