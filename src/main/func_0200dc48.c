/* func_0200dc48 @ 0x0200dc48, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0200dc48 {
    unsigned char pad_00[0x170];
    int unk_170;
} UnkStruct_0200dc48;

extern short func_0200dc80(UnkStruct_0200dc48 *arg);
extern int func_0203c568(void);
extern int data_021c67a4;

short func_0200dc48(UnkStruct_0200dc48 *arg0)
{
    short r4;
    r4 = func_0200dc80(arg0);
    if (arg0->unk_170 != 2 && data_021c67a4 != 0) {
        r4 = (short) (r4 + func_0203c568());
    }
    return r4;
}
