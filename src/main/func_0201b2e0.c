/* func_0201b2e0 @ 0x0201b2e0, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020c81d8;
extern void MI_CpuCopy8(int, int, int);

void func_0201b2e0(int p0)
{
    *(int *) ((char *) (p0) + (0)) = 4096;
    *(int *) ((char *) (p0) + (4)) = 0;
    *(int *) ((char *) (p0) + (8)) = 0;
    *(int *) ((char *) (p0) + (48)) = 5;
    *(int *) ((char *) (p0) + (56)) = 0;
    *(int *) ((char *) (p0) + (60)) = 0;
    *(int *) ((char *) (p0) + (64)) = 0;
    *(int *) ((char *) (p0) + (68)) = 0;
    *(int *) ((char *) (p0) + (72)) = 0;
    *(int *) ((char *) (p0) + (76)) = 0;
    *(unsigned char *) ((char *) (((int) (p0) + (84))) + (0)) = 0;
    *(unsigned char *) ((char *) (((int) (p0) + (85))) + (0)) = 0;
    MI_CpuCopy8((int) &data_020c81d8, ((int) (p0) + (12)), 36);
}
