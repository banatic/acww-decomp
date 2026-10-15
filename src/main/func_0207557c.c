/* func_0207557c @ 0x0207557c, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(const void *src, void *dest, int size);
extern int func_0209847c(int arg);
extern void func_020962a4(int a, int b);

void func_0207557c(unsigned char *payload, unsigned int length, int player)
{
    int local;
    int p2_plus_3;
    int r;

    MI_CpuCopy8(payload, &local, 4);
    p2_plus_3 = player + 3;
    r = func_0209847c(p2_plus_3);
    MI_CpuCopy8(payload + 4, (void *) (r + local), length - 4);
    func_020962a4(player, p2_plus_3);
}
