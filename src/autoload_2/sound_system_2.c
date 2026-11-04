/* sound_system_2: 2 functions, module autoload_2
 * mwccarm 1.2/base -O4,p
 * func_020f0fb0 @ 0x020f0fb0, 0x40 bytes, ARM
 * func_020f0f7c @ 0x020f0f7c, 0x34 bytes, ARM
 */

typedef struct {
    unsigned char data[0x70];
    unsigned char flag;
} UnkStruct_020f0f7c;

extern void *func_020f5a4c(void);
extern void func_020f5b04(void *coefficients, int value);
extern void func_020f12cc(UnkStruct_020f0f7c *self, int arg);

void func_020f0fb0(unsigned char *p, int arg)
{
    if (p[0x72] != 0) {
        p[0x72] = p[0x72] - 1;
        return;
    } else {
        if (p[0x72] != 0) {
            return;
        }
        func_020f5b04(func_020f5a4c(), arg);
    }
}

void func_020f0f7c(UnkStruct_020f0f7c *self, unsigned char value)
{
    if (self->flag == value) {
        return;
    }
    self->flag = value;
    func_020f12cc(self, 1);
}
