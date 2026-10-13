/* func_ov050_02260448 @ 0x02260448, 0x2c bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov050_022636b0(void *p);
extern void func_0202ee5c(void *p);
extern void func_020edf54(void *p);
extern char data_ov050_02265a60;

typedef struct {
    void *vt;
    char pad_04[0x654];
    int unk_658;
} UnkStruct_02260448;

void *func_ov050_02260448(UnkStruct_02260448 *self)
{
    self->vt = (void *) &data_ov050_02265a60;
    func_ov050_022636b0(&self->unk_658);
    func_0202ee5c(self);
    func_020edf54(self);
    return self;
}
