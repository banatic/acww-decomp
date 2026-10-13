/* func_02022938 @ 0x02022938, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

/* FAKEMATCH: the volatile reads give the two loads of the item id and the empty if keeps the object pointer of the second call loaded after r0 and r1; inline pointer helpers give the loads but not the call order */

extern void func_0202e118(void *dst, unsigned int src);
extern void func_02022bbc(void *p, int n, void *data);
extern void func_0202bd40(void *p, int n, int val, void *ptr);
extern unsigned char data_020c8d28[];
struct UnkStruct_02022938 {
    unsigned char pad_00[0x100];
    unsigned int unk_100;
};
int func_02022938(struct UnkStruct_02022938 *obj)
{
    unsigned char *ptr2;
    unsigned short result;
    unsigned short b;
    unsigned short a;
    func_0202e118(&result, obj->unk_100);
    b = *((volatile unsigned short *) (&result));
    a = *((volatile unsigned short *) ((0, &result)));
    if ((a == 0xfff1) || ((b >= 0x1380) && (b <= 0x139f))) {
        ptr2 = ((unsigned char *) obj) + 0x100;
        func_02022bbc(obj, 3, data_020c8d28);
        if (((!obj) && (!obj)) && (!obj)) {
        }
        func_0202bd40(obj, 5, *((int *) ((*((unsigned char **) ptr2)) + 0x830)),
                      *((void **) (((unsigned char *) obj) + 0x100)));
        ptr2 = ((unsigned char *) obj) + 0x100;
        return 1;
    }
    return 0;
}
