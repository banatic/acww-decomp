/* func_0206d594 @ 0x0206d594, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *unk_00;
    char pad_04[44];
    void *unk_30;
} UnkStruct_0206d594;

extern void func_020a8fb8(void *);
extern void *func_020a9260(UnkStruct_0206d594 *);
extern void func_020edb3c(UnkStruct_0206d594 *);
extern char data_020def7c;

UnkStruct_0206d594 *func_0206d594(UnkStruct_0206d594 *self)
{
    self->unk_00 = &data_020def7c;
    if (self->unk_30) {
        func_020a8fb8(self->unk_30);
    }
    func_020a9260(self);
    func_020edb3c(self);
    return self;
}
