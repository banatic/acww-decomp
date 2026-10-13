/* func_02050b94 @ 0x02050b94, 0x46 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int CARD_IsAvailable(int *out, int arg2);
extern void CARD_Init(void);
extern int OS_GetLockID(void);
extern void func_0211ec44(unsigned short);
extern int func_0211f23c(int);
extern int CARD_GetBackupTotalSize(int);
extern void func_0211ec34(unsigned short);
extern void OS_ReleaseLockID(unsigned short);

void func_02050b94(int *out, int arg2)
{
    int r;

    if (CARD_IsAvailable(out, arg2) == 0) {
        CARD_Init();
    }
    r = OS_GetLockID();
    func_0211ec44((unsigned short) r);
    *out = CARD_GetBackupTotalSize(func_0211f23c(arg2));
    func_0211ec34((unsigned short) r);
    OS_ReleaseLockID((unsigned short) r);
    ((unsigned char *) out)[8] = 4;
}
