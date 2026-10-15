/* func_ov003_0222079c @ 0x0222079c, 0x3c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02220120(void);
extern int func_020b3b20(void);
extern void func_ov003_0221ffcc(void *ptr);
extern void func_ov003_0221feb8(void *ptr);
extern void func_ov003_0221fe30(void);
extern void func_ov003_022203f4(void);
extern char data_ov003_0223cea0[];
extern char data_ov003_0223ce80[];
extern char data_ov003_0223ce58[];

int func_ov003_0222079c(void *param)
{
    func_ov003_02220120();
    // clang-format off
    asm {
        mov r0, param
    }
    // clang-format on
    func_020b3b20();
    func_ov003_0221ffcc(data_ov003_0223cea0);
    func_ov003_0221feb8(data_ov003_0223ce80);
    // clang-format off
    asm {
        ldr r0, =data_ov003_0223ce58
    }
    // clang-format on
    func_ov003_0221fe30();
    // clang-format off
    asm {
        mov r0, param
    }
    // clang-format on
    func_ov003_022203f4();
    return 1;
}
