/* func_020f3794 @ 0x020f3794, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020f45c4(void *self);
extern char data_0213ead4[];

struct object_020f3794 {
    void *unk_00;
    char unk_04;
};

struct object_020f3794 *func_020f3794(struct object_020f3794 *self)
{
    func_020f45c4(self);
    self->unk_00 = data_0213ead4;
    self->unk_04 = 0x16;
    return self;
}
