/* func_02070ba4 @ 0x02070ba4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *unk_00;
} UnkStruct_02070ba4;
extern void func_02070b84(void *self);
extern void *func_020a8c38(void *self);
extern int data_020e179c;
UnkStruct_02070ba4 *func_02070ba4(UnkStruct_02070ba4 *self)
{
    self->unk_00 = &data_020e179c;
    func_02070b84(self);
    func_020a8c38(self);
    return self;
}
