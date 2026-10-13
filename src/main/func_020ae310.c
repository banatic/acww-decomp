/* func_020ae310 @ 0x020ae310, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020ae3b8(void *ptr);
extern void func_020ae4fc(int a, unsigned char b);
extern int data_021f3b30;

void func_020ae310(int param)
{
    func_020ae4fc(func_020ae3b8(&data_021f3b30), (unsigned char) param);
}
