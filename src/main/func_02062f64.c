/* func_02062f64 @ 0x02062f64, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int *vtable;
} UnkStruct_02062f64;

extern void func_020a8cac(UnkStruct_02062f64 *self, int arg);
extern void func_020a8c1c(UnkStruct_02062f64 *self);
extern void func_02062e80(UnkStruct_02062f64 *self, int arg);
extern int data_020de62c;

UnkStruct_02062f64 *func_02062f64(UnkStruct_02062f64 *self, int arg)
{
    func_020a8cac(self, arg);
    self->vtable = &data_020de62c;
    func_020a8c1c(self);
    func_02062e80(self, arg);
    return self;
}
