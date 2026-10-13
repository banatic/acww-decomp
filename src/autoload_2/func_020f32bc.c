/* func_020f32bc @ 0x020f32bc, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f45c4(void *);
extern int data_0213ec0c;

void *func_020f32bc(void *p)
{
    func_020f45c4(p);
    ((void **) p)[0] = &data_0213ec0c;
    ((char *) p)[4] = 0x21;
    return p;
}
