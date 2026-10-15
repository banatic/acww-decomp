/* func_ov048_02260b64 @ 0x02260b64, 0x124 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x40];
    void *unk_40;
    char pad_44[0x74];
    void *unk_B8;
} ObjStruct;

extern unsigned int func_02073044(void);
extern int func_020ec920(void);
extern int func_ov048_02260f64(ObjStruct *obj, int arg2);
extern void func_02074120(void);
extern int func_0208602c(void);
extern int func_020860c4(int);
extern int func_02087f30(void *);
extern int func_020984e8(void);
extern unsigned int func_02099688(unsigned int);
extern int func_0208829c(void *);
extern void func_02088284(void *);
extern int func_02074150(void);
extern void func_02088290(void *);
extern int func_020a6f44(void);
extern int func_02075dcc(void *addr, int arg2);
extern int data_020ccf94;
extern void func_020732b4(int arg1, int arg2);
extern void func_020a6f10(int arg);
extern void func_020a6ef0(int arg);
extern int func_020ec260(void);
extern void func_020a13c4(unsigned char value);
extern void func_ov048_02262378(ObjStruct *obj);
extern void func_ov048_022616b8(ObjStruct *obj, int arg2);
extern void func_ov048_022635f4(void *ptr, int arg2);
extern int func_020eba18(void);
extern int func_ov048_022609a4(void);
extern void func_ov048_02260e28(ObjStruct *obj, int arg2, int arg3);

void func_ov048_02260b64(ObjStruct *obj)
{
    int flag, val, r, r2;

    func_02073044();
    flag = !func_020ec920();
    if (func_ov048_02260f64(obj, flag) != 0) {
        func_02074120();
        if (func_02087f30((void *) func_020860c4((int) func_0208602c())) != 0) {
            if (func_0208829c((void *) func_02099688((unsigned int) func_020984e8())) != 0) {
                func_02088284((void *) func_02099688((unsigned int) func_020984e8()));
            }
        }
        return;
    }

    val = func_02074150();
    if (val == 5) {
        if (func_02087f30((void *) func_020860c4((int) func_0208602c())) != 0) {
            if (func_0208829c((void *) func_02099688((unsigned int) func_020984e8())) == 0) {
                func_02088290((void *) func_02099688((unsigned int) func_020984e8()));
            }
        }
        r = func_020a6f44();
        if (func_02075dcc((char *) obj + 0x812, r) != 0) {
            func_020732b4(data_020ccf94, 0);
            func_020a6f10(0);
            func_020a6ef0(0);
            asm {
                bl func_020ec260
                bl func_020a13c4
            }
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
        asm {
            mov r0, obj
        }
        r2 = func_ov048_022609a4();
        func_ov048_02260e28(obj, r2, 0);
    }
}
