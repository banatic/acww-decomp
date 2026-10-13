/* func_02062f90 @ 0x02062f90, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *unk_00;
} UnkStruct_02062f90;

extern void func_020a8cac(void *self, void *arg);
extern void func_020a8c1c(void *self);
extern void func_02062ea4(void *self, void *arg);
extern char data_020de62c;

void *func_02062f90(UnkStruct_02062f90 *self, void *arg)
{
    func_020a8cac(self, arg);
    self->unk_00 = &data_020de62c;
    func_020a8c1c(self);
    func_02062ea4(self, arg);
    return self;
}
