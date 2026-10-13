/* func_0208fdc0 @ 0x0208fdc0, 0x8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x13];
    unsigned char unk_13;
    unsigned char pad_14[8];
    int unk_1C;
} UnkStruct_0208fdc0;
void func_0208fdc0(UnkStruct_0208fdc0 *p, int a)
{
    p->unk_13 = 1;
    p->unk_1C = a;
}
