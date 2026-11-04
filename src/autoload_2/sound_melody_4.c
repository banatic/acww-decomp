/* sound_melody_4: 3 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020f6720 @ 0x020f6720, 0x34 bytes, ARM
 * func_020f6700 @ 0x020f6700, 0x20 bytes, ARM
 * func_020f66f0 @ 0x020f66f0, 0x10 bytes, ARM
 */

extern unsigned char data_02138ff4[];
extern void func_020f6f70(void *);
extern void func_020f6ff4(void *param1, void *param2);

void *func_020f6720(unsigned char *self)
{
    unsigned char idx = self[0x3b];
    unsigned char *src = data_02138ff4 + (idx << 4);
    int i;
    for (i = 0; i < 0x10; i++) {
        (self + i)[0x28] = src[i];
    }
    return self + 0x28;
}

void func_020f6700(void *param)
{
    func_020f6f70((char *) param + 0x14);
    ((unsigned char *) param)[0x1e] = 0;
}

void func_020f66f0(void *param1)
{
    func_020f6ff4(param1, (char *) param1 + 0x28);
}
