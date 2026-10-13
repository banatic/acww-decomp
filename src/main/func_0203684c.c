/* func_0203684c @ 0x0203684c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *vtable;
} UnkStruct_0203684c;

extern void func_020edb3c(UnkStruct_0203684c *);
extern char data_020da2f4[];

UnkStruct_0203684c *func_0203684c(UnkStruct_0203684c *self)
{
    self->vtable = data_020da2f4;
    func_020edb3c(self);
    return self;
}
