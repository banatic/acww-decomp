/* sound_system_9: 2 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020f1d84 @ 0x020f1d84, 0x20 bytes, ARM
 * func_020f1d3c @ 0x020f1d3c, 0x48 bytes, ARM
 */

typedef struct {
    unsigned char pad_00[0x54];
    volatile unsigned int unk_54;
    unsigned int unk_58;
    unsigned int unk_5C;
} UnkStruct_020f1d3c;

extern int func_020eef70(void);
extern int func_0210e198(int, int);

int func_020f1d84(int a, int b)
{
    int r0;
    r0 = func_020eef70();
    return func_0210e198(b, r0);
}

unsigned int func_020f1d3c(UnkStruct_020f1d3c *self, unsigned int arg)
{
    self->unk_54 = self->unk_5C + self->unk_58 * self->unk_54;
    if (arg == 0) {
        return (self->unk_54 >> 16) << 16 >> 16;
    } else {
        return (((self->unk_54 >> 16) * arg) >> 16) << 16 >> 16;
    }
}
