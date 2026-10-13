/* func_0207385c @ 0x0207385c, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Func0207385cStruct {
    unsigned char pad_00[0xCC];
    int unk_CC;
} Func0207385cStruct;

extern void func_02073854(Func0207385cStruct *self, int arg2);
extern int func_02073884(Func0207385cStruct *self);

void func_0207385c(Func0207385cStruct *self)
{
    func_02073854(self, 0);
    self->unk_CC = func_02073884(self);
}
