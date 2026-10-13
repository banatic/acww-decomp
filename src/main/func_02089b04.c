/* func_02089b04 @ 0x02089b04, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b7f88(void *self);

typedef struct UnkStruct_02089b04 {
    char pad_00[0x1c];
    int unk_1C;
    char unk_20;
} UnkStruct_02089b04;

void *func_02089b04(UnkStruct_02089b04 *self)
{
    func_020b7f88(self);
    self->unk_1C = 0;
    self->unk_20 = 0;
    return self;
}
