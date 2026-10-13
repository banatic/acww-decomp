/* func_020c1574 @ 0x020c1574, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02138c48(void *, int, int, void *);
extern void func_020012dc(void);
extern void func_020be550(void);
extern void func_020be554(void);

void *func_020c1574(void *obj)
{
    func_02138c48((void *) ((char *) obj + 0x302c), 8, 0xc, func_020012dc);
    func_02138c48((void *) ((char *) obj + 0x2f58), 4, 0x14, func_020be550);
    func_02138c48(obj, 0x3c, 0x74, func_020be554);
    return obj;
}
