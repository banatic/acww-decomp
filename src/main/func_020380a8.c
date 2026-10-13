/* func_020380a8 @ 0x020380a8, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8bb8(void *dst, const void *src);
extern void func_02038078(void *ptr);

extern unsigned char data_021c5b38[];

void func_020380a8(void *ptr)
{
    void *r4 = ptr;
    func_020a8bb8((char *) ptr + 0xe8, (void *) data_021c5b38);
    func_02038078(r4);
}
