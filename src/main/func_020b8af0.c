/* func_020b8af0 @ 0x020b8af0, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

extern unsigned char data_020e54a8;
extern int func_020960f8(int, int);
extern void *func_020953e4(void);

typedef struct UnkStruct_020b8af0 {
    unsigned short first;
} UnkStruct_020b8af0;

typedef struct UnkStruct_020b8af0_2 {
    unsigned char pad_00[0xf4];
    UnkStruct_020b8af0 *unk_F4;
    unsigned short unk_F8;
} UnkStruct_020b8af0_2;

void func_020b8af0(UnkStruct_020b8af0_2 *self)
{
    void *p;
    int val;
    int flag;

    p = 0;
    if (func_020960f8(2, 4) != 0) {
        p = func_020953e4();
    }

    if (p != 0) {
        val = *(unsigned short *) p & 0xf000;
        val >>= 12;
        flag = (data_020e54a8 == 0) ? 1 : 0;
        if (flag != 0) {
            if (val == 1 || val == 3 || val == 4) {
                // keep p
            } else {
                p = 0;
            }
        } else {
            if (val == 1) {
                // keep p
            } else {
                p = 0;
            }
        }
    }

    if (self->unk_F4 != 0) {
        self->unk_F8 = self->unk_F4->first;
    } else {
        self->unk_F8 = 0xfff1;
    }
    self->unk_F4 = (UnkStruct_020b8af0 *) p;
}
