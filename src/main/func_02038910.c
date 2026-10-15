/* func_02038910 @ 0x02038910, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xc4];
    int unk_C4;
    unsigned char unk_C8;
} UnkStruct_02038910;

typedef struct {
    unsigned char pad_00[0xc];
    unsigned short value;
} OtherStruct;

extern unsigned char data_020e54a8;
extern OtherStruct *data_021f42f4;
extern char data_020da570[];

extern void func_02038424(UnkStruct_02038910 *self);
extern int func_0205556c(void *buf, unsigned int fourcc, void *data);
extern void func_020386c4(UnkStruct_02038910 *self);
extern void func_020382b8(UnkStruct_02038910 *self);
extern void func_020382d4(UnkStruct_02038910 *self);

void func_02038910(UnkStruct_02038910 *self)
{
    int flag1 = 1;
    unsigned int b1;
    unsigned int b2;
    int flag2;

    b1 = (data_020e54a8 == 0) ? 1 : 0;
    if (b1 == 0) {
        b2 = (data_020e54a8 == 1) ? 1 : 0;
        if (b2 == 0) {
            flag1 = 0;
        }
    }
    flag2 = (data_021f42f4->value == 5) ? 1 : 0;
    func_02038424(self);
    if (flag1 != 0 || flag2 != 0) {
        func_0205556c((char *) self + 4, 0x43617557, data_020da570);
        func_020386c4(self);
        self->unk_C4 = 0;
        self->unk_C8 = 0;
        func_020382b8(self);
    } else {
        func_020382d4(self);
    }
}
