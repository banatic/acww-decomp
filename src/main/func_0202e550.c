/* func_0202e550 @ 0x0202e550, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208150c(void *p);
extern int func_02003704(void);
extern int func_02003648(void);

typedef struct {
    unsigned char pad_00[0x830];
    void *unk_830;
} UnkStruct_0202e550;

int func_0202e550(UnkStruct_0202e550 *param)
{
    int result = -1;
    if (param->unk_830 != 0) {
        func_0208150c(param->unk_830);
        if (func_02003704() == 1) {
            func_0208150c(param->unk_830);
            result = func_02003648();
        }
    }
    return result;
}
