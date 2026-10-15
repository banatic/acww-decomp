/* func_ov070_02278a00 @ 0x02278a00, 0x28 bytes, Thumb, module ov070
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov070_022796c0(void *p);
extern void *func_0202ee5c(void *p);
extern char data_ov070_02279e4c[];

typedef struct {
    void *unk_00;
    char pad_04[0x654];
    char sub;
} UnkStruct_02278a00;

void *func_ov070_02278a00(UnkStruct_02278a00 *self)
{
    self->unk_00 = data_ov070_02279e4c;
    func_ov070_022796c0(&self->sub);
    func_0202ee5c(self);
    return self;
}
