/* func_02089b50 @ 0x02089b50, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *vtable;
} UnkStruct_02089b50;

extern void *func_0208a088(UnkStruct_02089b50 *self);
extern char data_020e2030[];

UnkStruct_02089b50 *func_02089b50(UnkStruct_02089b50 *self)
{
    func_0208a088(self);
    self->vtable = (void *) &data_020e2030;
    return self;
}
