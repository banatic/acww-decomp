/* func_020ef874 @ 0x020ef874, 0x48 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void OS_Terminate(void);

typedef struct {
    char pad_00[0x34];
    unsigned short unk_34;
} Func020ef874Struct;

void func_020ef874(Func020ef874Struct *obj, int bit, int enable)
{
    if (obj == 0) {
        OS_Terminate();
    }
    if (enable == 1) {
        obj->unk_34 |= (1 << bit);
    } else {
        obj->unk_34 &= ~(1 << bit);
    }
}
