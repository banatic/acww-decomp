/* func_020b7fa0 @ 0x020b7fa0, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020b7fa0 {
    unsigned int data[4];
} UnkStruct_020b7fa0;

typedef struct St {
    char pad_00[0x3c];
    unsigned int unk_3C;
    unsigned char unk_40;
} St;

extern int func_0202fc5c(UnkStruct_020b7fa0 *local);
extern int func_0202fc18(St *arg0, int arg1, int arg2, int arg3, UnkStruct_020b7fa0 *local);

int func_020b7fa0(St *arg0, int arg1, int arg2, int arg3, int arg4, unsigned char arg5)
{
    UnkStruct_020b7fa0 local;
    if (func_0202fc5c(&local)) {
        arg0->unk_3C = arg4;
        arg0->unk_40 = arg5;
        return func_0202fc18(arg0, arg1, arg2, arg3, &local);
    }
    return 0;
}
