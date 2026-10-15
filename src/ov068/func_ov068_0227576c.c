/* func_ov068_0227576c @ 0x0227576c, 0xa0 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0227576c UnkStruct_0227576c;
struct UnkStruct_0227576c {
    unsigned char pad_00[0x618];
    unsigned char unk_618;
    unsigned char pad_619[0xa58 - 0x619];
    unsigned char unk_A58;
    unsigned char unk_A59;
    unsigned char pad_A5A[0xa5c - 0xa5a];
    unsigned char unk_A5C;
    unsigned char pad_A5D[0xa5e - 0xa5d];
    short unk_A5E;
    unsigned char unk_A60;
};

extern int func_02014868(void *);
extern int func_0203e0a8(void *, int);
extern unsigned int *func_02095794(int);
extern int func_02030818(void *);

void func_ov068_0227576c(UnkStruct_0227576c *self)
{
    if (func_02014868(&self->unk_618) == 0) {
        if (!(self->unk_A5E != 0 && self->unk_A5C != 0)) {
            unsigned char tmp = self->unk_A60;
            if (tmp == 0) {
                func_0203e0a8(self, 0);
                self->unk_A58 = 1;
                return;
            }
            if (tmp != 0) {
                tmp--;
                self->unk_A60 = tmp;
            }
        }
        if (self->unk_A5E > 0) {
            self->unk_A5E--;
        }
    }
    {
        unsigned int *data = func_02095794(4);
        if (data != 0) {
            unsigned int buf[3];
            buf[0] = data[0];
            buf[1] = data[1];
            buf[2] = data[2];
            if (func_02030818(buf) != 0) {
                func_0203e0a8(self, 0);
                self->unk_A59 = 1;
            }
        }
    }
}
