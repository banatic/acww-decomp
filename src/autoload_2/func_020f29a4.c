/* func_020f29a4 @ 0x020f29a4, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020f45c4(void *);
extern unsigned char data_0213ee48;

struct UnkStruct_020f29a4 {
    unsigned char *data;
    unsigned char flag;
};

struct UnkStruct_020f29a4 *func_020f29a4(struct UnkStruct_020f29a4 *self)
{
    func_020f45c4(self);
    self->data = &data_0213ee48;
    self->flag = 0x30;
    return self;
}
