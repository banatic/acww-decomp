/* func_0203f364 @ 0x0203f364, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_020ccf94;
extern int func_02073d90(void *);
extern int func_0203f444(int);
extern void func_0203f490(int, int);

void func_0203f364(void)
{
    void *r4;
    int r0;

    r4 = (void *) data_020ccf94;
    r0 = func_02073d90(r4);
    if (r0 != 0) {
        if (*(int *) ((char *) r4 + 0x64) == 0) {
            func_0203f444(0);
        } else {
            func_0203f490(3, 0);
        }
    }
}
