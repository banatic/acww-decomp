/* wfc_setup: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206e518 @ 0x0206e518, 0x48 bytes, Thumb
 * func_0206e508 @ 0x0206e508, 0x10 bytes, Thumb
 * func_0206e4fc @ 0x0206e4fc, 0xc bytes, Thumb
 * func_0206e4f0 @ 0x0206e4f0, 0xc bytes, Thumb
 * func_0206e464 @ 0x0206e464, 0x8c bytes, Thumb
 */

typedef unsigned int uintptr_t;

extern int func_02077b70(int *p, int n);
extern int func_0210172c(int a);
extern void func_02077b9c(int *p);
extern void func_020e9898(int a);
extern int data_021d11c4;
extern unsigned char data_020df29c;
extern int SDK_OVERLAY_ov065_ID;
extern int func_020e98f4(int, int);
extern int OS_DisableInterrupts(void);
extern unsigned int OS_DisableIrqMask(int);
extern unsigned int OS_ResetRequestIrqMask(int);
extern void func_ov065_0227f1f4(void *(*alloc)(int, unsigned int, int), void (*free)(int, void *, unsigned int));
extern void func_0204f934(int);
extern int func_ov001_022141f4(int, int, int);
extern void func_0204f8ec(int);
extern unsigned int OS_RestoreInterrupts(int);
extern int SDK_OVERLAY_ov001_ID;

int func_0206e518(void)
{
    int a;
    int b;

    a = func_020e98f4(0x700, 0x20);
    func_02077b70(&data_021d11c4, (int) &SDK_OVERLAY_ov065_ID);
    b = func_0210172c(a);
    data_020df29c = (unsigned char) b;
    func_02077b9c(&data_021d11c4);
    func_020e9898(a);
    return b;
}

unsigned char func_0206e508(void)
{
    unsigned char old = data_020df29c;
    data_020df29c = 4;
    return old;
}

void *func_0206e4fc(int name, unsigned int size, int align)
{
    (void) name;
    return (void *) (uintptr_t) (unsigned int) func_020e98f4(size, align);
}

void func_0206e4f0(int name, void *block, unsigned int size)
{
    (void) name;
    (void) size;
    func_020e9898((int) (uintptr_t) block);
}

void func_0206e464(void)
{
    int a = OS_DisableInterrupts();
    unsigned short saved = *(volatile unsigned short *) 0x04000208;
    *(volatile unsigned short *) 0x04000208 = 0;
    OS_DisableIrqMask(7);
    OS_ResetRequestIrqMask(7);
    func_02077b70(&data_021d11c4, (int) &SDK_OVERLAY_ov065_ID);
    func_ov065_0227f1f4(func_0206e4fc, func_0206e4f0);
    func_0204f934((int) &SDK_OVERLAY_ov001_ID);
    {
        int v = func_020e98f4(0x40000, 0x20);
        func_ov001_022141f4(v, 6, 0);
        func_020e9898(v);
    }
    func_0204f8ec((int) &SDK_OVERLAY_ov001_ID);
    func_02077b9c(&data_021d11c4);
    (void) *(volatile unsigned short *) 0x04000208;
    *(volatile unsigned short *) 0x04000208 = saved;
    OS_RestoreInterrupts(a);
}
