/* func_0209bb48 @ 0x0209bb48, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209bd80(void *);
extern void *func_0209529c(void *);

typedef struct {
    char pad_00[0x0C];
    char sub[0x20];
    unsigned short unk_2C;
} UnkStruct_0209bb48;

UnkStruct_0209bb48 *func_0209bb48(UnkStruct_0209bb48 *arg)
{
    func_0209bd80(arg);
    func_0209529c(arg->sub);
    arg->unk_2C = 0xFFF1;
    return arg;
}
