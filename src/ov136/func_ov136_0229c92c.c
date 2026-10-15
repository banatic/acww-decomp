/* func_ov136_0229c92c @ 0x0229c92c, 0x48 bytes, Thumb, module ov136
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_0220a720(char *ptr, int n);
extern void func_ov002_02208090(char *ptr, int n);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov134_0229bbdc(char *ptr, int *arr);
extern void func_0206f820(int *arr);
extern void func_0206fc4c(int val);

void func_ov136_0229c92c(char *obj)
{
    int local[2];

    func_ov002_0220a720(obj + 0xf8, 6);
    func_ov002_02208090(obj, 2);
    func_ov002_02208098((void *) (obj), 0xd);
    local[0] = 0;
    local[1] = 0;
    func_ov134_0229bbdc(obj + 0x2c4, local);
    func_0206f820(local);
    func_0206fc4c(1);
}
