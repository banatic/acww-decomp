/* func_02035ac8 @ 0x02035ac8, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020356c4(int, int, int, int);
extern void func_02035ae8(void);
extern void func_02035c08(void);

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned short unk_08;
} UnkStruct_02035ac8;

void func_02035ac8(UnkStruct_02035ac8 *p)
{
    p->unk_08 = 0x41;
    func_020356c4(0xB, 0x41, 0x7F, 1);
    func_02035ae8();
    func_02035c08();
}
