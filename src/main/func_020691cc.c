/* func_020691cc @ 0x020691cc, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02069194(void);
extern void func_020a9354(void *param1, void *param2);
extern void func_020a92d8(void *param1, int param2);

void func_020691cc(void *param1, void *param2)
{
    void *r5 = param1;
    void *r4 = param2;

    func_02069194();
    *(int *) ((char *) r5 + 0x28) = 0;
    func_020a9354(r5, r4);
    func_020a92d8(r5, 0);
}
