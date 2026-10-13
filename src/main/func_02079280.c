/* func_02079280 @ 0x02079280, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x1D];
    unsigned char unk_1D;
    unsigned char pad_1E[0x0E];
} UnkStruct_02079280;

extern UnkStruct_02079280 *func_02079350(void);

void func_02079280(void)
{
    UnkStruct_02079280 *p;
    int i;
    p = func_02079350();
    for (i = 0; i < 8; i++) {
        p->unk_1D &= ~1;
        p++;
    }
}
