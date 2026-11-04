/* sound_object_kinds_5: 2 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020f8474 @ 0x020f8474, 0x20 bytes, ARM
 * func_020f8444 @ 0x020f8444, 0x30 bytes, ARM
 */

extern void func_020f7d4c(void *unused0);
extern int func_020f7bc4(void *param1, int param2, void *param3);

void func_020f8474(unsigned short *r4)
{
    func_020f7d4c(r4);
    r4[7] = 0;
    r4[8] = 0;
}

void func_020f8444(void *param1)
{
    func_020f7bc4(param1, 0x517, (char *) param1 + 8);
    *(unsigned short *) ((char *) param1 + 0x14) = 3;
    *(unsigned short *) ((char *) param1 + 0x12) = *(unsigned short *) ((char *) param1 + 0x14);
}
