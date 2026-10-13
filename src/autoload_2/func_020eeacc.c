/* func_020eeacc @ 0x020eeacc, 0x38 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[4];
    short flag;
} UnkStruct_020eeacc;

extern int func_020eeb04(UnkStruct_020eeacc *self, int value);

int func_020eeacc(UnkStruct_020eeacc *self)
{
    if (self->flag == 1) {
        self->flag = func_020eeb04(self, 0);
    }
    if (self->flag == 1) {
        return 0;
    } else {
        return 1;
    }
}
