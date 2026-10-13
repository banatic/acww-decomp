/* func_ov048_02260b64 @ 0x02260b64, 0x124 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x40];
    void *unk_40;
    char pad_44[0x74];
    void *unk_B8;
} ObjStruct;

extern void func_02073044(ObjStruct *obj);
extern int func_020ec920(void);
extern int func_ov048_02260f64(ObjStruct *obj, int arg2);
extern void func_02074120(void);
extern void func_0208602c(void);
extern void func_020860c4(void);
extern int func_02087f30(void);
extern void func_020984e8(void);
extern void func_02099688(void);
extern int func_0208829c(void);
extern void func_02088284(void);
extern int func_02074150(void);
extern void func_02088290(void);
extern int func_020a6f44(void);
extern int func_02075dcc(void *addr, int arg2);
extern int data_020ccf94;
extern void func_020732b4(int arg1, int arg2);
extern void func_020a6f10(int arg);
extern void func_020a6ef0(int arg);
extern void func_020ec260(void);
extern void func_020a13c4(void);
extern void func_ov048_02262378(ObjStruct *obj);
extern void func_ov048_022616b8(ObjStruct *obj, int arg2);
extern void func_ov048_022635f4(void *ptr, int arg2);
extern int func_020eba18(void);
extern int func_ov048_022609a4(ObjStruct *obj);
extern void func_ov048_02260e28(ObjStruct *obj, int arg2, int arg3);

void func_ov048_02260b64(ObjStruct *obj)
{
    int flag, val, r, r2;

    func_02073044(obj);
    flag = !func_020ec920();
    if (func_ov048_02260f64(obj, flag) != 0) {
        func_02074120();
        func_0208602c();
        func_020860c4();
        if (func_02087f30() != 0) {
            func_020984e8();
            func_02099688();
            if (func_0208829c() != 0) {
                func_020984e8();
                func_02099688();
                func_02088284();
            }
        }
        return;
    }

    val = func_02074150();
    if (val == 5) {
        func_0208602c();
        func_020860c4();
        if (func_02087f30() != 0) {
            func_020984e8();
            func_02099688();
            if (func_0208829c() == 0) {
                func_020984e8();
                func_02099688();
                func_02088290();
            }
        }
        r = func_020a6f44();
        if (func_02075dcc((char *) obj + 0x812, r) != 0) {
            func_020732b4(data_020ccf94, 0);
            func_020a6f10(0);
            func_020a6ef0(0);
            func_020ec260();
            func_020a13c4();
            func_02074120();
            *(int *) ((char *) obj->unk_40 + 0x14) = 0;
            func_ov048_02262378(obj);
            func_ov048_022616b8(obj, 0);
            func_ov048_022635f4(obj->unk_B8, 0xC);
        }
        return;
    }

    if (val != 6) {
        if (func_020eba18() != 0x800c) {
            return;
        }
    }
    func_02074120();
    if (func_020eba18() == 0x800c) {
        func_ov048_02260e28(obj, 0x79, 1);
    } else {
        r2 = func_ov048_022609a4(obj);
        func_ov048_02260e28(obj, r2, 0);
    }
}
