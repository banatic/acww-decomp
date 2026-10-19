/* func_ov106_0229c458 @ 0x0229c458, 0x24 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_0208f0c4(void *p, int n);
extern void func_0200467c(int cmd);

void func_ov106_0229c458(char *param)
{
    func_ov002_02208098((void *) (param), 0x22);
    func_0208f0c4(param + 0x2b3c, 2);
    func_0200467c(0x29);
}
