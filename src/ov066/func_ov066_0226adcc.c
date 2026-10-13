/* func_ov066_0226adcc @ 0x0226adcc, 0x50 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

typedef struct {
    char pad_00[2];
    unsigned short flag;
    char pad_04[0x1c];
    void (*callback)(void *self);
} UnkStruct_0226adcc;

extern int func_ov066_0226686c(int value);
extern void OS_Terminate(int value);

void func_ov066_0226adcc(UnkStruct_0226adcc *obj)
{
    if (obj->flag == 0) {
        if (obj->callback != 0) {
            obj->callback(obj);
        }
        return;
    } else {
        OS_Terminate(func_ov066_0226686c(obj->flag));
    }
}
