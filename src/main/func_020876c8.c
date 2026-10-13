/* func_020876c8 @ 0x020876c8, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644b4(int param);

typedef struct {
    char pad_00[8];
    short unk_08;
    unsigned char unk_0A;
} UnkStruct_020876c8;

int func_020876c8(UnkStruct_020876c8 *ptr)
{
    int y;
    int x;
    y = func_020644b4(0x419a);
    x = ptr->unk_0A;
    y += 0x2000;
    x = x * y;
    ptr->unk_08 = (short) (x >> 12);
    return 0;
}
