/* func_0202eb20 @ 0x0202eb20, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020d9ff8;
extern void func_0201615c(void *);

struct UnkStruct_0202eb20 {
    void *p;
};

void *func_0202eb20(struct UnkStruct_0202eb20 *self)
{
    self->p = &data_020d9ff8;
    func_0201615c(self);
    return self;
}
