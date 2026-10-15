/* func_ov003_0222fd60 @ 0x0222fd60, 0xb8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_0222fd60;
extern UnkStruct_0222fd60 *data_020ccf94;

extern int func_0205c9c8(int size, int heapword);
extern void func_0205c9ac(void);
extern int func_0205ca30(int size, int heapword);
extern void func_0205ca14(void);
extern int func_0205c9fc(int size, int heapword);
extern void func_0205c9e0(void);

extern int func_0209d180(void *self, unsigned int count, int a, int b, int size, int (*allocate)(int, int),
                         void (*cleanup)(void));
extern int func_02073dd4(void *a, int b);
extern int func_ov003_0222ff74(void *self, int a, int b);
extern void func_ov003_0222c758(void);

int func_ov003_0222fd60(char *self)
{
    UnkStruct_0222fd60 *context;
    volatile unsigned int outgoing[4];
    outgoing[0] = 0x9c4;
    outgoing[1] = (unsigned int) func_0205c9c8;
    outgoing[2] = (unsigned int) func_0205c9ac;
    outgoing[3] = (unsigned int) 0;
    // clang-format off
    asm {
        mov r0, self
        add r0, #0x50
        mov r1, #8
        ldr r2, =0x400
        mov r3, #0x40
        bl func_0209d180
    }
    // clang-format on
    outgoing[0] = 0x6e8;
    outgoing[1] = (unsigned int) func_0205ca30;
    outgoing[2] = (unsigned int) func_0205ca14;
    outgoing[3] = (unsigned int) 0;
    // clang-format off
    asm {
        mov r0, self
        add r0, #0x68
        mov r1, #2
        ldr r2, =0x400
        mov r3, #0x40
        bl func_0209d180
    }
    // clang-format on
    outgoing[0] = 0x9c4;
    outgoing[1] = (unsigned int) func_0205c9fc;
    outgoing[2] = (unsigned int) func_0205c9e0;
    outgoing[3] = (unsigned int) 0;
    // clang-format off
    asm {
        mov r0, self
        add r0, #0x80
        mov r1, #4
        ldr r2, =0x400
        mov r3, #0x40
        bl func_0209d180
    }
    // clang-format on
    context = data_020ccf94;
    if (func_02073dd4(context, context->unk_64) == 0) {
        func_ov003_0222ff74(self, 0x3a, 0);
        func_ov003_0222ff74(self, 0x3b, 1);
    }
    func_ov003_0222c758();
    return 1;
}
