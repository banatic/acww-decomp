/* func_02066514 @ 0x02066514, 0x4a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020984e8(void);
extern void *func_02099870(int);
extern void *func_02099734(void *);
extern void *func_02098ddc(void *);
extern void func_02051c08(void *, void *, int);
extern void func_020666bc(void *, void *);

void func_02066514(void *param0)
{
    void *r5;
    void *r6;
    r5 = func_020984e8();
    r6 = func_02099870((int) r5);
    if (*(unsigned char *) ((char *) param0 + 0x22) != 1) {
        r5 = func_02098ddc(func_02099734(r5));
        func_02051c08((void *) ((char *) r5 + 0x14), (void *) ((char *) param0 + 0x44), 10);
        *(unsigned char *) ((char *) param0 + 0xf8) = *(unsigned char *) ((char *) r5 + 0x49);
    }
    func_020666bc((void *) ((char *) param0 + 4), r6);
}
