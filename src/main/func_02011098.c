/* func_02011098 @ 0x02011098, 0x6 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[140];
    unsigned short unk_8C;
} UnkStruct_02011098;
void func_02011098(UnkStruct_02011098 *p, unsigned short v)
{
    p->unk_8C = v;
}
