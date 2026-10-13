/* func_0209d57c @ 0x0209d57c, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern int data_021dc70c;

extern int func_02073d90(void *);
extern int func_02073918(void *, int);
extern void func_02073820(void *);
extern int func_020737f0(void *, unsigned char *, int);
extern int func_02073770(void *, int, int);
extern void func_0209d8cc(void *, unsigned char, int);

void func_0209d57c(unsigned char a, int b)
{
    void *p;
    unsigned char c;

    p = data_020ccf94;
    if (func_02073d90(p) == 0 || func_02073918(p, 0) != 0 || func_02073918(p, 4) != 0) {
        func_0209d8cc(&data_021dc70c, a, b);
        return;
    }

    c = a;
    p = data_020ccf94;
    func_02073820(p);
    func_020737f0(p, &c, 1);
    func_02073770(p, 0x35, 0);
}
