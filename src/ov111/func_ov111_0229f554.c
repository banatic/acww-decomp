/* func_ov111_0229f554 @ 0x0229f554, 0x44 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov095_0229bb34(void *dst, const void *src, int width, int height, unsigned char flag, void *ptr);
extern void func_ov111_0229efec(void *self);

void func_ov111_0229f554(void *param)
{
    unsigned char old_a1;
    void *ptr_9e;
    old_a1 = *(unsigned char *) ((char *) param + 0xa1);
    ptr_9e = (char *) param + 0x9e;
    *(unsigned char *) ((char *) param + 0xa1) =
        (unsigned char) func_ov095_0229bb34((char *) param + 0xac, (char *) param + 0x3d16, 0x10, 0xa0, old_a1, ptr_9e);
    *(unsigned char *) ((char *) param + 0x9c) = 0x10;
    func_ov111_0229efec(param);
}
