#ifndef CPP_OV050_OBJ_OV050_02265B14_H
#define CPP_OV050_OBJ_OV050_02265B14_H

// Scene object of ov050, the member at 0x658 of Obj_ov050_02265a60 (vtable 02265b14, constructor
// 022636c8, destructors 022636b0/02263690). Its main base is constructed by 0202eb70
// (vtable family 0x020d8bd4). Each dispatcher matches unk_1E against a key table and
// passes its argument on to the handler.
class Obj_ov050_02265b14 {
  public:
    virtual ~Obj_ov050_02265b14();
    char pad_04[0x1e - 4];
    unsigned char unk_1E;
    char pad_1F[0x40 - 0x1f];
    int unk_40;
    char pad_44[0xb0 - 0x44];
    unsigned int unk_B0;
    int unk_B4;
    char pad_B8[0xd0 - 0xb8];
    int unk_D0;

    // states run by func_ov050_02260e80, matched against unk_1E
    void func_ov050_02260e50(int arg);

    // states run by func_ov050_02261560, matched against unk_1E
    void func_ov050_022614c8(int arg);
    void func_ov050_02261494(int arg);
    void func_ov050_02261480(int arg);
    void func_ov050_022610b0(int arg);
    void func_ov050_022613d8(int arg);
    void func_ov050_02261390(int arg);
    void func_ov050_02261200(int arg);
    void func_ov050_022612f4(int arg);
    void func_ov050_02261174(int arg);
    void func_ov050_02261138(int arg);
    void func_ov050_02261094(int arg);
    void func_ov050_02261078(int arg);
    void func_ov050_0226105c(int arg);
    void func_ov050_02261040(int arg);

    // states run by func_ov050_02262be8, matched against unk_1E
    void func_ov050_02262bac(int arg);
    void func_ov050_02262b58(int arg);
    void func_ov050_02262b08(int arg);
    void func_ov050_02262ad8(int arg);
    void func_ov050_02262acc(int arg);
    void func_ov050_02262ab8(int arg);
    void func_ov050_02262a28(int arg);
    void func_ov050_022629ec(int arg);
    void func_ov050_02262970(int arg);
    void func_ov050_02262910(int arg);
    void func_ov050_022628c8(int arg);
    void func_ov050_0226288c(int arg);
    void func_ov050_02262850(int arg);
    void func_ov050_022627d4(int arg);
    void func_ov050_02262798(int arg);
    void func_ov050_02262734(int arg);
    void func_ov050_02262700(int arg);
    void func_ov050_022626c8(int arg);
    void func_ov050_0226265c(int arg);
    void func_ov050_02262628(int arg);
    void func_ov050_02262618(int arg);

    void func_ov050_02260e80(int arg);
    void func_ov050_02261560(int arg);
    void func_ov050_02262be8(int arg);

    // picks func_ov050_02261560, func_ov050_02260f28 or func_ov050_02260e80
    void func_ov050_02261830(int param);
};

#endif
