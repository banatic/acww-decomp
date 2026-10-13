/* func_0208a088 @ 0x0208a088, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *unk_00;
} UnkStruct_0208a088;

extern char data_020e201c;
extern void func_02089fe4(void *ptr);

UnkStruct_0208a088 *func_0208a088(UnkStruct_0208a088 *self)
{
    self->unk_00 = (void *) &data_020e201c;
    func_02089fe4(self);
    return self;
}
