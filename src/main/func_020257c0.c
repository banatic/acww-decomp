/* func_020257c0 @ 0x020257c0, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02014f60(void *);
extern void func_0209ba7c(int);
extern void func_0207863c(int);

void func_020257c0(void *arg0)
{
    func_02014f60(arg0);
    func_0209ba7c(*(int *) ((char *) arg0 + 0x164));
    func_0207863c(*(int *) (*(char **) ((char *) arg0 + 0x100) + 0x830));
}
