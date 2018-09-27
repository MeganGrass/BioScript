#pragma once


// Set, Ck					// Flg_addr
#define FLAG_SYSTEM		0	// System_flg
#define FLAG_STATUS		1	// Status_flg
#define FLAG_STOP		2	// Stop_flg
#define FLAG_SCENARIO	3	// Scenario_flg
#define FLAG_COMMON		4	// Common_flg
#define FLAG_ROOM		5	// Room_flg
#define FLAG_ENEMY		6	// Enemy_flg
#define FLAG_ENEMY_2	7	// Enemy_flg2
#define FLAG_ITEM		8	// Item_flg
#define FLAG_MAP		9	// Map_flg
#define FLAG_USE		10	// Use_flg
#define FLAG_MESSAGE	11	// MojiPrint.Mess_flg
#define FLAG_ROOM_ENEMY	12	// Room_enemy_flg
#define FLAG_PBF00		13	// Pri_be_flg
#define FLAG_PBF01		14	// Pri_be_flg+0x10
#define FLAG_PBF02		15	// Pri_be_flg+0x20
#define FLAG_PBF03		16	// Pri_be_flg+0x30
#define FLAG_PBF04		17	// Pri_be_flg+0x40
#define FLAG_PBF05		18	// Pri_be_flg+0x50
#define FLAG_PBF06		19	// Pri_be_flg+0x60
#define FLAG_PBF07		20	// Pri_be_flg+0x70
#define FLAG_PBF08		21	// Pri_be_flg+0x80
#define FLAG_PBF09		22	// Pri_be_flg+0x90
#define FLAG_PBF0A		23	// Pri_be_flg+0xA0
#define FLAG_PBF0B		24	// Pri_be_flg+0xB0
#define FLAG_PBF0C		25	// Pri_be_flg+0xC0
#define FLAG_PBF0D		26	// Pri_be_flg+0xD0
#define FLAG_PBF0E		27	// Pri_be_flg+0xE0
#define FLAG_PBF0F		28	// Pri_be_flg+0xF0
#define FLAG_ZAPPING	29	// Zapping_flg
#define FLAG_RBJ_SET	30	// Rbj_set_flg
#define FLAG_KEY		31	// Key_flg
#define FLAG_MAP_C		32	// Map_c_flg
#define FLAG_MAP_I		33	// Map_i_flg
#define FLAG_ITEM_2		34	// Item_flg2

// AOT_SET
#define SCE_NOTHING		0x00
#define SCE_DOOR		0x01
#define SCE_ITEM		0x02
#define SCE_NORMAL		0x03
#define SCE_MESSAGE		0x04
#define SCE_EVENT		0x05
#define SCE_FLAG_CHG	0x06
#define SCE_WATER		0x07
#define SCE_MOVE		0x08
#define SCE_SAVE		0x09
#define SCE_ITEMBOX		0x0A
#define SCE_DAMAGE		0x0B
#define SCE_STATUS		0x0C
#define SCE_HIKIDASHI	0x0D	// Drawer
#define SCE_WINDOWS		0x0E

// AOT_SET (Prototype)
#define SCE_NOTHING_P	0x00
#define SCE_MESSAGE_P	0x01
#define SCE_DOOR_P		0x02
#define SCE_EVENT_P		0x03
#define SCE_FLAG_CHG_P	0x04
#define SCE_NORMAL_P	0x05
#define SCE_STATUS_P	0x06
// Modify Enemy Position?	0x07
#define SCE_WATER_P		0x08
#define SCE_ITEM_P		0x09
#define SCE_DAMAGE_P	0x0A
#define SCE_MOVE_P		0x0B
#define SCE_STAIRS_X	0x0C	// Prototype, only
#define SCE_STAIRS_Z	0x0D	// Prototype, only

// ATARI
#define SAT_AUTOMATIC	0x00
#define SAT_PLAYER		0x01
#define SAT_ENEMY		0x02	// Brad Vickers
#define SAT_04			0x04	// ???
#define SAT_08			0x08	// ???
#define SAT_MANUAL		0x10
#define SAT_FRONT		0x20
#define SAT_UNDER		0x40
#define SAT_80			0x80	// ???

