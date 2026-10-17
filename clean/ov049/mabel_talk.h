/* Mabel's talk scene (MabelTalk, mabel.h; class vtable data_ov049_022634b4, derived from the
 * scene class 0x020d9ff8).
 *
 * Its vtable slots, beyond the scene's: 0x00 and 0x04 its destructors, 0x14 a line ended
 * (MabelTalk_OnLineEnded), 0x18 the player's answer (MabelTalk_OnAnswer), 0x78 the line the
 * talk starts with (MabelTalk_Line), 0x80 before each step of the scene and 0x84 a command of
 * the scene ended (the sequences, below).
 *
 * Its message files (data_ov049_02263298): "sp_npc_ysister" (her own lines), "sp_npc_drama4"
 * (the dated events of kind 2) and "sp_etc_sequence4" (while a game is being started anew).
 * The answers and the ends of lines of her own file go to handlers in tables keyed by the line
 * shown (the receiver's message, byte 0x1e); those of the other files to one handler each.
 *
 * What the talk does, by line (MABEL_LINE_*):
 * - an item on display (talk mode 4): its price and name are put in (line 0x28), then the
 *   choices to buy it, to try it on (not for umbrellas) or not (MabelTalk_OfferItemChoices).
 *   Bought (MabelTalk_Buy) when the player has a free pocket slot and the bells; tried on, the
 *   player wears it (the camera's mode 4) until the try-on ends, when the item worn before is
 *   put back on and the player is asked again (line 0x2d);
 * - one of the shop's designs (talk mode 5): its title and who made it (lines 0x31 to 0x33);
 * - the player's clothes sold to her: the pockets' screen 2 in mode 0x1e, the price of the
 *   items picked (a quarter of each one's) offered and paid (line 0x1b);
 * - the player's designs: one shown in the shop (mode 5, sequence 3), one of the shop's
 *   bought (mode 7, sequence 4) or swapped (mode 8, sequence 5); the player wearing the design
 *   is dressed again;
 * - for 350 bells, one of the player's designs (the screen in mode 4) given a kind at random
 *   from the answer to line 0x10 (MabelTalk_SetDesignKind);
 * - a villager's errand: the item 0x155f or 0x1560 handed to her (sequence 9).
 *
 * Its sequences (MabelTalk.sequence), a member function each from data_ov049_022633b0 (filled
 * at start-up), run once when a command of the scene ends, or before each step when the
 * entry's flag (byte 8, set in the overlay's data) is set (sequences 7 and 8). */
#ifndef CLEAN_OV049_MABEL_TALK_H
#define CLEAN_OV049_MABEL_TALK_H

#include "mabel.h"
#include "types.h"

enum MabelTalkSequence {
    MABEL_TALK_SEQUENCE_NONE = 0,
    MABEL_TALK_SEQUENCE_DESIGN_PICKED = 1, /* MabelTalk_SayDesignPicked */
    MABEL_TALK_SEQUENCE_SCREEN_B = 2,      /* MabelTalk_SayAfterScreenB */
    MABEL_TALK_SEQUENCE_SHOW_DESIGN = 3,   /* MabelTalk_ShowDesign */
    MABEL_TALK_SEQUENCE_BUY_DESIGN = 4,    /* MabelTalk_BuyDesign */
    MABEL_TALK_SEQUENCE_SWAP_DESIGN = 5,   /* MabelTalk_SwapDesign */
    MABEL_TALK_SEQUENCE_PRICE_SALE = 6,    /* MabelTalk_PriceSale */
    MABEL_TALK_SEQUENCE_TRYING_ON = 7,     /* MabelTalk_WatchTryOn, each step */
    MABEL_TALK_SEQUENCE_TRIED_ON = 8,      /* MabelTalk_EndTryOn, each step */
    MABEL_TALK_SEQUENCE_ERRAND = 9,        /* MabelTalk_TakeErrand */
    MABEL_TALK_SEQUENCES = 10
};

