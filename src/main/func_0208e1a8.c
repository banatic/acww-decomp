/* func_0208e1a8 @ 0x0208e1a8, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208e19c(void *self);

typedef struct {
    char pad_00[0x74];
    int unk_74;
} UnkStruct_0208e1a8;

void func_0208e1a8(UnkStruct_0208e1a8 *self)
{
    if (self->unk_74 == 0) {
        func_0208e19c(self);
    }
}
