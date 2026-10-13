/* func_020bc9c4 @ 0x020bc9c4, 0xbc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_020644cc(unsigned int);

extern unsigned char data_020d2315[];
extern unsigned char data_020d2378[];

typedef struct {
    unsigned char pad_00[0x2f2c];
    unsigned int unk_2F2C;
    unsigned char pad_2F30[4];
    unsigned int unk_2F34;
    unsigned int unk_2F38;
    unsigned int unk_2F3C;
    unsigned int unk_2F40;
    unsigned int unk_2F44;
} UnkStruct_020bc9c4;

void func_020bc9c4(UnkStruct_020bc9c4 *self, int flag)
{
    unsigned char *p;
    unsigned int ret;
    int result;
    int i;
    int idx;
    int v;
    int skip;
    int j;

    if (flag == 0x14) {
        ret = func_020644cc(0x64);
        p = data_020d2315;
        result = 5;
        for (i = 1; i < 14; i++, p++) {
            if (ret < *p) {
                result = i;
                break;
            }
        }
        self->unk_2F2C = result;
    } else {
        self->unk_2F2C = flag;
    }

    idx = self->unk_2F2C;
    v = data_020d2378[idx];
    if (v > 0) {
        skip = 0;
        j = idx - 1;
        if ((unsigned) j <= 18) {
            if ((1 << j) & 0x4c007) {
                skip = 1;
            }
        }
        if (skip) {
            self->unk_2F34 = func_020644cc(v);
        } else {
            self->unk_2F38 = func_020644cc(v);
            self->unk_2F3C = func_020644cc(v);
            self->unk_2F40 = func_020644cc(v);
            self->unk_2F44 = func_020644cc(v);
        }
    }
}
