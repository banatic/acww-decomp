/* func_ov003_0221cf8c @ 0x0221cf8c, 0x34 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020565b0(void *ptr);
extern void *func_ov009_0226539c(void *self);

typedef struct {
    void *unk_00;
    char pad_04[0xe8];
    void *unk_EC;
    char pad_F0[0x1c4];
    char unk_2B4;
} UnkStruct_0221cf8c;

extern unsigned char data_ov003_02238c54[];
extern unsigned char data_ov003_02238d18[];

void *func_ov003_0221cf8c(void *self)
{
    UnkStruct_0221cf8c *s = self;
    s->unk_00 = (void *) data_ov003_02238c54;
    s->unk_EC = (void *) data_ov003_02238d18;
    func_020565b0(&s->unk_2B4);
    func_ov009_0226539c(s);
    return s;
}
