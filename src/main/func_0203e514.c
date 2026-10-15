/* func_0203e514 @ 0x0203e514, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203ec98(void);
extern void func_0203e58c(void);
extern void func_0203e55c(void);
extern void func_0203e5f4(void);
extern void func_0203e5c0(void);
extern void func_0203f568(int);

extern unsigned char data_021c72c4[];

int func_0203e514(int param)
{
    if (func_0203ec98()) {
        asm { add r0, param, #0 }
        func_0203e58c();
        asm { add r0, param, #0 }
        func_0203e55c();
    }
    if (!func_0203ec98()) {
        asm { add r0, param, #0 }
        func_0203e5f4();
    }
    if (func_0203ec98()) {
        asm { add r0, param, #0 }
        func_0203e5c0();
    }
    func_0203f568((unsigned int) data_021c72c4);
    return 1;
}
