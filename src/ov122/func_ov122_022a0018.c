/* func_ov122_022a0018 @ 0x022a0018, 0x20 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fe60(void);
extern unsigned char *func_ov122_022a0054(void *);
extern unsigned char *func_ov122_022a0038(void *);

unsigned char *func_ov122_022a0018(void *p)
{
    if (func_0206fe60()) {
        return func_ov122_022a0054(p);
    } else {
        return func_ov122_022a0038(p);
    }
}
