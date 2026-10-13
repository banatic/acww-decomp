/* func_ov138_0229c978 @ 0x0229c978, 0x48 bytes, Thumb, module ov138
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a720(void *ptr, int n);
extern void func_ov002_02208090(void *self, int n);
extern void func_ov002_02208098(void *self, int n);
extern void func_ov134_0229bbdc(void *dst, void *src);
extern void func_0206f820(void *p);
extern void func_0206fc4c(int n);

void func_ov138_0229c978(void *arg)
{
    func_ov002_0220a720((char *) arg + 0xfc, 6);
    func_ov002_02208090(arg, 2);
    func_ov002_02208098(arg, 0xb);
    {
        int v[2];
        v[0] = 0;
        v[1] = 0;
        func_ov134_0229bbdc((char *) arg + 0x2c8, v);
        func_0206f820(v);
        func_0206fc4c(1);
    }
}
