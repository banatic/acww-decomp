/* func_0201cf74 @ 0x0201cf74, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0201cf90(int a0, int a1, int a2, unsigned char a3, unsigned char a4, unsigned int a5);

typedef struct {
    unsigned char unk_00;
    unsigned char unk_01;
} UnkStruct_0201cf74;

void func_0201cf74(int a0, int a1, int a2, UnkStruct_0201cf74 *a3, unsigned int a4)
{
    func_0201cf90(a0, a1, a2, a3->unk_00, a3->unk_01, a4);
}
