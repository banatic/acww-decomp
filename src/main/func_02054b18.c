/* func_02054b18 @ 0x02054b18, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020dd0ac;
extern int data_020dd0bc;
extern int data_020dd0cc;

extern void func_02056ed4(void *);
extern void func_02057078(void *);
extern void *func_02054d9c(void *);
extern void func_020edb3c(void *);

void *func_02054b18(void *arg)
{
    *((int *) arg) = (int) &data_020dd0ac;
    *((int *) ((char *) arg + 0x9c)) = (int) &data_020dd0bc;
    *((int *) ((char *) arg + 0xb8)) = (int) &data_020dd0cc;
    func_02056ed4((char *) arg + 0x110);
    func_02057078((char *) arg + 0xf8);
    func_02054d9c(arg);
    func_020edb3c(arg);
    return arg;
}
