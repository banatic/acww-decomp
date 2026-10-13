/* func_ov094_0229bbd8 @ 0x0229bbd8, 0x40 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov094_0229b174(void *);

void func_ov094_0229bbd8(void *p, int v)
{
    func_ov094_0229b174((char *) p + 8);
    func_ov094_0229b174((char *) p + 0x10);
    func_ov094_0229b174((char *) p + 0x18);
    ((unsigned char *) p)[0x24] = 0x37;
    ((unsigned char *) p)[0x25] = 0;
    *(int *) ((char *) p + 0x20) = v;
    *(int *) ((char *) p + 4) = 0;
    ((unsigned char *) p)[0x27] = 0xa;
}
