/* heap_16: 2 functions, module autoload_2
 * mwccarm 1.2/base -O4,p
 * func_020ea5c4 @ 0x020ea5c4, 0x70 bytes, ARM
 * func_020ea584 @ 0x020ea584, 0x40 bytes, ARM
 */

typedef struct {
    int unk_00;
    int unk_04;
} ThreadInfo;

extern void OS_SetThreadParameter(void *thread, unsigned int param);
extern unsigned int OS_GetThreadParameter(void *thread);
extern unsigned int data_021fbe94;
extern void (*data_021fbe88)(void *, void *);
extern ThreadInfo OSi_ThreadInfo;
extern int func_020e9a08(int param);

void func_020ea5c4(void *a, void *b)
{
    OS_SetThreadParameter(a, data_021fbe94);
    data_021fbe94 = OS_GetThreadParameter(b);
    OS_SetThreadParameter(b, 0);
    if (data_021fbe88) {
        data_021fbe88(a, b);
    }
}

void func_020ea584(int a, int b)
{
    if (a == OSi_ThreadInfo.unk_04) {
        func_020e9a08(b);
    } else {
        OS_SetThreadParameter((void *) a, b);
    }
}
