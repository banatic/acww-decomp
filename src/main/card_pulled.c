/* card_pulled: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02098414 @ 0x02098414, 0xc bytes, Thumb
 * func_02098404 @ 0x02098404, 0x10 bytes, Thumb
 */

extern int data_021cfb64;
extern void func_02120000(int (*)(void));

int func_02098414(void)
{
    *(unsigned char *) &data_021cfb64 = 1;
    return 1;
}

void func_02098404(void)
{
    func_02120000(func_02098414);
}
