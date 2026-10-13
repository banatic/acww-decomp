/* func_0201063c @ 0x0201063c, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0205d25c(void *p);
extern int func_0203cfa8(int a);
extern void func_020b9d3c(void *p, int b, void *c, int d, int e, int f);
extern int data_020d8408;

typedef struct {
    char pad_00[0x290];
    int unk_290;
    char pad_294[0x774 - 0x294];
    int unk_774;
    int unk_778;
} my_struct;

void func_0201063c(my_struct *self)
{
    int val = self->unk_290;
    func_020b9d3c(&self->unk_778, val, &data_020d8408, func_0203cfa8(func_0205d25c(&self->unk_774)), 0, 0);
}
