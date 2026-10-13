/* func_020aaa54 @ 0x020aaa54, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x2c];
    int unk_2C;
} UnkStruct_020aaa54;

extern int func_020a7fd4(void);

int func_020aaa54(UnkStruct_020aaa54 *p)
{
    return p->unk_2C == 0 && func_020a7fd4() != 0;
}
