/* func_02035dcc @ 0x02035dcc, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021f42f4;
extern int func_02095f90(void);
extern void func_02035e7c(void);
extern void func_02035864(void);
extern int func_02035e68(void);
extern int func_02035e54(void);
extern void func_02036894(int, int);
extern void func_02036784(int, int);

typedef struct {
    char pad_00[8];
    unsigned char unk_08;
    unsigned char unk_09;
    unsigned char unk_0A;
    int unk_0C;
} UnkStruct_02035dcc;

void func_02035dcc(UnkStruct_02035dcc *self)
{
    if (*(unsigned short *) ((char *) data_021f42f4 + 0xc) == 5) {
        return;
    }

    if (self->unk_0C < 0) {
        int x = func_02095f90();
        if (x == 0x3c) {
            // do nothing
        } else if (x == 0x8b) {
            self->unk_0C = 0x21;
        } else if (x == 0x8e) {
            self->unk_0C = 0x21;
        } else if (x == 0x43) {
            self->unk_0C = 0x21;
        } else if (x == 0x44) {
            self->unk_0C = 0x21;
        } else if (x == 0x02) {
            self->unk_0C = 0x19;
        } else {
            self->unk_0C = 0x14;
        }
    }

    if (self->unk_09 != 0) {
        func_02035e7c();
        func_02035864();
    }

    self->unk_08 = 0;
    self->unk_09 = 0;
    self->unk_0A = 0;

    func_02036894(func_02035e68(), 0);
    func_02036784(func_02035e54(), 0);
}
