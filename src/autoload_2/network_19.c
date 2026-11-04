/* network_19: 4 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020ed6ac @ 0x020ed6ac, 0x18 bytes, ARM
 * func_020ed6a8 @ 0x020ed6a8, 0x4 bytes, ARM
 * func_020ed68c @ 0x020ed68c, 0x1c bytes, ARM
 * func_020ed658 @ 0x020ed658, 0x34 bytes, ARM
 */

extern unsigned int data_0213e6c4;
extern char data_021fbffa[];
extern void func_020ed950(void *);
extern void (*CTRDGi_WriteAgbFlashSectorAsync)(int, char *, unsigned int);

void func_020ed6ac(unsigned int r0, int local, int is_server, int cancelled, int peer, void *user_data)
{
    if (r0 == 0) {
        data_0213e6c4 = 0;
    }
}

void func_020ed6a8(int status, int local, int cancelled, int peer, int connection, void *userData) {}

void func_020ed68c(int a, int b)
{
    data_021fbffa[b * 4] = 0;
    func_020ed950((void *) a);
}

void func_020ed658(int a, int b, int c)
{
    data_021fbffa[a * 4] = 0;
    CTRDGi_WriteAgbFlashSectorAsync(a, (char *) b, (unsigned int) c);
}
