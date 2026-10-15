/* func_020f36ac @ 0x020f36ac, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern char data_0213eb08;
extern void *func_020f4514(void *p);

typedef struct {
    void *unk_00;
} UnkStruct_020f36ac;

void *func_020f36ac(UnkStruct_020f36ac *self)
{
    self->unk_00 = &data_0213eb08;
    func_020f4514(self);
    return self;
}
