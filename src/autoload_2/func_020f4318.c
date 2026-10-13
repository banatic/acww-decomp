/* func_020f4318 @ 0x020f4318, 0x20 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020eec48(void);
extern void func_020eec60(void);

void func_020f4318(unsigned char *r4)
{
    func_020eec48();
    func_020eec60();
    r4[6] = 0;
}
