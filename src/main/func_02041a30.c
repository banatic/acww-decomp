/* func_02041a30 @ 0x02041a30, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020669e0(void *);
extern char data_020db71c[];
extern char data_020da13c[];

typedef struct {
    void *vtable;
    char pad_04[0x50];
    char unk_54;
} UnkStruct_02041a30;

void *func_02041a30(UnkStruct_02041a30 *self)
{
    self->vtable = data_020db71c;
    func_020669e0(&self->unk_54);
    self->vtable = data_020da13c;
    func_020ee62c(self);
    return self;
}
