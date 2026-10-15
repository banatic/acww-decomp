/* func_ov109_0229cccc @ 0x0229cccc, 0x44 bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

extern volatile unsigned char data_021f43ec;
extern int func_ov002_0220b9b8(void *, void *, int, int);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);
extern void func_0208e5c4(void *);

void func_ov109_0229cccc(unsigned char *obj, unsigned char arg)
{
    char b;

    b = data_021f43ec;
    b = arg;
    func_ov002_0220b9b8(obj + 0x26cc, &b, 1, 0);
    func_ov002_02208098(obj, 0xe);
    func_0208e5c4(obj + 0x2274);
}
