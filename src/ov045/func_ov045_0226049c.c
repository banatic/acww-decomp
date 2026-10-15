/* func_ov045_0226049c @ 0x0226049c, 0x18 bytes, Thumb, module ov045
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a887c(void *self);
extern int data_ov045_0226142c;

typedef struct {
    void *p;
} UnkStruct_0226049c;

UnkStruct_0226049c *func_ov045_0226049c(UnkStruct_0226049c *self)
{
    self->p = &data_ov045_0226142c;
    func_020a887c(self);
    return self;
}
