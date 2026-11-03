/* mes_slider_window_5: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020ac0ac @ 0x020ac0ac, 0x70 bytes, Thumb
 * func_020ac078 @ 0x020ac078, 0x34 bytes, Thumb
 * func_020ac040 @ 0x020ac040, 0x38 bytes, Thumb
 */

typedef struct {
    void *vtable;
    char pad_04[0x1c];
    char sub1[0x4c];
    char sub2[0x78];
    char sub3[0x58];
    int unk_13C;
    char unk_140[6];
} UnkStruct_020ac0ac;

extern void func_020ac9a4(void *);
extern void *func_020aca04(void *);
extern void *func_0208f518(void *, int, int);
extern void *func_020acb94(void *);
extern unsigned char data_020e3fe4[];
extern void *func_020acb70(void *a);
extern void *func_0208f4e0(void *a);
extern void *func_020ac9ec(void *a);
extern void *func_020ac954(void *a);
extern void func_020edb3c(void *);

UnkStruct_020ac0ac *func_020ac0ac(UnkStruct_020ac0ac *obj)
{
    func_020ac9a4(obj);
    obj->vtable = data_020e3fe4;
    func_020aca04(&obj->sub1);
    func_0208f518(&obj->sub2, 1, 0);
    func_020acb94(&obj->sub3);
    obj->unk_13C = 0;
    obj->unk_140[0] = 0;
    obj->unk_140[1] = 0;
    obj->unk_140[2] = 0;
    obj->unk_140[3] = 0;
    obj->unk_140[4] = 0;
    obj->unk_140[5] = 0;
    return obj;
}

void *func_020ac078(void *arg)
{
    *(void **) arg = (void *) data_020e3fe4;
    func_020acb70((void *) ((char *) arg + 0xE4));
    func_0208f4e0((void *) ((char *) arg + 0x6C));
    func_020ac9ec((void *) ((char *) arg + 0x20));
    func_020ac954(arg);
    return arg;
}

void *func_020ac040(void *param)
{
    *(void **) param = ((char *) data_020e3fe4);
    func_020acb70((void *) ((unsigned int) param + 0xe4));
    func_0208f4e0((void *) ((unsigned int) param + 0x6c));
    func_020ac9ec((void *) ((unsigned int) param + 0x20));
    func_020ac954(param);
    func_020edb3c(param);
    return param;
}
