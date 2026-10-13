/* func_020abb48 @ 0x020abb48, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020aca24(void *);

void func_020abb48(void *obj)
{
    *(unsigned int *) ((char *) obj + 0x13c) = 4;
    func_020aca24((char *) obj + 0xe4);
}
