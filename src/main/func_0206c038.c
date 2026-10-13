/* func_0206c038 @ 0x0206c038, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_0206c038(unsigned int *arg0)
{
    unsigned int val;
    unsigned char *puVar2;

    val = *(unsigned int *) ((unsigned char *) arg0 + 0x410);
    if (val != 0 && val <= 3) {
        puVar2 = (unsigned char *) arg0 + val;
        puVar2[0x437] = 1;
    }
}
