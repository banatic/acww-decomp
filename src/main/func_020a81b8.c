/* func_020a81b8 @ 0x020a81b8, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e3d4c[];
extern unsigned char data_021f43ec;

void MI_CpuFill8(void *, int, unsigned int);

struct UnkStruct_020a81b8 {
    char *ptr;
    char unk_04[26];
    unsigned char byte;
};

struct UnkStruct_020a81b8 *func_020a81b8(struct UnkStruct_020a81b8 *self)
{
    self->ptr = data_020e3d4c;
    self->byte = data_021f43ec;
    MI_CpuFill8(self->unk_04, 0, 26);
    return self;
}
