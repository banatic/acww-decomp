/* func_020f3da0 @ 0x020f3da0, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020f3f14(void *self);
extern char data_0213e99c;

typedef struct {
    void *unk_00;
} Unk_020f3da0;

void *func_020f3da0(Unk_020f3da0 *self)
{
    self->unk_00 = &data_0213e99c;
    func_020f3f14(self);
    return self;
}
