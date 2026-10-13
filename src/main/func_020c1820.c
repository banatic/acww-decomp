/* func_020c1820 @ 0x020c1820, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e7c60;
extern void func_020c1b6c(void *ptr);
extern void func_0202ee5c(void *ptr);

typedef struct {
    void *unk_00;
    char pad_04[0x654];
    char sub;
} UnkStruct_020c1820;

void *func_020c1820(UnkStruct_020c1820 *param)
{
    param->unk_00 = &data_020e7c60;
    func_020c1b6c(&param->sub);
    func_0202ee5c(param);
    return param;
}
