/* func_ov048_02260448 @ 0x02260448, 0x2c bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov048_02264298;
extern void *func_ov048_022626f0(void *);
extern void *func_0202ee5c(void *);
extern void func_020edf54(void *);

typedef struct {
    void *unk_00;
    unsigned char pad_04[0x654];
    unsigned char unk_658;
} UnkStruct_02260448;

void *func_ov048_02260448(UnkStruct_02260448 *self)
{
    self->unk_00 = &data_ov048_02264298;
    func_ov048_022626f0(&self->unk_658);
    func_0202ee5c(self);
    func_020edf54(self);
    return self;
}
