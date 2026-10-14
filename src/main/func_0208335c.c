/* func_0208335c @ 0x0208335c, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e1b38;
extern void func_020833d4(void);
extern void func_02083c78(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void));

typedef struct {
    char *unk_00;
    unsigned int pad_04;
    void *unk_08;
} UnkStruct_0208335c;

void *func_0208335c(UnkStruct_0208335c *param)
{
    param->unk_00 = &data_020e1b38;
    __cxa_vec_cleanup(&param->unk_08, 5, 2, func_020833d4);
    func_02083c78(param);
    return param;
}
