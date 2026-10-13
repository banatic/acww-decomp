/* func_020b5418 @ 0x020b5418, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a9484(void);
extern void func_020a8754(void *sub);
extern char data_020e3e68;
extern char data_020e5278;

typedef struct {
    volatile unsigned int vtbl;
    char pad_04[0x20];
    int unk_24;
    char sub[0x14];
    int unk_3C;
    int unk_40;
    char unk_44;
    char unk_45;
    char unk_46;
    char unk_47;
    char unk_48;
} UnkStruct_020b5418;

UnkStruct_020b5418 *func_020b5418(UnkStruct_020b5418 *self, int param)
{
    func_020a9484();
    self->vtbl = (unsigned int) &data_020e3e68;
    self->vtbl = (unsigned int) &data_020e5278;
    self->unk_24 = param;
    func_020a8754(self->sub);
    self->unk_3C = 0;
    self->unk_40 = 0;
    self->unk_44 = 0;
    self->unk_45 = 1;
    self->unk_46 = 0;
    self->unk_47 = 0;
    self->unk_48 = 0;
    return self;
}
