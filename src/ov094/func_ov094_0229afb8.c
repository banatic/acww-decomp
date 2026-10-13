/* func_ov094_0229afb8 @ 0x0229afb8, 0x28 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov094_0229bf90;
extern void func_ov094_0229b0f8(void *);
extern void func_020edb3c(void *);

void *func_ov094_0229afb8(void *param)
{
    *(void **) param = (void *) &data_ov094_0229bf90;
    func_ov094_0229b0f8((char *) param + 0x184);
    func_020edb3c(param);
    return param;
}
