/* func_020ea584 @ 0x020ea584, 0x40 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

typedef struct {
    int unk_00;
    int unk_04;
} ThreadInfo;
extern ThreadInfo OSi_ThreadInfo;
extern void func_020e9a08(int param);
extern void OS_SetThreadParameter(int thread, int param);

void func_020ea584(int a, int b)
{
    if (a == OSi_ThreadInfo.unk_04) {
        func_020e9a08(b);
    } else {
        OS_SetThreadParameter(a, b);
    }
}
