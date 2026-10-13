/* func_02090ef4 @ 0x02090ef4, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02090968(void *);
extern void func_020907d8(void *);
extern void func_0209031c(void *);
extern void NNS_FndDestroyFrmHeap(void *);
extern void func_020e9898(void *);

extern void *data_021d52cc;
extern void *data_021d52d0;
extern void *data_021d52c4;

int func_02090ef4(void *obj)
{
    if (data_021d52cc) {
        NNS_FndDestroyFrmHeap(data_021d52cc);
        data_021d52cc = 0;
    }
    if (data_021d52d0) {
        func_02090968((char *) obj + 0x58);
        func_020e9898(data_021d52d0);
        data_021d52d0 = 0;
    }
    func_020907d8((char *) obj + 0x35c);
    func_0209031c((char *) obj + 0x181c);
    data_021d52c4 = 0;
    return 1;
}
