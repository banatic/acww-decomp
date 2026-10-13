/* func_ov066_0226760c @ 0x0226760c, 0x30 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,s
 */

typedef struct Node {
    int unk_00;
    int value;
} Node;

extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern Node *data_ov066_0226bdec;

int func_ov066_0226760c(void)
{
    int result = 0;
    int state = OS_DisableInterrupts();

    if (data_ov066_0226bdec != 0) {
        result = data_ov066_0226bdec->value;
    }
    OS_RestoreInterrupts(state);
    return result;
}
