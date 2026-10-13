/* func_0208dcd4 @ 0x0208dcd4, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x24];
    volatile int unk_24;
} UnkStruct_0208dcd4;

extern int func_0208db3c(UnkStruct_0208dcd4 *param);
extern void func_0208dc88(UnkStruct_0208dcd4 *param);

void func_0208dcd4(UnkStruct_0208dcd4 *param)
{
    if (func_0208db3c(param)) {
        param->unk_24--;
        if (param->unk_24 > 0) {
            return;
        }
        func_0208dc88(param);
    }
}
