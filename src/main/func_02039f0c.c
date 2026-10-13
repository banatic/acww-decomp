/* func_02039f0c @ 0x02039f0c, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02051a78(void *);
extern void func_020a8bb8(void *, void *);

void func_02039f0c(void *param0, void *param1, void *param2, void *param3)
{
    void *r5 = param0;
    void *r6 = param2;
    void *r4 = param3;

    func_02051a78((char *) r5 + 0x88);
    func_020a8bb8((char *) r5 + 0x54, r6);
    *(unsigned int *) ((char *) r5 + 0x10) = (unsigned int) ((char *) r4 + 5);
}
