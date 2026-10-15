/* func_020f302c @ 0x020f302c, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern char data_0213eca8;
extern void *func_020f4514(void *self);

struct S_t {
    void *unk_00;
};

void *func_020f302c(void *self)
{
    ((struct S_t *) self)->unk_00 = &data_0213eca8;
    func_020f4514(self);
    return self;
}
