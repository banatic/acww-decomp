/* func_02038a50 @ 0x02038a50, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02038c54(void *);
extern void *func_02038cb4(void *);
extern void *func_02038d18(void *);
extern void *func_02055764(void *);
extern void func_020edb3c(void *);
extern unsigned char data_020da520[];

typedef struct UnkStruct_02038a50 {
    void *unk_00;
    unsigned char unk_04[0xe4];
    unsigned char unk_E8[0x114];
    unsigned char unk_1FC[0x54];
    unsigned char unk_250[1];
} UnkStruct_02038a50;

UnkStruct_02038a50 *func_02038a50(UnkStruct_02038a50 *self)
{
    self->unk_00 = (void *) data_020da520;
    func_02038c54(self->unk_250);
    func_02038cb4(self->unk_1FC);
    func_02038d18(self->unk_E8);
    func_02055764(self->unk_04);
    func_020edb3c(self);
    return self;
}
