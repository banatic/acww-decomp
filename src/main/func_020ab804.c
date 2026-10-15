/* func_020ab804 @ 0x020ab804, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f43ec;
extern void *func_020ab8dc(unsigned char *p);
extern int func_020a82e8(unsigned char *p);
extern void func_020ab79c(void *p);

typedef struct {
    unsigned char unk_00;
    unsigned char pad_01[7];
    unsigned char unk_08[92];
    unsigned char unk_64[12];
    unsigned char unk_70;
} UnkStruct_020ab804;

UnkStruct_020ab804 *func_020ab804(UnkStruct_020ab804 *self)
{
    self->unk_00 = data_021f43ec;
    func_020ab8dc(self->unk_08);
    func_020a82e8(self->unk_64);
    self->unk_70 = data_021f43ec;
    func_020ab79c(self);
    return self;
}
