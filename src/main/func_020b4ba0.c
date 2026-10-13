/* func_020b4ba0 @ 0x020b4ba0, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b4ba0(void *arg0);

void func_020b4ba0(void *arg0)
{
    unsigned int val;
    unsigned char *puVar2;

    val = *(unsigned int *) ((char *) arg0 + 0x24);
    if (val - 1 <= 1) {
        puVar2 = (unsigned char *) ((char *) arg0 + 0x34);
        *puVar2 = 1;
    }
    return;
}
