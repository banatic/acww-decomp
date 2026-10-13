/* func_ov120_0229abec @ 0x0229abec, 0x1c bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov120_0229a438(void *obj, unsigned int arg);

void func_ov120_0229abec(unsigned char *obj, unsigned short value)
{
    *(unsigned short *) (obj + 0x98) = value;
    *(unsigned short *) (obj + 0x9A) = *(unsigned short *) (obj + 0x98);
    func_ov120_0229a438(obj, 0x10);
}
