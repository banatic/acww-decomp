/* func_ov108_0229c468 @ 0x0229c468, 0x30 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov108_0229c5f4(void *);
extern void func_ov002_022096d8(void *, int);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov108_0229c468(void *p)
{
    *((unsigned char *) p + 0x2b4) = 1;
    func_ov108_0229c5f4(p);
    func_ov002_022096d8((char *) p + 0x24fc, 0);
    func_ov002_02208098((void *) (p), 0x15);
}
