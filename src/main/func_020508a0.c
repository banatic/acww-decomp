/* func_020508a0 @ 0x020508a0, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a;
    int b;
} UnkStruct_020508a0;
extern UnkStruct_020508a0 data_021c8188;
extern int func_02050974(UnkStruct_020508a0 *p);
extern int OS_GetTick(void);
extern void CARD_CancelBackupAsync(void);
extern int func_0211f230(void);
extern void func_0211ec34(unsigned short h);
extern void OS_ReleaseLockID(unsigned short h);
void func_020508a0(void)
{
    int t;
    if (func_02050974(&data_021c8188) == 3) {
        t = OS_GetTick();
        CARD_CancelBackupAsync();
        while (func_0211f230() == 0 && (unsigned int) (OS_GetTick() - t) < 0xcc8d)
            ;
        if (data_021c8188.b != -3) {
            func_0211ec34((unsigned short) data_021c8188.b);
            OS_ReleaseLockID((unsigned short) data_021c8188.b);
        }
    }
}
