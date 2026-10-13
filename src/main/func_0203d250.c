/* func_0203d250 @ 0x0203d250, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char unk_00;
    unsigned char unused0 : 2;
    unsigned char flag : 1;
} UnkStruct_0203d250;

int func_0203d250(const UnkStruct_0203d250 *s)
{
    if (s->flag) {
        return 1;
    } else {
        return 0;
    }
}
