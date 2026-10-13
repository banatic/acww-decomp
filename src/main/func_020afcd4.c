/* func_020afcd4 @ 0x020afcd4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020af028(void *ptr);
extern void func_02077f14(int a, void *b);

extern unsigned char data_020e41b8[];
extern unsigned char data_021f395c[];

void func_020afcd4(void)
{
    func_02077f14(func_020af028((void *) data_021f395c) + 3, (void *) data_020e41b8);
}
