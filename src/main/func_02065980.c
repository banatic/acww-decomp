/* func_02065980 @ 0x02065980, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02064e28(void *);
extern void func_02065450(void *);
extern void func_020656ac(void *);

int func_02065980(void *arg0)
{
    void *r5;
    int r4;
    void *r6;

    r6 = arg0;
    r5 = (char *) r6 + 0x58;
    r4 = 0;
    while (r4 < *(int *) ((char *) r6 + 0x54)) {
        func_02064e28(r5);
        r5 = (char *) r5 + 0x44;
        r4++;
    }
    func_02065450((char *) r6 + 0x124);
    func_020656ac(r6);
    return 1;
}
