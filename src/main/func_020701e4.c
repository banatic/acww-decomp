/* func_020701e4 @ 0x020701e4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020e8ce0(void *global, void *param);
extern void func_0206ff24(unsigned char byte);
extern unsigned int data_021cfca0;

typedef struct UnkStruct_020701e4 {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned char *unk_08;
} UnkStruct_020701e4;

void func_020701e4(UnkStruct_020701e4 *param)
{
    func_020e8ce0(&data_021cfca0, param);
    func_0206ff24(*(param->unk_08 + 0x90));
}