// WORK_SET, KAGE_SET
#define WORK_NONE		0x00
#define WORK_PLAYER		0x01
#define WORK_SPLAYER	0x02
#define WORK_ENEMY		0x03
#define WORK_OBJECT		0x04
#define WORK_DOOR		0x05
#define WORK_ALL		0x06
#define WORK_PL_PARTS	0x80
#define WORK_SPL_PARTS	0xA0
#define WORK_EM_PARTS	0xC0
#define WORK_OM_PARTS	0xE0

// SPD_SET
#define SPEED_X_POS		0x00
#define SPEED_Y_POS		0x01
#define SPEED_Z_POS		0x02
#define SPEED_X_DIR		0x03
#define SPEED_Y_DIR		0x04
#define SPEED_Z_DIR		0x05
#define SPEED_X_POS2	0x06
#define SPEED_Y_POS2	0x07
#define SPEED_Z_POS2	0x08
#define SPEED_X_DIR2	0x09
#define SPEED_Y_DIR2	0x0A
#define SPEED_Z_DIR2	0x0B

// MEMBER SET/2, COPY, CMP and CALC/2
#define MEMBER_POINTER		0x00
#define MEMBER_BE_FLAG		0x01
#define MEMBER_ROUTINE0		0x02
#define MEMBER_ROUTINE1		0x03
#define MEMBER_ROUTINE2		0x04
#define MEMBER_ROUTINE3		0x05
#define MEMBER_ID			0x06
#define MEMBER_TYPE			0x07
#define MEMBER_OBJ_NO		0x08
#define MEMBER_SCE_NO		0x09
#define MEMBER_ATTRIBUTE	0x0A
#define MEMBER_X_POS		0x0B
#define MEMBER_Y_POS		0x0C
#define MEMBER_Z_POS		0x0D
#define MEMBER_X_DIR		0x0E
#define MEMBER_Y_DIR		0x0F
#define MEMBER_Z_DIR		0x10
#define MEMBER_nFLOOR		0x11
#define MEMBER_STATUS_FLAG	0x12
#define MEMBER_GROUND		0x13
#define MEMBER_X_DEST		0x14
#define MEMBER_Z_DEST		0x15
#define MEMBER_SCE_FLAG		0x16
#define MEMBER_SCE_FREE0	0x17
#define MEMBER_SCE_FREE1	0x18
#define MEMBER_SCE_FREE2	0x19
#define MEMBER_SCE_FREE3	0x1A
#define MEMBER_X_SPEED0		0x1B
#define MEMBER_X_SPEED1		0x1C
#define MEMBER_Y_SPEED		0x1D
#define MEMBER_Z_SPEED		0x1E
#define MEMBER_HOKAN_FLAG	0x1F
#define MEMBER_OBJ_OFS_X	0x20
#define MEMBER_OBJ_OFS_Y	0x21
#define MEMBER_OBJ_OFS_Z	0x22
#define MEMBER_OBJ_W		0x23
#define MEMBER_OBJ_H		0x24
#define MEMBER_OBJ_D		0x25
#define MEMBER_PARTS_POS_Y	0x26
#define MEMBER_SCA_OLD_X	0x27
#define MEMBER_SCA_OLD_Z	0x28
#define MEMBER_FREE0		0x29
#define MEMBER_FREE1		0x2A
#define MEMBER_DAMAGE_CNT	0x2B

// PLC_NECK
#define NECK_FRONT		0x00
#define NECK_COORD		0x01
#define NECK_ANGLE		0x02
#define NECK_YES		0x03
#define NECK_NO			0x04
#define NECK_TRACE		0x05
#define NECK_AUTO		0x06
#define NECK_FREE		0x07
#define NECK_INIT		0x08

