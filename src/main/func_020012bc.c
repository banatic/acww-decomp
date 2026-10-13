/* func_020012bc @ 0x020012bc, 0x20 bytes, ARM, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02001268(void);
extern void func_02000c98(void);
extern void OS_Init(void);

void func_020012bc(void)
{
    OS_Init();
    func_02001268();
    func_02000c98();
}
