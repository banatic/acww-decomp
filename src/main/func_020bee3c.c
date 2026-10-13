/* func_020bee3c @ 0x020bee3c, 0xe bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    int unk_04;
} UnkStruct_020bee3c;

void func_020bee3c(UnkStruct_020bee3c *p)
{
    int tmp;
    tmp = p->unk_04 - 1;
    p->unk_04 = tmp > 0 ? tmp : 0;
}
