/* func_02062d44 @ 0x02062d44, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206e71c(void *);
extern void func_0206e808(void *);
extern int func_0206e8b4(void *);

void *func_02062d44(void *p)
{
    func_0206e71c(p);
    func_0206e808((char *) p + 0x54);
    func_0206e8b4((char *) p + 0x54);
    func_0206e8b4((char *) p + 0x38);
    func_0206e8b4((char *) p + 0x1c);
    func_0206e8b4(p);
    return p;
}
