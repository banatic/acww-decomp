/* func_020b947c @ 0x020b947c, 0x110 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_020b95b4(unsigned int size, unsigned int mode);
extern unsigned int func_020b958c(unsigned int size);
extern void OS_Terminate(void);
extern void NNS_GfdInitFrmTexVramManager(int, int);
extern void NNS_GfdInitFrmPlttVramManager(int, int);
extern int GX_GetSizeOfTexPltt(void);
extern int GX_GetBankForTex(void);

extern unsigned long data_021f6c70, data_021f6c94, data_021f6c84, data_021f6c88, data_021f6c8c, data_021f6c90, data_021f6c74,
    data_021f6c78, data_021f6c7c, data_021f6c80;
extern void *NNS_GfdDefaultFuncAllocTexVram;
extern void *NNS_GfdDefaultFuncAllocPlttVram;

void func_020b947c(void)
{
    int result;

    NNS_GfdInitFrmTexVramManager(4, 1);
    NNS_GfdInitFrmPlttVramManager(0x8000, 1);
    NNS_GfdDefaultFuncAllocTexVram = (((void *) func_020b95b4));
    NNS_GfdDefaultFuncAllocPlttVram = (((void *) func_020b958c));
    data_021f6c70 = 0;
    data_021f6c94 = GX_GetSizeOfTexPltt();
    data_021f6c84 = 0;
    data_021f6c88 = 0;
    data_021f6c8c = 0;
    data_021f6c90 = 0;
    data_021f6c74 = 0;
    data_021f6c78 = 0;
    data_021f6c7c = 0;
    data_021f6c80 = 0;

    result = GX_GetBankForTex();
    if (result == 7) {
        goto L7;
    }
    if (result != 15) {
        goto Lcall;
    }
    data_021f6c90 = 0;
    data_021f6c8c = 0x00020000;
    data_021f6c88 = 0x00030000;
    data_021f6c84 = 0x00040000;
    data_021f6c80 = 0x00020000;
    data_021f6c7c = 0x00030000;
    data_021f6c78 = 0x00040000;
    data_021f6c74 = 0x00080000;
    goto Ldone;
L7:
    data_021f6c90 = 0;
    data_021f6c8c = 0x00020000;
    data_021f6c88 = 0x00030000;
    data_021f6c84 = 0x00040000;
    data_021f6c80 = 0x00020000;
    data_021f6c7c = 0x00030000;
    data_021f6c78 = 0x00040000;
    data_021f6c74 = 0x00060000;
    goto Ldone;
Lcall:
    OS_Terminate();
Ldone:;
}
