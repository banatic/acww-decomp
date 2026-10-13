/* func_ov132_0229b5c8 @ 0x0229b5c8, 0x40 bytes, Thumb, module ov132
 * mwccarm 1.2/base -O4,s
 */

extern int func_020ee45c(void *);
extern void func_ov092_02299324(int, unsigned char, int);
extern void func_ov002_02207f04(void *, int, int, int, int);
extern void func_ov002_02208090(void *, int);
extern void func_ov132_0229b578(void *);

void func_ov132_0229b5c8(void *obj)
{
    int ret = func_020ee45c(obj);
    func_ov092_02299324(ret, ((unsigned char *) obj)[0x1505], 1);
    func_ov002_02207f04(obj, 10, 0, 0, 0x30);
    func_ov132_0229b578(obj);
    func_ov002_02208090(obj, 3);
}
