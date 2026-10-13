/* func_0209bac0 @ 0x0209bac0, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x2a];
    unsigned char unk_2A;
} UnkStruct_0209bac0;

extern void func_0209baf4(UnkStruct_0209bac0 *a, int b, int c);
extern void func_0209bae4(UnkStruct_0209bac0 *a, int b, int c);

int func_0209bac0(UnkStruct_0209bac0 *a, int b, int c)
{
    func_0209baf4(a, b, c);
    func_0209bae4(a, b, c);
    a->unk_2A = 0;
    return 0;
}
