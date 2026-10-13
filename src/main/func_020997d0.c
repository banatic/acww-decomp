/* func_020997d0 @ 0x020997d0, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x243d];
    unsigned char : 3;
    unsigned char field : 3;
} UnkStruct_020997d0;

unsigned int func_020997d0(UnkStruct_020997d0 *p)
{
    return p->field;
}
