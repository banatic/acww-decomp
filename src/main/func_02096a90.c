/* func_02096a90 @ 0x02096a90, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020ee660(void *);
extern unsigned int data_020da13c;
extern unsigned int data_020e2f90;

struct UnkStruct_02096a90 {
    volatile unsigned int vtable;
};

struct UnkStruct_02096a90 *func_02096a90(struct UnkStruct_02096a90 *self)
{
    func_020ee660(self);
    self->vtable = (unsigned int) &data_020da13c;
    self->vtable = (unsigned int) &data_020e2f90;
    return self;
}
