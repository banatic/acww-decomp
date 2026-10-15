/* func_ov121_0229afb8 @ 0x0229afb8, 0x20 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fe60(void);
extern unsigned char *func_ov121_0229b008(void *p);
extern unsigned char *func_ov121_0229afd8(void *p);

unsigned char *func_ov121_0229afb8(void *p)
{
    if (func_0206fe60()) {
        return func_ov121_0229b008(p);
    } else {
        return func_ov121_0229afd8(p);
    }
}
