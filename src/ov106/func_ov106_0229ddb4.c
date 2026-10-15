/* func_ov106_0229ddb4 @ 0x0229ddb4, 0x3c bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208e28(char *);
extern int func_0206fe54(void);
extern void func_ov106_0229ca90(char *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov106_0229ddb4(char *param)
{
    if (func_ov002_02208e28(param + 0x2304)) {
        if (func_0206fe54()) {
            func_ov106_0229ca90(param);
            func_ov002_02208098((void *) (param), 0xb);
        } else {
            func_ov002_02208098((void *) (param), 6);
        }
    }
}
