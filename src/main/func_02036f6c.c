/* func_02036f6c @ 0x02036f6c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020da2e4[];

typedef struct {
    void *ptr;
    int value;
    unsigned short arr[5];
    unsigned char flags[4];
} UnkStruct_02036f6c;

void func_02036f6c(UnkStruct_02036f6c *self, int value)
{
    self->ptr = data_020da2e4;
    self->value = value;
    self->arr[0] = 0xffff;
    self->arr[1] = 0xffff;
    self->arr[2] = 0xffff;
    self->arr[3] = 0xffff;
    self->arr[4] = 0xffff;
    self->flags[0] = 0;
    self->flags[1] = 0;
    self->flags[2] = 0;
    self->flags[3] = 0;
}
