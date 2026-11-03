/* star_designer_5: 2 functions, module ov129
 * mwccarm 1.2/base -O4,s
 * func_ov129_0229d8a0 @ 0x0229d8a0, 0x104 bytes, Thumb
 * func_ov129_0229d780 @ 0x0229d780, 0x120 bytes, Thumb
 */

extern "C" int data_ov129_0229dcc8;
extern "C" void func_ov129_0229d218(void *);
extern "C" void func_ov129_0229d1b8(void *);

class UnkStruct_0229d8a0 {
  public:
    virtual void vfunc_00();
    char pad_04[0x88];
    unsigned char index;
};

typedef void (UnkStruct_0229d8a0::*MemFn)();

extern "C" MemFn data_ov129_0229dba0;
extern "C" MemFn data_ov129_0229dbf8;
extern "C" MemFn data_ov129_0229dc10;
extern "C" MemFn data_ov129_0229db90;
extern "C" MemFn data_ov129_0229db98;
extern "C" MemFn data_ov129_0229dc28;
extern "C" MemFn data_ov129_0229dc20;
extern "C" MemFn data_ov129_0229dc18;
extern "C" MemFn data_ov129_0229dbc0;
extern "C" MemFn data_ov129_0229dc08;
extern "C" MemFn data_ov129_0229dc00;
extern "C" MemFn data_ov129_0229dbe8;
extern "C" MemFn data_ov129_0229dd24[12];

class UnkStruct_0229d780 {
  public:
    char pad_00[0x8d];
    unsigned char idx;
};

typedef void (UnkStruct_0229d780::*PMF)();

extern const PMF data_ov129_0229db68;
extern const PMF data_ov129_0229dbd8;
extern const PMF data_ov129_0229db60;
extern const PMF data_ov129_0229dbc8;
extern const PMF data_ov129_0229db58;
extern const PMF data_ov129_0229db70;
extern const PMF data_ov129_0229db78;
extern const PMF data_ov129_0229dba8;
extern const PMF data_ov129_0229db80;
extern const PMF data_ov129_0229db88;
extern const PMF data_ov129_0229dbb0;
extern const PMF data_ov129_0229dbb8;
extern const PMF data_ov129_0229dbd0;
extern const PMF data_ov129_0229dbe0;
extern const PMF data_ov129_0229dbf0;

extern "C" int func_ov129_0229d8a0(UnkStruct_0229d8a0 *obj)
{
    if (!(data_ov129_0229dcc8 & 1)) {
        data_ov129_0229dd24[0] = data_ov129_0229dba0;
        data_ov129_0229dd24[1] = data_ov129_0229dbf8;
        data_ov129_0229dd24[2] = data_ov129_0229dc10;
        data_ov129_0229dd24[3] = data_ov129_0229db90;
        data_ov129_0229dd24[4] = data_ov129_0229db98;
        data_ov129_0229dd24[5] = data_ov129_0229dc28;
        data_ov129_0229dd24[6] = data_ov129_0229dc20;
        data_ov129_0229dd24[7] = data_ov129_0229dc18;
        data_ov129_0229dd24[8] = data_ov129_0229dbc0;
        data_ov129_0229dd24[9] = data_ov129_0229dc08;
        data_ov129_0229dd24[10] = data_ov129_0229dc00;
        data_ov129_0229dd24[11] = data_ov129_0229dbe8;
        data_ov129_0229dcc8 |= 1;
    }
    func_ov129_0229d218(obj);
    (obj->*data_ov129_0229dd24[obj->index])();
    func_ov129_0229d1b8(obj);
    return 1;
}

extern "C" void func_ov129_0229d780(UnkStruct_0229d780 *obj)
{
    static int flag = 0;
    static PMF arr[15];
    if (!(flag & 1)) {
        arr[0] = data_ov129_0229db68;
        arr[1] = data_ov129_0229dbd8;
        arr[2] = data_ov129_0229db60;
        arr[3] = data_ov129_0229dbc8;
        arr[4] = data_ov129_0229db58;
        arr[5] = data_ov129_0229db70;
        arr[6] = data_ov129_0229db78;
        arr[7] = data_ov129_0229dba8;
        arr[8] = data_ov129_0229db80;
        arr[9] = data_ov129_0229db88;
        arr[10] = data_ov129_0229dbb0;
        arr[11] = data_ov129_0229dbb8;
        arr[12] = data_ov129_0229dbd0;
        arr[13] = data_ov129_0229dbe0;
        arr[14] = data_ov129_0229dbf0;
        flag |= 1;
    }
    (obj->*arr[obj->idx])();
}