/* A sequence's function in data_ov049_022633b0. */
typedef struct MabelTalkStep {
    MemberPointer run; /* void (talk) */
    u8 each_step;      /* 0x08: run before each step, else when a command ends */
    u8 unk_09[3];
} MabelTalkStep;

/* What its line function gives: the message file's name and the line. */
typedef struct MabelTalkLine {
    const char *text;
    u8 message;
    u8 unk_05[3];
} MabelTalkLine;

/* A list of the answers offered (MabelTalk_OfferChoices): their messages and their count. */
typedef struct MabelTalkChoices {
    const u8 *messages;
    u8 count;
    u8 unk_05[3];
} MabelTalkChoices;

/* The lines of "sp_npc_ysister" named in the code. */
#define MABEL_LINE_FIRST 0x00            /* talk mode 0 */
#define MABEL_LINE_AGAIN 0x01            /* talk mode 1 */
#define MABEL_LINE_SPOT_TAKEN 0x02       /* talk mode 3 */
#define MABEL_LINE_TALKED 0x04           /* talk mode 2 */
#define MABEL_LINE_0B 0x0b               /* its first answer costs 350 bells */
#define MABEL_LINE_NO_BELLS_FEE 0x0d     /* the player cannot pay 350 bells */
#define MABEL_LINE_FEE_OK 0x0e           /* ends opening the screen in mode 4 */
#define MABEL_LINE_NO_DESIGN 0x0f        /* no design picked on that screen */
#define MABEL_LINE_DESIGN_KIND 0x10      /* a design picked: its answer gives its kind */
#define MABEL_LINE_11 0x11               /* ends opening the screen in mode 0xb */
#define MABEL_LINE_FEE 0x12              /* ends taking 350 bells */
#define MABEL_LINE_SELL 0x14             /* ends opening the screen of the clothes to sell */
#define MABEL_LINE_NO_SALE 0x15          /* nothing confirmed on it */
#define MABEL_LINE_NOTHING_TO_SELL 0x17  /* the items picked are worth nothing */
#define MABEL_LINE_SOLD 0x1a             /* the bells fit the wallet: paid */
#define MABEL_LINE_SALE_PRICE 0x1b       /* the price offered for the items picked */
#define MABEL_LINE_SOLD_BAGS 0x1e        /* the bells go into bags too: paid at its end */
#define MABEL_LINE_SWAPPED 0x21          /* a design swapped */
#define MABEL_LINE_NO_PICK 0x22          /* no design picked on the screen */
#define MABEL_LINE_SWAP 0x23             /* ends opening the screen in mode 8 */
#define MABEL_LINE_SHOWN 0x24            /* a design of the player's shown in the shop */
#define MABEL_LINE_BUY_DESIGN 0x26       /* ends opening the screen in mode 7 */
#define MABEL_LINE_DESIGN_BOUGHT 0x27    /* a design of the shop's copied to the player's */
#define MABEL_LINE_ITEM_PRICE 0x28       /* talk mode 4: the item's price and name */
#define MABEL_LINE_BOUGHT 0x29           /* the item bought */
#define MABEL_LINE_NO_BELLS 0x2b         /* the player cannot pay for the item */
#define MABEL_LINE_NO_ROOM 0x2c          /* no free pocket slot */
#define MABEL_LINE_TRIED_ON 0x2d         /* after a try-on: buy it or not */
#define MABEL_LINE_ERRAND 0x2e           /* a villager's errand for her */
#define MABEL_LINE_ERRAND_TAKEN 0x2f     /* the errand's item handed over */
#define MABEL_LINE_NO_ERRAND 0x30        /* none handed over */
#define MABEL_LINE_DESIGN_OWN 0x31       /* talk mode 5: a design the player made */
#define MABEL_LINE_DESIGN_TOWN 0x32      /* made by another player of the town */
#define MABEL_LINE_DESIGN_ELSEWHERE 0x33 /* made in another town */
#define MABEL_LINE_SHOW_DESIGN 0x36      /* ends opening the screen in mode 5 */
#define MABEL_LINE_LINKED_ANSWER_0 0x37  /* linked, the answer 0 at the lines of 022617b4 */
#define MABEL_LINE_NO_ROOM_SALE 0x38     /* the bells fit nowhere */
#define MABEL_LINE_LINKED_ANSWER_2 0x1c  /* linked, the answer 2 at those lines */

