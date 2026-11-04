/* sound_12: 7 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020efc50 @ 0x020efc50, 0x24 bytes, ARM
 * func_020efc44 @ 0x020efc44, 0xc bytes, ARM
 * func_020efc38 @ 0x020efc38, 0xc bytes, ARM
 * func_020efc2c @ 0x020efc2c, 0xc bytes, ARM
 * func_020efc20 @ 0x020efc20, 0xc bytes, ARM
 * func_020efc18 @ 0x020efc18, 0x8 bytes, ARM
 * func_020efc10 @ 0x020efc10, 0x8 bytes, ARM
 */

typedef struct UnkStruct_020efc10 {
    unsigned char pad_00[4];
    int unk_04;
} UnkStruct_020efc10;

extern void OS_Terminate(void);
extern void NNS_FndAppendListObject(void *list, void *object);
extern void NNS_FndRemoveListObject(void *list, void *object);
extern void *NNS_FndGetNextListObject(void *list, void *object);
extern void *NNS_FndGetPrevListObject(void *list, void *object);

void func_020efc50(void *p)
{
    if (p == 0) {
        OS_Terminate();
    }
    *(int *) p = 0;
    *(int *) ((char *) p + 4) = 0;
}

void func_020efc44(void *list, void *object)
{
    NNS_FndAppendListObject(list, object);
}

void func_020efc38(void *list, void *object)
{
    NNS_FndRemoveListObject(list, object);
}

void *func_020efc2c(void *list, void *object)
{
    return NNS_FndGetNextListObject(list, object);
}

void *func_020efc20(void *list, void *object)
{
    return NNS_FndGetPrevListObject(list, object);
}

unsigned long func_020efc18(const unsigned long *p)
{
    return *p;
}

int func_020efc10(UnkStruct_020efc10 *self)
{
    return self->unk_04;
}
