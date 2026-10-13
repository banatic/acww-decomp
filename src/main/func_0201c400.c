/* func_0201c400 @ 0x0201c400, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xEA];
    volatile unsigned short unk_EA;
} UnkStruct_0201c400;

extern void func_0201c438(UnkStruct_0201c400 *a, unsigned short b);
extern int func_0201c444(UnkStruct_0201c400 *a);
extern void func_0203efb0(UnkStruct_0201c400 *a, int b);

void func_0201c400(UnkStruct_0201c400 *a, unsigned short *b)
{
    a->unk_EA = *b;
    func_0201c438(a, (unsigned short) (a->unk_EA & 0x0FFF));
    func_0203efb0(a, func_0201c444(a));
}
