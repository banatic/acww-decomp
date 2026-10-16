/* A class of overlay 4's room objects (vtable 0x02251ec4, receiver part 0x02251f70, 0x88c bytes)
 * that shows one of the shop's eight designs (design_assets.h): the room items 0x3e04-0x3e23,
 * four codes (variants) a design. Once the model is bound and the shop's texture of that design
 * exists (in scene 10 only), it is put on the model's material "w"; until then the start is
 * tried again. From then on a sound emitter of its own plays sound 0x50 at the object's centre
 * each time that design of the shop changes. */
#ifndef CLEAN_OV004_ROOM_OBJECT_SHOP_DESIGN_H
#define CLEAN_OV004_ROOM_OBJECT_SHOP_DESIGN_H

#include "types.h"

#include "room_object.h"

typedef struct ShopDesignObject {
    RoomObject base;
    s32 design; /* 0 to 7, the shop's design shown */
    /* A sound emitter (the class with vtable 0x0213f074, main/sound_emitter.h), built by
     * func_020f5958. */
    u8 emitter[0x40];
    u8 has_sound; /* the emitter is in use (once the design was put on) */
    u8 unk_889[3];
} ShopDesignObject;

int ShopDesignObject_Vfunc0C(ShopDesignObject *object);
int ShopDesignObject_Update(ShopDesignObject *object);
int ShopDesignObject_Start(ShopDesignObject *object);
ShopDesignObject *ShopDesignObject_Delete(ShopDesignObject *object);
ShopDesignObject *ShopDesignObject_Destroy(ShopDesignObject *object);
ShopDesignObject *ShopDesignObject_Construct(ShopDesignObject *object);
void ShopDesignObject_Create(void);

#endif
