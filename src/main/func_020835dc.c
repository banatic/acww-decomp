/* func_020835dc @ 0x020835dc, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e1ac8;
extern void func_02138c48(void *ptr, int a, int b, void (*cb)(void));
extern void func_02083c78(void *ptr);
extern void func_02083654(void);

typedef struct {
    void *unk_00;
    int unk_04;
    char data[1];
} UnkStruct_020835dc;

void *func_020835dc(UnkStruct_020835dc *param)
{
    param->unk_00 = &data_020e1ac8;
    func_02138c48(&param->data[0], 5, 8, func_02083654);
    func_02083c78(param);
    return param;
}
