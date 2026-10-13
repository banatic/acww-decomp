/* func_020bc42c @ 0x020bc42c, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b6840(int param);
extern void func_020bda88(int arg);
extern void func_020bd3b4(int arg);

typedef struct {
    char pad_00[0x24];
    int unk_24;
    char pad_28[0x0C];
    int unk_34;
} UnkStruct_020bc42c;

extern UnkStruct_020bc42c data_021f8ab0;

void func_020bc42c(int arg)
{
    int result;
    result = func_020b6840(0);
    if (result == 0 || result == 3) {
        return;
    }
    if (data_021f8ab0.unk_34 == 1 && data_021f8ab0.unk_24 == 4) {
        func_020bda88(arg);
    }
    func_020bd3b4(arg);
}
