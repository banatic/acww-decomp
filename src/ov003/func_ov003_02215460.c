/* func_ov003_02215460 @ 0x02215460, 0x34 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov003_0223812c;
extern void func_0201107c(void *a, void *b);
extern void func_020109a0(void *a, int b, int c, unsigned short d);
extern void func_0205eae0(void *a, int b, int c, int d);

void func_ov003_02215460(void *obj, void *message, int previous)
{
    func_0201107c(obj, &data_ov003_0223812c);
    func_020109a0(obj, 0x57, 3, 0);
    func_0205eae0((char *) obj + 0x5a0, 0x1a, 3, 0);
}
