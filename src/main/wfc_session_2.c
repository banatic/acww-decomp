/* wfc_session_2: 9 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209ffb0 @ 0x0209ffb0, 0x80 bytes, Thumb
 * func_0209ff54 @ 0x0209ff54, 0x5c bytes, Thumb
 * func_0209ff0c @ 0x0209ff0c, 0x48 bytes, Thumb
 * func_0209fea4 @ 0x0209fea4, 0x68 bytes, Thumb
 * func_0209fe40 @ 0x0209fe40, 0x64 bytes, Thumb
 * func_0209fe1c @ 0x0209fe1c, 0x24 bytes, Thumb
 * func_0209fdf8 @ 0x0209fdf8, 0x24 bytes, Thumb
 * func_0209fdd4 @ 0x0209fdd4, 0x24 bytes, Thumb
 * func_0209fdac @ 0x0209fdac, 0x28 bytes, Thumb
 */

extern int func_020ec1e8(void);
extern int func_020749c4(void);
extern int func_020984e8(void);
extern int func_0209985c(int);
extern void func_0209fd54(void);
extern void func_0209fcd8(void);
extern void func_0209fc60(void);
extern void func_020a01f8(void);
extern int func_020a1518(void);
extern int func_020682e0(int);
extern void func_02068358(int);
extern void func_02068434(int);
extern void func_0206844c(int, unsigned char *, unsigned char *);
extern unsigned char data_020e3c2c[];
extern int data_021f3278;
extern int data_020e3800;
extern int data_020e3bf0;
extern int func_02088208(void *);
extern int func_020881ac(void *);
extern int func_020508fc(void *, int, int);
extern void func_020881b8(void *, int);
extern void func_02073100(void);
extern int func_020eb384(void *, void *, int, int);
extern int data_020e3bb0;
extern int data_021f40a4;
extern int func_020eb188(void *, void *, int, int);
extern int func_0209f150(void *, int);
extern unsigned char *strcpy(void *, void *);
extern char *func_0212d914(void *, void *);
extern int func_020eb108(void *, const void *, unsigned int, unsigned int);
extern void *data_020e3808;
extern void *data_020e380c;
extern unsigned char data_021dc7a8[];
extern unsigned char data_021f3d90[];
extern void *data_020e3804;
extern unsigned char data_021f3cbc[];
extern int func_020eb070(void);
extern unsigned char data_021f3c14;
extern char data_021f3c04;
extern unsigned char data_021f3c18;
extern int __arm func_020eb2ec(void);
extern void func_02088250(void *ptr);

int func_0209ffb0(void *receiver)
{
    int tested_value0;
    int flag = 0;
    int ret;
    unsigned char byte;

    if (func_020ec1e8() == 3 || func_020ec1e8() == 4) {
        flag = 1;
    }

    ret = func_020749c4();

    if (flag) {
        if ((tested_value0 = (int) (func_020984e8()))) {
            int idx = func_0209985c(tested_value0);
            if (idx >= 0 && idx < 4) {
                func_0209fd54();
                func_0209fcd8();
                func_0209fc60();
                func_020a01f8();
                if (func_020a1518()) {
                    int handle = func_020682e0(0);
                    func_02068358(handle);
                    func_02068434(handle);
                    byte = 2;
                    func_0206844c(handle, &byte, data_020e3c2c);
                }
            }
        }
    }

    return ret;
}

int func_0209ff54(void)
{
    void *work;
    int v1, v2, val;

    work = &data_021f3278;
    if (func_02088208(work) == 3) {
        v1 = func_020881ac(work);
        v2 = func_020508fc(work, 0x238, v1);
        func_020881b8(work, v2);
        val = data_020e3800;
        func_02073100();
        func_020eb384(&data_020e3bf0, work, 0x238, val);
        return 1;
    }
    return 0;
}

int func_0209ff0c(void)
{
    int val;

    if (func_02088208((void *) &data_021f3278) == 0) {
        val = data_020e3800;
        func_02073100();
        if (func_020eb188((void *) &data_020e3bb0, (void *) &data_021f40a4, 0x238, val) == 0) {
            return 0;
        } else {
            return 1;
        }
    }
    return 0;
}

int func_0209fea4(void)
{
    char buffer[128];
    unsigned int val;

    if (func_0209f150((void *) data_021dc7a8, 0x14)) {
        return 0;
    }

    strcpy(buffer, data_020e3808);
    func_0212d914(buffer, data_020e380c);
    val = (*(unsigned int *) &data_020e3800);
    func_02073100();

    return func_020eb108(buffer, (void *) data_021f3d90, 0x114, val) ? 1 : 0;
}

int func_0209fe40(void)
{
    char buf[0x80];
    int val;

    if (func_0209f150((void *) data_021dc7a8, 0x14) == 0) {
        goto body;
    } else {
        return 0;
    }

body:
    strcpy(buf, (void *) data_020e3808);
    func_0212d914(buf, (void *) data_020e3804);
    val = data_020e3800;
    func_02073100();
    if (func_020eb108(buf, (void *) data_021f3cbc, 0xd2, val) != 0) {
        return 1;
    } else {
        return 0;
    }
}

int func_0209fe1c(void)
{
    func_02073100();
    if (func_020eb070()) {
        data_021f3c14 = 1;
        return 1;
    }
    return 0;
}

int func_0209fdf8(void)
{
    if ((func_02073100(), func_020eb070())) {
        data_021f3c04 = 1;
        return 1;
    }
    return 0;
}

int func_0209fdd4(void)
{
    if ((func_02073100(), func_020eb070()) != 0) {
        data_021f3c18 = 1;
        return 1;
    }
    return 0;
}

int func_0209fdac(void)
{
    func_02073100();
    if (func_020eb2ec() != 0) {
        func_02088250(&data_021f3278);
        return 1;
    }
    return 0;
}
