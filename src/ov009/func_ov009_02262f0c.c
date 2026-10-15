/* func_ov009_02262f0c @ 0x02262f0c, 0x1e bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern int func_020044a0(void *);

typedef struct {
    unsigned char pad_00[0x40];
    unsigned char flag;
} UnkStruct_02262f0c;

void func_ov009_02262f0c(UnkStruct_02262f0c *self)
{
    if (self->flag) {
        func_020044a0(self);
        self->flag = 0;
    }
}
