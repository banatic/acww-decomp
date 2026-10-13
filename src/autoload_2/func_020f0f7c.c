/* func_020f0f7c @ 0x020f0f7c, 0x34 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

typedef struct {
    unsigned char data[0x70];
    unsigned char flag;
} UnkStruct_020f0f7c;

extern void func_020f12cc(UnkStruct_020f0f7c *self, int arg);

void func_020f0f7c(UnkStruct_020f0f7c *self, unsigned char value)
{
    if (self->flag == value) {
        return;
    }
    self->flag = value;
    func_020f12cc(self, 1);
}
