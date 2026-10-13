/* func_0206db30 @ 0x0206db30, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *vtbl;
} UnkStruct_0206db30;

extern void func_020a887c(UnkStruct_0206db30 *self);
extern void func_020edb3c(UnkStruct_0206db30 *self);

extern unsigned char data_020df270[];

UnkStruct_0206db30 *func_0206db30(UnkStruct_0206db30 *self)
{
    self->vtbl = (void *) data_020df270;
    func_020a887c(self);
    func_020edb3c(self);
    return self;
}
