/* func_02078460 @ 0x02078460, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020778b0(void *a, unsigned short b, void *c);

typedef struct {
    unsigned short pad_00;
    unsigned char unk_02;
} UnkStruct_02078460;

void func_02078460(UnkStruct_02078460 *a, unsigned char b, unsigned short *c)
{
    unsigned short val = *c;
    func_020778b0(a, val, c);
    a->unk_02 = b;
}
