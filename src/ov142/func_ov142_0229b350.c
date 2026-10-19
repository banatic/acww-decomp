/* func_ov142_0229b350 @ 0x0229b350, 0x44 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200467c(int);
extern void *func_ov002_0220a720(void *, int);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_0206fc4c(int);
extern unsigned short *func_ov142_0229a644(void *, short);
extern void func_0206f68c(int);
extern void func_ov142_0229b174(void *);

void func_ov142_0229b350(void *param)
{
    func_0200467c(0x29);
    func_ov002_0220a720((char *) param + 0x194, 3);
    func_ov002_02208098((void *) (param), 0xd);
    func_0206fc4c(1);
    func_0206f68c(*func_ov142_0229a644(param, *(short *) ((char *) param + 0xb8)));
    func_ov142_0229b174(param);
}
