/* message_decoder_6: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b5418 @ 0x020b5418, 0x58 bytes, Thumb
 * func_020b53f8 @ 0x020b53f8, 0x20 bytes, Thumb
 * func_020b53d0 @ 0x020b53d0, 0x28 bytes, Thumb
 */

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

extern void *func_020a9484(void *);
extern void func_020a8754(void *sub);
extern void *func_020a941c(void *self);
extern unsigned char data_020e3e68[];
extern unsigned char data_020e5278[];
extern void func_020edb3c(void *);

UnkStruct_020b5418 *func_020b5418(UnkStruct_020b5418 *self, int param)
{
    func_020a9484(self);
    self->vtbl = (unsigned int) ((char *) data_020e3e68);
    self->vtbl = (unsigned int) ((char *) data_020e5278);
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

void *func_020b53f8(void *self)
{
    *(unsigned int *) self = (unsigned int) data_020e5278;
    *(unsigned int *) self = (unsigned int) data_020e3e68;
    func_020a941c(self);
    return self;
}

void *volatile *func_020b53d0(void *volatile *this)
{
    *this = (void *) data_020e5278;
    *this = (void *) data_020e3e68;
    func_020a941c((void *) this);
    func_020edb3c((void *) this);
    return this;
}
