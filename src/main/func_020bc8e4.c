/* func_020bc8e4 @ 0x020bc8e4, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x2f30];
    int unk_2F30;
} UnkStruct_020bc8e4;

extern void func_020bca80(UnkStruct_020bc8e4 *, int, int, int);
extern void func_020bc9c4(UnkStruct_020bc8e4 *, int);
extern void func_020bcc70(UnkStruct_020bc8e4 *);

void func_020bc8e4(UnkStruct_020bc8e4 *arg)
{
    int field = arg->unk_2F30;
    if (field < 0) {
        func_020bca80(arg, 0x32, 0x64, 0x190);
    } else if (field == 0) {
        func_020bc9c4(arg, 0x14);
    }
    func_020bcc70(arg);
}
