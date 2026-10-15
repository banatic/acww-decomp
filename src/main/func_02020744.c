/* func_02020744 @ 0x02020744, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    int unk_04;
} UnkStruct_02020744;

extern int func_02015590(void *param, int arg);
extern void func_0202dbf0(void *param, UnkStruct_02020744 s);
extern UnkStruct_02020744 data_020d9218;

void func_02020744(void *param, void *out)
{
    func_02015590(param, 3);
    func_0202dbf0(param, data_020d9218);
}
