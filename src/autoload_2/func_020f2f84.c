/* func_020f2f84 @ 0x020f2f84, 0x34 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *vtbl;
    char kind;
    int member;
} UnkStruct_020f2f84;

extern void func_020f45c4(UnkStruct_020f2f84 *self);
extern void func_020f9624(int *member);
extern int data_0213ecdc;

UnkStruct_020f2f84 *func_020f2f84(UnkStruct_020f2f84 *self)
{
    func_020f45c4(self);
    self->vtbl = &data_0213ecdc;
    func_020f9624(&self->member);
    self->kind = 0x29;
    return self;
}
