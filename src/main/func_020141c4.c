/* func_020141c4 @ 0x020141c4, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02019b70(void *ptr);

void func_020141c4(void *param1, void *param2)
{
    unsigned char b;
    void *ptr;

    b = *(unsigned char *) ((char *) param1 + 0xe);
    if (b != 0) {
        ptr = (char *) param2 + 0x564;
        func_02019b70(ptr);
        *(unsigned char *) ((char *) param1 + 0xa) = 2;
        *(unsigned char *) ((char *) param1 + 8) = 5;
    }
}
