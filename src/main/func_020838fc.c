/* func_020838fc @ 0x020838fc, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02078a30(void *, int);

void func_020838fc(void *arg0, int argument1)
{
    func_02078a30((char *) arg0 + 4, (int) argument1);
    *(unsigned char *) arg0 = 1;
}
