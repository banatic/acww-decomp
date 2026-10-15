/* func_ov002_022082a0 @ 0x022082a0, 0x38 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_022087bc(void *ptr);
extern void func_ov002_022089d4(void *ptr);
extern void func_ov002_02207f6c(void *ptr);
extern void func_020ee62c(void *ptr);
extern char data_ov002_0220bb24;
extern char data_020da13c;

void *func_ov002_022082a0(void *obj)
{
    *(void **) obj = &data_ov002_0220bb24;
    func_ov002_022087bc((void *) ((char *) obj + 0x70));
    func_ov002_022089d4((void *) ((char *) obj + 0x50));
    *(void **) obj = &data_020da13c;
    func_020ee62c(obj);
    func_ov002_02207f6c(obj);
    return obj;
}