// PLC_DEST, PLC_MOTION
#define PLC_NOTHING				0
#define PLC_DEATH				1
#define PLC_WALK_FORWARD		4
#define PLC_RUN					5
#define PLC_STANDING			6
#define PLC_WALK_BACKWARD		7
#define PLC_CAREFUL_BACKWARD	8

// ITEM_AOT_SET (Action)
#define ITEM_NORMAL		0x00	// Stand to obtain
#define ITEM_KNEEL		0x01	// Kneel down to pickup
#define ITEM_ACTION_80	0x80	// ???
#define ITEM_ACTION_A0	0xA0	// ???
#define ITEM_ACTION_C0	0xC0	// ???
#define ITEM_ACTION_E0	0xE0	// ???

// DOOR_AOT_SET (Animation)
#define DOOR_NORMAL		0x00	// Knob on left, push forward
#define DOOR_REVERSE	0x01	// Knob on right, pull toward
#define DOOR_NORMAL2	0x02
#define DOOR_REVERSE2	0x03
#define DOOR_UP			0x04	// Ascending Lift
#define DOOR_DOWN		0x05	// Descending Lift
#define DOOR_NONE		0x06	// Disable Door Scripts
#define DOOR_NOBU2		0x80

// CMP, MEMB_CMP (Operator)
#define CMP_EQ			0x00	// equal
#define CMP_GT			0x01	// greater than
#define CMP_GE			0x02	// greater than or equal
#define CMP_LT			0x03	// less than
#define CMP_LE			0x04	// less than or equal
#define CMP_NE			0x05	// not equal
#define CMP_AND			0x06	// and

// CALC/2 (Operation)
#define CALC_ADD		0x00
#define CALC_SUB		0x01
#define CALC_MUL		0x02
#define CALC_DIV		0x03
#define CALC_MOD		0x04
#define CALC_OR			0x05
#define CALC_AND		0x06
#define CALC_XOR		0x07
#define CALC_NOT		0x08
#define CALC_LSL		0x09
#define CALC_LSR		0x0A
#define CALC_ASR		0x0B

// OM_SET (TexCtr)
#define OM_NORMAL			0x00
#define OM_MIZU				0x01
#define OM_HIT				0x02
#define OM_BOX				0x04

// OM_SET (BeFlag)
#define OM_DISABLED			0x0000
#define OM_ENABLED			0x0001
#define OM_NO_COLLISION		0x0002	// Walk/Run Through
#define OM_0004				0x0004	// ???
#define OM_0008				0x0008	// Texture Transparency
#define OM_0010				0x0010	// ???
#define OM_0020				0x0020	// ???
#define OM_ENEM_SE_INS_MASK	0x0040
#define OM_PLAYER_PUSH		0x0080	// Push to move
#define OM_MV				0x0100	// Climb on top animation
#define OM_MO				0x0200	// Auto-Move when collide
#define OM_0400				0x0400	// ???
#define OM_0800				0x0800	// ???
#define OM_1000				0x1000	// ???
#define OM_SC_AT			0x2000
#define OM_OB_AT			0x4000
#define OM_NO_HOSEI			0x8000	// No Display

// OM_SET (Attribute)
#define OM_LIGHT_ON			0x0000
#define OM_01				0x0001	// ???
#define OM_02				0x0002	// ???
#define OM_04				0x0004	// ???
#define OM_08				0x0008	// ???
#define OM_LIGHT_OFF		0x0010
#define OM_DISABLED_2		0x0020

// BGM_CTL (Id)
#define BGM_MAIN		0
#define BGM_SUB0		1
#define BGM_SUB1		2

// BGM_CTL (Op)
#define BGM_NOP			0
#define BGM_START		1
#define BGM_STOP		2
#define BGM_RESTART		3
#define BGM_PAUSE		4
#define BGM_FADEOUT		5

// BGM_CTL (Type)
#define MAIN_VOL		0
#define PROG0_VOL		1
#define PROG1_VOL		2
#define PROG2_VOL		3

// SE_ON (VAB)
#define SND_CORE		0
#define SND_ARMS		1
#define SND_ROOM		2
#define SND_ENEM		3
#define SND_DOOR		4