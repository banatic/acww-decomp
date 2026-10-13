/* func_020b33b8 @ 0x020b33b8, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char data[0x40];
} UnkStruct_020b33b8;

extern void func_020b35d8(void *);
extern void func_020b3550(void *);
extern void func_020b364c(void *);
extern void func_020b373c(void *);

UnkStruct_020b33b8 *func_020b33b8(UnkStruct_020b33b8 *self)
{
    func_020b35d8(&self->data[0x34]);
    func_020b3550(&self->data[0x18]);
    func_020b364c(&self->data[0x14]);
    func_020b373c(self);
    return self;
}
