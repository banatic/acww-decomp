/* func_020f92d0 @ 0x020f92d0, 0x138 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

typedef struct {
    char pad_00[0x15];
    signed char unk_15;
} UnkStruct_020f92d0;

extern void *data_021fd1f8;
extern int func_0210b498(void *p, int i, unsigned char *buf);

void func_020f92d0(UnkStruct_020f92d0 *self)
{
    unsigned char buf[28];
    void *pp;
    int i;

    pp = &data_021fd1f8;
    self->unk_15 = -1;

    for (i = 2; i <= 13; i++) {
        if (func_0210b498(pp, i, buf) == 0) {
            continue;
        }
        if (i == 10) {
            continue;
        }
        if (buf[9] == 0) {
            continue;
        }

        switch (i) {
            case 11:
                self->unk_15 = 0;
                return;
            case 6:
                self->unk_15 = 1;
                return;
            case 3:
            case 9:
                self->unk_15 = 2;
                return;
            case 5:
            case 8:
                self->unk_15 = 3;
                return;
            case 2:
            case 7:
            case 12:
                self->unk_15 = 4;
                return;
            case 4:
            case 13:
                self->unk_15 = 5;
                return;
            case 0:
            case 1:
            case 10:
            default:
                self->unk_15 = 0;
                return;
        }
    }
}