/* The talk's questions and its class (mabel_talk.c). */
unsigned long MabelTalk_Mode(MabelTalk *talk);
void MabelTalk_SetMode(MabelTalk *talk, unsigned long mode);
void MabelTalk_Begin(MabelTalk *talk, Mabel *owner);
void *MabelTalk_DestructDelete(MabelTalk *talk);
MabelTalk *MabelTalk_Destruct(MabelTalk *talk);
void *MabelTalk_Construct(void *talk);
void MabelTalk_Line(MabelTalk *talk, MabelTalkLine *out);

/* The deals. */
void MabelTalk_SetDesignKind(int unused, int kind);
void MabelTalk_Buy(MabelTalk *talk);
void MabelTalk_OfferChoices(MabelTalk *talk, const MabelTalkChoices *choices, int cancel);

/* The sequences. */
void MabelTalk_SetSequence(MabelTalk *talk, unsigned long sequence);
void MabelTalk_RunCommandSequence(MabelTalk *talk);
void MabelTalk_RunStepSequence(MabelTalk *talk);
void MabelTalk_TakeErrand(MabelTalk *talk);
void MabelTalk_EndTryOn(MabelTalk *talk);
void MabelTalk_WatchTryOn(MabelTalk *talk);
void MabelTalk_PriceSale(MabelTalk *talk);
void MabelTalk_SwapDesign(MabelTalk *talk);
void MabelTalk_BuyDesign(MabelTalk *talk);
void MabelTalk_ShowDesign(MabelTalk *talk);
void MabelTalk_SayAfterScreenB(MabelTalk *talk);
void MabelTalk_SayDesignPicked(MabelTalk *talk);

/* The answers. */
void MabelTalk_OnAnswer(MabelTalk *talk, int arg);
void MabelTalk_OnPlainAnswer(MabelTalk *talk);
void MabelTalk_OnDramaAnswer(MabelTalk *talk);
void MabelTalk_OnAnswerErrand(MabelTalk *talk, int answer);
unsigned short MabelTalk_IsErrandItem(unsigned short *item, int state);
void MabelTalk_OnAnswerTriedOn(MabelTalk *talk, int answer);
void MabelTalk_OnAnswerItem(MabelTalk *talk, int answer);
void MabelTalk_OnAnswerNoSale(int unused, int answer);
void MabelTalk_OnAnswerSalePrice(MabelTalk *talk, int answer);
void MabelTalk_OnAnswerDesignKind(MabelTalk *talk, int answer);
void MabelTalk_OnAnswerFee(MabelTalk *talk, int answer);
void MabelTalk_OnAnswerLinked(MabelTalk *talk, int answer);

/* The ends of lines. */
void MabelTalk_OnLineEnded(MabelTalk *talk, void *arg);
void MabelTalk_OnPlainLineEnded(MabelTalk *talk);
void MabelTalk_OnOtherLineEnded(void);
void MabelTalk_OpenSwap(MabelTalk *talk);
void MabelTalk_OpenBuyDesign(MabelTalk *talk);
void MabelTalk_OpenShowDesign(MabelTalk *talk);
void MabelTalk_OfferItemChoices(MabelTalk *talk);
void MabelTalk_PaySale(MabelTalk *talk);
void MabelTalk_OpenSell(MabelTalk *talk);
void MabelTalk_TakeFee(MabelTalk *talk);
void MabelTalk_OpenScreenB(MabelTalk *talk);
void MabelTalk_OpenDesignPick(MabelTalk *talk);

#endif
