/* func_020835dc @ 0x020835dc, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e1ac8;
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void func_02083c78(void *ptr);
extern void *func_02083654(void *);

typedef struct {
    void *unk_00;
    int unk_04;
    char data[1];
} UnkStruct_020835dc;

void *func_020835dc(UnkStruct_020835dc *param)
{
    param->unk_00 = &data_020e1ac8;
    __cxa_vec_cleanup((void *) (&param->data[0]), 5, 8, (((void (*)(void *)) func_02083654)));
    func_02083c78(param);
    return param;
}
