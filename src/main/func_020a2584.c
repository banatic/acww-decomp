/* func_020a2584 @ 0x020a2584, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *vtbl;
} UnkStruct_020a2584;

extern void *func_02066a30(UnkStruct_020a2584 *self);
extern char data_020e3b38;

UnkStruct_020a2584 *func_020a2584(UnkStruct_020a2584 *self)
{
    func_02066a30(self);
    self->vtbl = &data_020e3b38;
    return self;
}
