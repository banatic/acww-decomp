/* func_ov118_0229a3b8 @ 0x0229a3b8, 0x80 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *addr, int a, int b, void (*func)(void));
extern void func_ov117_0229a2ec(void *addr);
extern void func_ov002_02209cb4(void *addr);
extern void func_ov002_0220a5e4(void *addr);
extern void func_ov002_0220826c(void *addr);
extern void func_ov002_02207f6c(void *addr);
extern void func_ov118_0229a438(void);
extern void func_02070be8(void);
extern int data_ov118_0229cc08;

void *func_ov118_0229a3b8(void *obj)
{
    char *p;

    *(unsigned int *) obj = (unsigned int) &data_ov118_0229cc08;
    __cxa_vec_cleanup((char *) obj + 0x47ad, 14, 3, func_ov118_0229a438);
    __cxa_vec_cleanup((char *) obj + 0x47a4, 3, 3, func_ov118_0229a438);
    func_ov117_0229a2ec((char *) obj + 0x4724);
    func_ov002_02209cb4((char *) obj + 0x6c0);
    func_ov002_0220a5e4((char *) obj + 0x678);
    p = (char *) obj;
    p += 0xfc;
    __cxa_vec_cleanup(p, 13, 108, func_02070be8);
    func_ov002_0220826c(obj);
    func_ov002_02207f6c(obj);
    return obj;
}
