/* func_ov093_0229957c @ 0x0229957c, 0x20 bytes, Thumb, module ov093
 * mwccarm 1.2/base -O4,s
 */

extern int func_02064af4(void *dst, void *src, unsigned int size);
extern unsigned char data_ov093_0229991c[];

void func_ov093_0229957c(void *src)
{
    func_02064af4(data_ov093_0229991c, (char *) src + 0x1028, 0x800);
}
