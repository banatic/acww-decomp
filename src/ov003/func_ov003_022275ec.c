/* func_ov003_022275ec @ 0x022275ec, 0x1a bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x10];
    int unk_10;
    int unk_14;
} UnkStruct_022275ec;
void func_020f5958(void *p);
void *func_ov003_022275ec(UnkStruct_022275ec *self)
{
    self->unk_10 = 0;
    self->unk_14 = 0;
    func_020f5958((char *) self + 0x60);
    return self;
}
