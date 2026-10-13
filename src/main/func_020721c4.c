/* func_020721c4 @ 0x020721c4, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02064af4(void *dest, const void *src, int size);
extern unsigned char data_020e17d8[];

void func_020721c4(const void *src)
{
    func_02064af4(data_020e17d8, src, 0x200);
}
