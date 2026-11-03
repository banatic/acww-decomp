/* talk_page_5: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206cd28 @ 0x0206cd28, 0x16 bytes, Thumb
 * func_0206cd10 @ 0x0206cd10, 0x16 bytes, Thumb
 * func_0206ccf8 @ 0x0206ccf8, 0x16 bytes, Thumb
 * func_0206cce0 @ 0x0206cce0, 0x16 bytes, Thumb
 * func_0206ccc8 @ 0x0206ccc8, 0x16 bytes, Thumb
 */

extern int func_02050c40(void);
extern void func_020a9334(void *object, void *next);
extern unsigned int func_02050c38(void);
extern int func_02050c30(void);
extern int func_02050c48(void);
extern int func_02050c50(void);

void func_0206cd28(void *object)
{
    int next = func_02050c40();
    func_020a9334(object, (void *) next);
}

void func_0206cd10(unsigned int arg)
{
    unsigned int tmp;
    tmp = func_02050c38();
    func_020a9334((void *) arg, (void *) tmp);
}

void func_0206ccf8(void *object)
{
    int next = func_02050c30();
    func_020a9334(object, (void *) next);
}

void func_0206cce0(void *object)
{
    int next = func_02050c48();
    func_020a9334(object, (void *) next);
}

void func_0206ccc8(void *object)
{
    int next = func_02050c50();
    func_020a9334(object, (void *) next);
}
