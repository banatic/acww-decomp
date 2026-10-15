/* func_020be6ac @ 0x020be6ac, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020e8870(void *dst, int val, int size);
extern int func_02095518(short a, short b, int c);

void func_020be6ac(void *param0, void *param1, void *param2)
{
    short s1;
    short s2;
    void *p;

    p = (char *) param0 + 0x1a;
    func_020e8870(p, 0, (int) param1);
    p = (char *) param0 + 0x1c;
    func_020e8870(p, 0, (int) param2);
    s1 = *(short *) ((char *) param0 + 0x1a);
    s2 = *(short *) ((char *) param0 + 0x1c);
    func_02095518(s1, s2, 4);
}
