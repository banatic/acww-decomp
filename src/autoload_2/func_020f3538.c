/* func_020f3538 @ 0x020f3538, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f45c4(void *p);
extern char data_0213eb70;

typedef struct {
    void *unk_00;
    unsigned char unk_04;
} UnkStruct_020f3538;

UnkStruct_020f3538 *func_020f3538(UnkStruct_020f3538 *self)
{
    func_020f45c4(self);
    self->unk_00 = &data_0213eb70;
    self->unk_04 = 30;
    return self;
}
