/* func_02054944 @ 0x02054944, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02056b18(void *arg1, void *arg2);

void func_02054944(void *p0, void *p1)
{
    if ((*(int *) (*(void **) ((unsigned char *) p1 + 0xb4)) & 4) != 0) {
        *(int *) ((unsigned char *) (*(void **) ((unsigned char *) p1 + 0xb4)) + 0x4c) = 0;
        *(int *) ((unsigned char *) (*(void **) ((unsigned char *) p1 + 0xb4)) + 0x50) = 0;
        *(int *) ((unsigned char *) (*(void **) ((unsigned char *) p1 + 0xb4)) + 0x54) = 0;
    }
    if (*(int *) ((unsigned char *) p0 + 0x148) != 0) {
        func_02056b18((unsigned char *) p0 + 0x110, p1);
    }
}
