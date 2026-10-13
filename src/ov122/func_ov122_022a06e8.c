/* func_ov122_022a06e8 @ 0x022a06e8, 0x2c bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e930(void *);
extern void func_ov122_0229f170(void *);
extern void func_ov122_0229efc8(void *, int);

void func_ov122_022a06e8(void *param)
{
    if (func_0208e930((char *) param + 0x4010)) {
        func_ov122_0229f170(param);
        func_ov122_0229efc8(param, 0x200);
    }
}
