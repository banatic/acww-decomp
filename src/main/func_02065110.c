/* func_02065110 @ 0x02065110, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int type;
    char pad_04[0xC];
    short unk_10;
    short unk_12;
} UnkStruct_02065110;

extern void func_020ea78c(int, int);
extern void func_020ea6e0(int, int);
extern int func_020651b0(UnkStruct_02065110 *p);

void func_02065110(UnkStruct_02065110 *self, int other)
{
    switch (self->type) {
        case 0:
        case 1:
        case 2:
            func_020ea78c(other, self->unk_10);
            func_020ea6e0(other, func_020651b0(self));
            break;
        default:
            func_020ea78c(other, self->unk_10);
            func_020ea6e0(other, self->unk_12);
            break;
    }
}
