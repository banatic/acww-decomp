/* func_02052dc0 @ 0x02052dc0, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    int unk_04;
} UnkStruct_02052dc0;

extern unsigned int func_02052e20(UnkStruct_02052dc0 *self);
extern void **data_020dcfe0[];
extern unsigned int data_021c8744;
extern unsigned short data_021c8748[2];

void *func_02052dc0(UnkStruct_02052dc0 *self, unsigned int param1)
{
    if (self->unk_00 < 3 && param1 < func_02052e20(self)) {
        return &((void **) (data_020dcfe0[self->unk_00][self->unk_04]))[param1 & 3];
    }
    if ((data_021c8744 & 1) == 0) {
        data_021c8748[0] = 0;
        data_021c8748[1] = 0;
        data_021c8744 |= 1;
    }
    return data_021c8748;
}
