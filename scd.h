#pragma once

#pragma pack(push, 1)
typedef struct tagBio1Bytecode {
	UCHAR Opcode;											// Temporary Buffer
	struct tagNop {
		UCHAR Opcode;
	} Nop;								// 0x00	// Nop
	struct tagDoor_aot_set {
		UCHAR Opcode;		// 0x00 // 0x0C
		UCHAR Aot;			// 0x01 // 
		SHORT data2;		// 0x02 // 

		UCHAR data18;		// 0x18 // 
		UCHAR data19;		// 0x19 // 
	} Door_aot_set;			// 0x0C	// Door_aot_set
	struct tagItem_aot_set {
		UCHAR Opcode;		// 0x00 // 0x0D
		UCHAR Aot;			// 0x01 // 
		USHORT data2;		// 0x02 // 
		USHORT data4;		// 0x04 // 
		USHORT data6;		// 0x06 // 
		USHORT data8;		// 0x08 // 
		UCHAR dataA;		// 0x0A // 
		UCHAR dataB;		// 0x0B // 
		USHORT dataC;		// 0x0C // 
		USHORT dataE;		// 0x0E // 
		USHORT data10;		// 0x10 // 
	} Item_aot_set;			// 0x0D	// Item_aot_set
} Bio1Bytecode;		// Bio Hazard Director's Cut Dual Shock
typedef struct tagBio2BytecodeP {
	UCHAR Opcode;											// Temporary Buffer
	struct tagNop {
		UCHAR Opcode;
	} Nop;								// 0x00	// Nop
	struct tagEvt_end {
		UCHAR Opcode;
		UCHAR zAlign;
	} Evt_end;						// 0x01	// Evt_end
	struct tagEvt_next {
		UCHAR Opcode;
	} Evt_next;					// 0x02	// Evt_next
	struct tagEvt_chain {
		UCHAR Opcode;
		UCHAR Id;
	} Evt_chain;					// 0x03	// Evt_chain
	struct tagEvt_exec {
		UCHAR Opcode;			// 0x00 // 0x04
		UCHAR data1;			// 0x01 // typically 0xFF
		UCHAR Gosub;			// 0x02 // 0x18
		UCHAR ScdId;			// 0x03 // Script ID
	} Evt_exec;					// 0x04	// Evt_exec
	struct tagEvt_kill {
		UCHAR Opcode;
		UCHAR Id;
	} Evt_kill;					// 0x05	// Evt_kill
	struct tagIfel_ck {
		UCHAR Opcode;
		UCHAR zAlign;
		USHORT Size;
	} Ifel_ck;						// 0x06	// Ifel_ck
	struct tagElse_ck {
		UCHAR Opcode;
		UCHAR zAlign;
		USHORT Size;
	} Else_ck;						// 0x07	// Else_ck
	struct tagEndif {
		UCHAR Opcode;
		UCHAR zAlign;
	} Endif;							// 0x08	// Endif
	struct tagSleep {
		UCHAR Opcode;					// 0x00 // 0x09
		UCHAR Sleeping;					// 0x01 // 0x0A
		USHORT Count;					// 0x02 // Timer
	} Sleep;							// 0x09	// Sleep
	struct tagSleeping {
		UCHAR Opcode;			// 0x00 // 0x0A
		USHORT Count;			// 0x01 // Timer
	} Sleeping;					// 0x0A	// Sleeping
	struct tagWsleep {
		UCHAR Opcode;
	} Wsleep;						// 0x0B	// Wsleep
	struct tagWsleeping {
		UCHAR Opcode;
	} Wsleeping;					// 0x0C	// Wsleeping
	struct tagFor {
		UCHAR Opcode;
		UCHAR zAlign;
		USHORT Size;
		USHORT Count;
	} For;								// 0x0D	// For
	struct tagNext {
		UCHAR Opcode;
		UCHAR zAlign;
	} Next;							// 0x0E	// Next
	struct tagWhile {
		UCHAR Opcode;
		UCHAR Num;
		SHORT Size;
	} While;							// 0x0F	// While
	struct tagEwhile {
		UCHAR Opcode;
		UCHAR zAlign;
	} Ewhile;						// 0x10	// Ewhile
	struct tagDo {
		UCHAR Opcode;
		UCHAR Num;
		USHORT Size;
	} Do;								// 0x11	// Do
	struct tagEdwhile {
		UCHAR Opcode;
		UCHAR Size;
	} Edwhile;						// 0x12	// Edwhile
	struct tagSwitch {
		UCHAR Opcode;
		UCHAR Value;
		USHORT Size;
	} Switch;						// 0x13	// Switch
	struct tagCase {
		UCHAR Opcode;
		UCHAR zAlign;
		USHORT Size;
		USHORT Value;
	} Case;							// 0x14	// Case
	struct tagDefault {
		UCHAR Opcode;
		UCHAR zAlign;
	} Default;						// 0x15	// Default
	struct tagEswitch {
		UCHAR Opcode;
		UCHAR zAlign;
	} Eswitch;						// 0x16	// Eswitch
	struct tagGoto {
		UCHAR Opcode;				// 0x00	// 0x17
		UCHAR Ifel_ctr;				// 0x01	// always 0xFF (0x01 on r304-sub05, only)
		UCHAR Loop_ctr;				// 0x02	// always 0xFF (0x00 on r500-sub04 and sub07, only)
		UCHAR zAlign;				// 0x03	// always 0x00
		SHORT Offset;				// 0x04	// Relative Pointer, always references same script
	} Goto;							// 0x17	// Goto
	struct tagGosub {
		UCHAR Opcode;
		UCHAR SCD;						// SCD File Id
	} Gosub;							// 0x18	// Gosub
	struct tagReturn {
		UCHAR Opcode;
		UCHAR zAlign;
	} Return;						// 0x19	// Return
	struct tagBreak {
		UCHAR Opcode;
		UCHAR zAlign;
	} Break;							// 0x1A	// Break
	struct tagFor2 {
		UCHAR Opcode;
		UCHAR zAlign;
		USHORT data0;
		UCHAR data1;
		UCHAR data2;
	} For2;							// 0x1B	// For2
	struct tagBreak_point {
		UCHAR Opcode;
	} Break_point;				// 0x1C	// Break_point
	struct tagOpcode1D {
		UCHAR Opcode;
	} Opcode1D;					// 0x1D	// Nop
	struct tagOpcode1E {
		UCHAR Opcode;
	} Opcode1E;					// 0x1E	// Nop
	struct tagOpcode1F {
		UCHAR Opcode;
	} Opcode1F;					// 0x1F	// Nop
	struct tagOpcode20 {
		UCHAR Opcode;
	} Opcode20;					// 0x20	// Nop
	struct tagCk {
		UCHAR Opcode;				// 0x21
		UCHAR Flag;					// System_flg, etc
		UCHAR Id;					// Bit
		UCHAR OnOff;				// 00	OFF
									// 01	ON
	} Ck;								// 0x21 // Ck
	struct tagSet {
		UCHAR Opcode;				// 0x22
		UCHAR Flag;					// System_flg, etc
		UCHAR Id;					// Bit
		UCHAR OnOff;				// 00	OFF
									// 01	ON
	} Set;								// 0x22	// Set
	struct tagCmp {
		UCHAR Opcode;				// 0x23
		UCHAR zAlign;				// 0x00
		UCHAR Flag;					// F_atari, etc
		UCHAR Operator;				// 
		SHORT Value;				// 
	} Cmp;								// 0x23	// Cmp
	struct tagSave {
		UCHAR Opcode;				// 0x24
		UCHAR Destination;					// F_atari, etc
		SHORT Source;
	} Save;							// 0x24	// Save
	struct tagCopy {
		UCHAR Opcode;				// 0x25
		UCHAR Destination;
		UCHAR Source;
	} Copy;							// 0x25	// Copy
	struct tagCalc {
		UCHAR Opcode;
		UCHAR zAlign;				// 0x00
		UCHAR Operator;
		UCHAR Flag;
		SHORT Value;
	} Calc;							// 0x26	// Calc
	struct tagCalc2 {
		UCHAR Opcode;
		UCHAR Operator;
		UCHAR Flag;						// F_atari, etc
		UCHAR Value;
	} Calc2;							// 0x27	// Calc2
	struct tagSce_rnd {
		UCHAR Opcode;
	} Sce_rnd;						// 0x28	// Sce_rnd
	struct tagCut_chg {
		UCHAR Opcode;
		UCHAR nCut;
	} Cut_chg;						// 0x29	// Cut_chg
	struct tagCut_old {
		UCHAR Opcode;
	} Cut_old;						// 0x2A	// Cut_old
	struct tagMessage_on {
		UCHAR Opcode;
		UCHAR data1;
		USHORT data2;
	} Message_on;				// 0x2B	// Message_on
	struct tagAot_set {
		UCHAR Opcode;	// 0x2C
		CHAR Aot;		// Id
		UCHAR SCE;		// Type
		UCHAR SAT;		// Atari
		UCHAR nFloor;	// Height
		UCHAR Super;	// Matrix
		SHORT X, Z;		// Position
		USHORT W, D;	// Size

		USHORT Data0;	// Sce_Message
						// byte0	???
						// byte1	MSG Id
						//
						// Sce_Flg_chg
						// Flag Type
						// For example, if(Ck(ROOM, 0x01, OFF))
						// This variable would be 0x0005
						//
						// Sce_Event
						// Always 0x00FF
						//

		USHORT Data1;	// Sce_Message
						// byte0	???
						// byte1	???
						//
						// Sce_Flg_chg
						// Flag Id
						// For example, if(Ck(ROOM, 0x01, OFF))
						// This variable would be 0x0001
						//
						// Sce_Event
						// byte0	Script Id Init
						// byte1	Script Id Complete
						//

		USHORT Data2;	// Sce_Message
						// Always 0xFFFF
						//
	} Aot_set;						// 0x2C	// Aot_set				// if(SAT & 0x80) = 0
	struct tagAot_set_4p {
		UCHAR Opcode;			// 0x2C
		UCHAR Aot;				// Id
		UCHAR SCE;				// Type
		UCHAR SAT;				// Atari
		UCHAR nFloor;			// Height
		UCHAR Super;			// Matrix
		SHORT X0, Z0;			// Point #1
		SHORT X1, Z1;			// Point #2
		SHORT X2, Z2;			// Point #3
		SHORT X3, Z3;			// Point #4
		USHORT data0;
		USHORT data1;
		USHORT data2;
	} Aot_set_4p;				// 0x2C	// Aot_set_4p			// if(SAT & 0x80) = 1
	struct tagObj_model_set {
		UCHAR Opcode;			// 0x00	// 0x2D
		UCHAR MD1;				// 0x01	// MD1 File Id
		UCHAR Id;				// 0x02	// Global->Ob_model[].Id
		UCHAR nFloor;			// 0x03	//
		UCHAR Super;			// 0x04	//
		UCHAR Type;				// 0x05	// Global->Ob_model[].Type
		USHORT BeFlag;			// 0x06	// Global->Ob_model[].Be_flg
		SHORT Attribute;		// 0x08	// Global->Ob_model[].Attribute
		SHORT X;				// 0x0A	// 
		SHORT Y;				// 0x0C	// 
		SHORT Z;				// 0x0E	// 
		SHORT DirX;				// 0x10	// 
		SHORT DirY;				// 0x12	// 
		SHORT DirZ;				// 0x14	// 
		SHORT AtariOffsetX;		// 0x16	// 
		SHORT AtariOffsetY;		// 0x18	// 
		SHORT AtariOffsetZ;		// 0x1A	// 
		SHORT AtariSizeX;		// 0x1C	// 
		SHORT AtariSizeY;		// 0x1E	// 
		SHORT AtariSizeZ;		// 0x20	// 
	} Obj_model_set;			// 0x2D	// Obj_model_set
	struct tagWork_set {
		UCHAR Opcode;
		UCHAR Type;
		CHAR Aot;
	} Work_set;					// 0x2E	// Work_set
	struct tagSpeed_set {
		UCHAR Opcode;
		UCHAR Id;
		SHORT Value;
	} Speed_set;					// 0x2F	// Speed_set
	struct tagAdd_speed {
		UCHAR Opcode;
	} Add_speed;					// 0x30	// Add_speed
	struct tagAdd_aspeed {
		UCHAR Opcode;
	} Add_aspeed;				// 0x31	// Add_aspeed
	struct tagPos_set {
		UCHAR Opcode;
		UCHAR zAlign;
		SHORT X;
		SHORT Y;
		SHORT Z;
	} Pos_set;						// 0x32	// Pos_set
	struct tagDir_set {
		UCHAR Opcode;
		UCHAR zAlign;
		SHORT X;
		SHORT Y;
		SHORT Z;
	} Dir_set;						// 0x33	// Dir_set
	struct tagMember_set {
		UCHAR Opcode;
		UCHAR Destination;
		SHORT Source;
	} Member_set;				// 0x34	// Member_set
	struct tagMember_set2 {
		UCHAR Opcode;
		UCHAR Destination;
		UCHAR Source;
	} Member_set2;				// 0x35	// Member_set2
	struct tagSe_on {
		UCHAR Opcode;	// 0x36
		UCHAR VAB;		// VAB Bank Id
		SHORT EDT;		// EDT Sample Id
		SHORT data0;	// Sound Reverberation, Work Aot/Obj No
		SHORT X;		// Position
		SHORT Y;
		SHORT Z;
	} Se_on;							// 0x36	// Se_on
	struct tagSca_id_set {
		UCHAR Opcode;
		UCHAR iEntry;			// SCA Collision Entry
		USHORT Id;				// New Collision ID
	} Sca_id_set;				// 0x37	// Sca_id_set
	struct tagSca_xzwd_set {
		UCHAR Opcode;
		UCHAR zAlign;
		UCHAR data2;
		UCHAR data3;
		SHORT data4;
		SHORT data6;
		USHORT data8;
		USHORT dataA;
	} Sca_xzwd_set;			// 0x38	// Sca_xzwd_set
	struct tagSca_type_set {
		UCHAR Opcode;
		UCHAR iEntry;			// SCA Collision Entry
		USHORT Type;			// New Collision Type
	} Sca_type_set;			// 0x39	// Sca_type_set
	struct tagSce_espr_on {
		UCHAR Opcode;
		UCHAR zAlign;
		USHORT data0;
		USHORT data1;
		USHORT data2;
		SHORT X;
		SHORT Y;
		SHORT Z;
		SHORT DirY;
	} Sce_espr_on;				// 0x3A	// Sce_espr_on
	struct tagDoor_aot_set {
		UCHAR Opcode;
		UCHAR Aot;			// 0x01	// Id
		UCHAR SCE;			// 0x02	// Type (0x01)
		UCHAR SAT;			// 0x03	// Atari
		UCHAR nFloor;		// 0x04	// Height
		UCHAR Super;		// 0x05	// Matrix
		SHORT X;			// 0x06	//
		SHORT Z;			// 0x08	// Position
		USHORT W;			// 0x0A	//
		USHORT D;			// 0x0C	// Size
		SHORT Next_pos_x;	// 0x0E	//
		SHORT Next_pos_y;	// 0x10	//
		SHORT Next_pos_z;	// 0x12	//
		SHORT Next_cdir_y;	// 0x14	//
		UCHAR Next_stage;	// 0x16	//
		UCHAR Next_room;	// 0x17	//
		UCHAR Next_cut;		// 0x18	//
		UCHAR Next_nfloor;	// 0x19	//
		UCHAR Dtex_type;	// 0x1A	// DO2 File Id
		UCHAR Door_type;	// 0x1B	// DO2 Animation Set
		UCHAR Knock_type;	// 0x1C	// Sound
		UCHAR Key_id;		// 0x1D	// 
		UCHAR Key_type;		// 0x1E	// 
		UCHAR Free;			// 0x1F	// 
	} Door_aot_set;			// 0x3B	// Door_aot_set			// if(SAT & 0x80) = 0	// WIP
	struct tagDoor_aot_set_4p {
		UCHAR Opcode;		// 0x00 // 0x3B
		UCHAR Aot;			// 0x01 // Id
		UCHAR SCE;			// 0x02 // Type (0x01)
		UCHAR SAT;			// 0x03 // Atari
		UCHAR nFloor;		// 0x04 // Height
		UCHAR Super;		// 0x05 // Matrix
		SHORT X0, Z0;		// 0x06 // Point #1
		SHORT X1, Z1;		// 0x0A // Point #2
		SHORT X2, Z2;		// 0x0E // Point #3
		SHORT X3, Z3;		// 0x12 // Point #4
		SHORT PosX;			// 0x16 // Player position after entering door
		SHORT PosY;			// 0x18 // Player position after entering door
		SHORT PosZ;			// 0x1A // Player position after entering door
		SHORT DirY;			// 0x1C // Player direction after entering door
		UCHAR Stage;		// 0x1E // Stage after entering door
		UCHAR Room;			// 0x1F // Room after entering door
		UCHAR Cut;			// 0x20 // Camera ID of room after entering door
		UCHAR nFloorNxt;	// 0x21 // 
		UCHAR DO2;			// 0x22 // 
		UCHAR Animation;	// 0x23 // 
		UCHAR Sound;		// 0x24 // 
		UCHAR KeyId;		// 0x25 // 
		UCHAR KeyType;		// 0x26 // 
		UCHAR Free;			// 0x27 // 
	} Door_aot_set_4p;		// 0x3B	// Door_aot_set_4p		// if(SAT & 0x80) = 1	// WIP
	struct tagCut_auto {
		UCHAR Opcode;			// 0x3C
		UCHAR OnOff;			// 00	OFF
								// 01	ON
	} Cut_auto;					// 0x3C	// Cut_auto
	struct tagMember_copy {
		UCHAR Opcode;
		CHAR Destination;
		CHAR Source;
	} Member_copy;				// 0x3D	// Member_copy
	struct tagMember_cmp {
		UCHAR Opcode;			// 0x00	// 0x3E
		UCHAR zAlign;			// 0x01	// 0x00
		UCHAR Flag;				// 0x02	// Load_member_addr_branch() argv[1]
		UCHAR Operator;			// 0x03	// 
		SHORT Value;			// 0x04	// 
	} Member_cmp;				// 0x3E	// Member_cmp
	struct tagPlc_motion {
		UCHAR Opcode;
		UCHAR Animation;		// EDD/EMR Id
		UCHAR data0;			// 
		UCHAR data1;			// 
	} Plc_motion;				// 0x3F	// Plc_motion
	struct tagPlc_dest {
		UCHAR Opcode;
		UCHAR zAlign;			// 0x00
		UCHAR Animation;		// EDD/EMR Id
		UCHAR Bit;				// Room_flg
		SHORT X;
		SHORT Z;				// Destination
	} Plc_dest;					// 0x40	// Plc_dest
	struct tagPlc_neck {
		UCHAR Opcode;
		UCHAR Op;
		SHORT X;
		SHORT Y;
		SHORT Z;
		UCHAR SpeedX;
		UCHAR SpeedZ;
	} Plc_neck;					// 0x41	// Plc_neck
	struct tagPlc_ret {
		UCHAR Opcode;
	} Plc_ret;						// 0x42	// Plc_ret
	struct tagPlc_flg {
		UCHAR Opcode;
		UCHAR Type;			// 
		USHORT Flag;		// 
	} Plc_flg;						// 0x43	// Plc_flg
	struct tagSce_em_set {
		UCHAR Opcode;		// 0x00	// 0x44
		CHAR Em_no;			// 0x01	// AOT
		UCHAR Id;			// 0x02	// 
		UCHAR Type;			// 0x03	// 
		UCHAR nFloor;		// 0x04	// 
		UCHAR Sound_flg;	// 0x05	// 
		UCHAR Model_type;	// 0x06	// 
		UCHAR Em_set_flg;	// 0x07	// Enemy_flg/2, to determine if enemy has been killed
		SHORT Pos_x;		// 0x08	// 
		SHORT Pos_y;		// 0x0A	// 
		SHORT Pos_z;		// 0x0C	// 
		SHORT Cdir_y;		// 0x0E	// 
		SHORT Motion;		// 0x10	// 
		SHORT Ctr_flg;		// 0x12	// 
	} Sce_em_set;				// 0x44	// Sce_em_set
	struct tagOpcode45 {
		UCHAR Opcode;
		UCHAR data2;
		UCHAR data3;
	} Opcode45;					// 0x45	// UNKNOWN OPCODE
	struct tagAot_reset {
		UCHAR Opcode;
		CHAR Aot;
		UCHAR SCE;
		UCHAR SAT;
		USHORT Data0;
		USHORT Data1;
		USHORT Data2;
	} Aot_reset;					// 0x46	// Aot_reset
	struct tagAot_on {
		UCHAR Opcode;
		UCHAR Aot;
	} Aot_on;						// 0x47	// Aot_on
	struct tagSuper_set {
		UCHAR Opcode;
		UCHAR zAlign;
		UCHAR Work;			// Work Type
		UCHAR Id;			// Work Aot/Obj No
		SHORT pX, pY, pZ;	// Parent
		SHORT dX, dY, dZ;	// Destination
	} Super_set;					// 0x48	// Super_set
	struct tagSuper_reset {
		UCHAR Opcode;
		UCHAR zAlign;
		SHORT dX;
		SHORT dY;
		SHORT dZ;
	} Super_reset;				// 0x49	// Super_reset
	struct tagPlc_gun {
		UCHAR Opcode;
		UCHAR Animation;	// EDD/EMR Id
	} Plc_gun;						// 0x4A	// Plc_gun
	struct tagCut_replace {
		UCHAR Opcode;
		UCHAR Id;
		UCHAR Value;
	} Cut_replace;				// 0x4B	// Cut_replace
	struct tagOpcode4C {
		UCHAR Opcode;
		UCHAR data1;
		UCHAR data[0x10];
	} Opcode4C;					// 0x4C	// UNKNOWN OPCODE		// WIP	// ROOM115U.SCD and ROOM506U.SCD
	struct tagOpcode4D {
		UCHAR Opcode;
		CHAR data1;
		UCHAR data2;
		UCHAR data3;
		USHORT data4;
		USHORT data6;
		USHORT data8;
	} Opcode4D;					// 0x4D	// UNKNOWN OPCODE		// ROOM115U.SCD and ROOM506U.SCD
	struct tagSce_espr_kill {
		UCHAR Opcode;
		UCHAR id;				// Esp_kill() argv[0]
		UCHAR tp;				// Esp_kill() argv[1]
		CHAR WorkKind;			// Get_matrix() argv[0]
		CHAR WorkNo;			// Get_matrix() argv[1]
	} Sce_espr_kill;			// 0x4E	// Sce_espr_kill
	struct tagDoor_model_set {
		UCHAR Opcode;		// 0x00	// 0x4F
		UCHAR data0;		// 0x01	// 
		UCHAR Id;			// 0x02	// DOOR_WORK.Id
		UCHAR OfsY;			// 0x03	// DOOR_WORK.Atd[3]
		UCHAR BeFlg;		// 0x04	// DOOR_WORK.Be_flg
		UCHAR data5;		// 0x05	// 
		USHORT data6;		// 0x06	// 
		SHORT X;			// 0x08	// DOOR_WORK.Atd[3]
		SHORT Y;			// 0x0A	// DOOR_WORK.Atd[3]
		SHORT Z;			// 0x0C	// DOOR_WORK.Atd[3]
		SHORT DirY;			// 0x0E	// DOOR_WORK.Atd[3]
		USHORT data10;		// 0x10	// DOOR_WORK.MATRIX
		USHORT data11;		// 0x12	// DOOR_WORK.MATRIX
		USHORT data12;		// 0x14	// DOOR_WORK.MATRIX
	} Door_model_set;		// 0x4F	// Door_model_set
	struct tagItem_aot_set {
		UCHAR Opcode;		// 0x00 // 0x50
		UCHAR Aot;			// 0x01	// Id
		UCHAR SCE;			// 0x02	// Type (0x02)
		UCHAR SAT;			// 0x03	// Atari
		UCHAR nFloor;		// 0x04	// Height
		UCHAR Super;		// 0x05	// Matrix
		SHORT X;			// 0x06	// Position
		SHORT Z;			// 0x08	// Position
		USHORT W;			// 0x0A	// Size
		USHORT D;			// 0x0C	// Size
		USHORT iItem;		// 0x0E	// Item Id
		USHORT nItem;		// 0x10	// Item Amount
		USHORT Flag;		// 0x12	// Item_flg/2 Bit
		UCHAR MD1;			// 0x14	// MD1 File Id - 0xFF if no MD1
		UCHAR Action;		// 0x15	// Predefined action taken to obtain
	} Item_aot_set;			// 0x50	// Item_aot_set			// if(SAT & 0x80) = 0
	struct tagItem_aot_set_4p {
		UCHAR Opcode;		// 0x00 // 0x50
		UCHAR Aot;			// 0x01 // Id
		UCHAR SCE;			// 0x02 // Type (0x02)
		UCHAR SAT;			// 0x03 // Atari
		UCHAR nFloor;		// 0x04 // Height
		UCHAR Super;		// 0x05 // Matrix
		SHORT X0;			// 0x06 // Point #1
		SHORT Z0;			// 0x08 // Point #1
		SHORT X1;			// 0x0A // Point #2
		SHORT Z1;			// 0x0C // Point #2
		SHORT X2;			// 0x0E // Point #3
		SHORT Z2;			// 0x10 // Point #3
		SHORT X3;			// 0x12 // Point #4
		SHORT Z3;			// 0x14 // Point #4
		USHORT iItem;		// 0x16 // Item Id
		USHORT nItem;		// 0x18 // Item Amount
		USHORT Flag;		// 0x1A // Item_flg/2 Bit
		UCHAR MD1;			// 0x1C // MD1 File Id - 0xFF if no MD1
		UCHAR Action;		// 0x1D // Predefined action taken to obtain
	} Item_aot_set_4p;		// 0x50	// Item_aot_set			// if(SAT & 0x80) = 1
	struct tagSce_key_ck {
		UCHAR Opcode;
		UCHAR Flag;
		USHORT Value;
	} Sce_key_ck;				// 0x51	// Sce_key_ck
	struct tagSce_trg_ck {
		UCHAR Opcode;
		UCHAR Flag;
		USHORT Value;
	} Sce_trg_ck;				// 0x52	// Sce_trg_ck
	struct tagWork_set2 {
		UCHAR Opcode;
		UCHAR Type;
		CHAR Aot;
	} Work_set2;					// 0x53	// Parts_set
	struct tagSce_bgm_control {
		UCHAR Opcode;
		UCHAR Id;
		UCHAR Op;
		UCHAR Type;
		UCHAR VolL;			// Volume Left
		UCHAR VolR;			// Volume Right
	} Sce_bgm_control;		// 0x54	// Sce_bgm_control
	struct tagSce_espr_control {
		UCHAR Opcode;
		UCHAR Id;		// 0x01	// 
		UCHAR Type;		// 0x02	// 
		UCHAR Return;	// 0x03	// 
		CHAR WorkKind;	// 0x04	// 
		CHAR WorkNo;	// 0x05	// 
	} Sce_espr_control;	// 0x55	// Sce_espr_control
	struct tagSce_fade_set {
		UCHAR Opcode;
		UCHAR data0;
		UCHAR data1;
		UCHAR data2;
		USHORT data3;
	} Sce_fade_set;			// 0x56	// Sce_fade_set
	struct tagSce_fade_adjust {
		UCHAR Opcode;
		UCHAR data0;
		SHORT data1;
	} Sce_fade_adjust;		// 0x57	// Sce_fade_adjust
	struct tagCk2 {
		UCHAR Opcode;
		UCHAR Flag;					// System_flg, etc
		UCHAR Id;					// Bit
		UCHAR OnOff;				// 00	OFF
									// 01	ON
	} Ck2;								// 0x58	// Ck2
	struct tagSet2 {
		UCHAR Opcode;
		UCHAR Flag;					// System_flg, etc
		UCHAR Id;					// Bit
		UCHAR OnOff;				// 00	OFF
									// 01	ON
	} Set2;							// 0x59	// Set2
	struct tagMember_calc {
		UCHAR Opcode;
		UCHAR Operator;				// 0x01	// Calc_branch() argv[0]
		USHORT Flag;			// 0x02	// Load_member_addr_branch() argv[1]
		SHORT Value;				// 0x04	// Calc_branch() argv[2]
	} Member_calc;				// 0x5A	// Member_calc
	struct tagMember_calc2 {
		UCHAR Opcode;
		UCHAR Operator;			// 0x01	// Calc_branch() argv[0]
		UCHAR Flag;		// 0x02	// Load_member_addr_branch() argv[1]
		UCHAR Value;			// 0x03	// Calc_branch() argv[2]
	} Member_calc2;			// 0x5B	// Member_calc2
	struct tagSce_bgmtbl_set {
		UCHAR Opcode;
		UCHAR Stage;
		UCHAR Room;
		UCHAR data1;
	} Sce_bgmtbl_set;		// 0x5C	// Sce_bgmtbl_set		// WIP
	struct tagPlc_rot {
		UCHAR Opcode;
		UCHAR Id;
		USHORT Sce_free0;
	} Plc_rot;						// 0x5D	// Plc_rot
	struct tagXa_on {
		UCHAR Opcode;
		UCHAR Mode;
		USHORT Number;
	} Xa_on;							// 0x5E	// Xa_on
} Bio2BytecodeP;	    // Bio Hazard 2 Prototype (Nov. 1996)
typedef struct tagBio2BytecodeT {
	struct tagCol_chg_set {
		UCHAR Opcode;
		UCHAR data0[2];
	} Col_chg_set;				// 0x45	// Col_chg_set (unimplemented)
	struct tagKage_set {
		UCHAR Opcode;
		UCHAR data[0x13];
	} Kage_set;					// 0x60	// Kage_set (unimplemented)
} Bio2BytecodeT;	    // Bio Hazard 2 Trial Edition
typedef struct tagBio2Bytecode {
	UCHAR Opcode;										// Temporary Buffer
	struct tagNop {
		UCHAR Opcode;
	} Nop;								// 0x00	// 0x00 bytes // Nop
	struct tagEvt_end {
		UCHAR Opcode;
		UCHAR zAlign;
	} Evt_end;						// 0x01	// 0x00 bytes // Evt_end
	struct tagEvt_next {
		UCHAR Opcode;
	} Evt_next;					// 0x02	// 0x00 bytes // Evt_next
	struct tagEvt_chain {
		UCHAR Opcode;
		UCHAR Id;
	} Evt_chain;					// 0x03	// 0x00 bytes // Evt_chain
	struct tagEvt_exec {
		UCHAR Opcode;			// 0x00 // 0x04
		UCHAR data1;			// 0x01 // typically 0xFF
		UCHAR Gosub;			// 0x02 // 0x18
		UCHAR ScdId;			// 0x03 // Script ID
	} Evt_exec;					// 0x04	// 0x00 bytes // Evt_exec
	struct tagEvt_kill {
		UCHAR Opcode;
		UCHAR Id;
	} Evt_kill;					// 0x05	// 0x00 bytes // Evt_kill
	struct tagIfel_ck {
		UCHAR Opcode;
		UCHAR zAlign;
		USHORT Size;
	} Ifel_ck;						// 0x06	// 0x00 bytes // Ifel_ck
	struct tagElse_ck {
		UCHAR Opcode;
		UCHAR zAlign;
		USHORT Size;
	} Else_ck;						// 0x07	// 0x00 bytes // Else_ck
	struct tagEndif {
		UCHAR Opcode;
		UCHAR zAlign;
	} Endif;							// 0x08	// 0x00 bytes // Endif
	struct tagSleep {
		UCHAR Opcode;					// 0x00 // 0x09
		UCHAR Sleeping;					// 0x01 // 0x0A
		USHORT Count;					// 0x02 // Timer
	} Sleep;							// 0x09	// 0x00 bytes // Sleep
	struct tagSleeping {
		UCHAR Opcode;			// 0x00 // 0x0A
		USHORT Count;			// 0x01 // Timer
	} Sleeping;					// 0x0A	// 0x00 bytes // Sleeping
	struct tagWsleep {
		UCHAR Opcode;
	} Wsleep;						// 0x0B	// 0x00 bytes // Wsleep
	struct tagWsleeping {
		UCHAR Opcode;
	} Wsleeping;					// 0x0C	// 0x00 bytes // Wsleeping
	struct tagFor {
		UCHAR Opcode;
		UCHAR zAlign;
		USHORT Size;
		USHORT Count;
	} For;								// 0x0D	// 0x00 bytes // For
	struct tagNext {
		UCHAR Opcode;
		UCHAR zAlign;
	} Next;							// 0x0E	// 0x00 bytes // Next
	struct tagWhile {
		UCHAR Opcode;
		UCHAR Num;
		SHORT Size;
	} While;							// 0x0F	// 0x00 bytes // While
	struct tagEwhile {
		UCHAR Opcode;
		UCHAR zAlign;
	} Ewhile;						// 0x10	// 0x00 bytes // Ewhile
	struct tagDo {
		UCHAR Opcode;
		UCHAR Num;
		USHORT Size;
	} Do;								// 0x11	// 0x00 bytes // Do
	struct tagEdwhile {
		UCHAR Opcode;
		UCHAR Size;
	} Edwhile;						// 0x12	// 0x00 bytes // Edwhile
	struct tagSwitch {
		UCHAR Opcode;
		UCHAR Value;
		USHORT Size;
	} Switch;						// 0x13	// 0x00 bytes // Switch
	struct tagCase {
		UCHAR Opcode;
		UCHAR zAlign;
		USHORT Size;
		USHORT Value;
	} Case;							// 0x14	// 0x00 bytes // Case
	struct tagDefault {
		UCHAR Opcode;
		UCHAR zAlign;
	} Default;						// 0x15	// 0x00 bytes // Default
	struct tagEswitch {
		UCHAR Opcode;
		UCHAR zAlign;
	} Eswitch;						// 0x16	// 0x00 bytes // Eswitch
	struct tagGoto {
		UCHAR Opcode;				// 0x00	// 0x17
		UCHAR Ifel_ctr;				// 0x01	// always 0xFF (0x01 on r304-sub05, only)
		UCHAR Loop_ctr;				// 0x02	// always 0xFF (0x00 on r500-sub04 and sub07, only)
		UCHAR zAlign;				// 0x03	// always 0x00
		SHORT Offset;				// 0x04	// Relative Pointer, always references same script
	} Goto;							// 0x17	// 0x00 bytes // Goto
	struct tagGosub {
		UCHAR Opcode;
		UCHAR SCD;						// SCD File Id
	} Gosub;							// 0x18	// 0x00 bytes // Gosub				// Wrong Size?
	struct tagReturn {
		UCHAR Opcode;
		UCHAR zAlign;
	} Return;						// 0x19	// 0x00 bytes // Return
	struct tagBreak {
		UCHAR Opcode;
		UCHAR zAlign;
	} Break;							// 0x1A	// 0x00 bytes // Break
	struct tagFor2 {
		UCHAR Opcode;
		UCHAR zAlign;
		USHORT data0;
		UCHAR data1;
		UCHAR data2;
	} For2;							// 0x1B	// 0x00 bytes // For2
	struct tagBreak_point {
		UCHAR Opcode;
	} Break_point;				// 0x1C	// 0x00 bytes // Break_point
	struct tagWork_copy {
		UCHAR Opcode;		// 0x1D
		UCHAR Source;		// Index
		UCHAR Destination;	// 
		UCHAR Typecast;		// 0 = Byte
							// 1 = Short
	} Work_copy;					// 0x1D	// 0x00 bytes // Work_copy
	struct tagOpcode1E {
		UCHAR Opcode;
	} Opcode1E;					// 0x1E	// 0x00 bytes // Nop
	struct tagOpcode1F {
		UCHAR Opcode;
	} Opcode1F;					// 0x1F	// 0x00 bytes // Nop
	struct tagOpcode20 {
		UCHAR Opcode;
	} Opcode20;					// 0x20	// 0x00 bytes // Nop
	struct tagCk {
		UCHAR Opcode;				// 0x21
		UCHAR Flag;					// System_flg, etc
		UCHAR Id;					// Bit
		UCHAR OnOff;				// 00	OFF
									// 01	ON
	} Ck;								// 0x21 // 0x00 bytes // Ck
	struct tagSet {
		UCHAR Opcode;				// 0x22
		UCHAR Flag;					// System_flg, etc
		UCHAR Id;					// Bit
		UCHAR OnOff;				// 00	OFF
									// 01	ON
	} Set;								// 0x22	// 0x00 bytes // Set
	struct tagCmp {
		UCHAR Opcode;				// 0x23
		UCHAR zAlign;				// 0x00
		UCHAR Flag;					// F_atari, etc
		UCHAR Operator;				// 
		SHORT Value;				// 
	} Cmp;								// 0x23	// 0x00 bytes // Cmp
	struct tagSave {
		UCHAR Opcode;				// 0x24
		UCHAR Destination;					// F_atari, etc
		SHORT Source;
	} Save;							// 0x24	// 0x00 bytes // Save
	struct tagCopy {
		UCHAR Opcode;				// 0x25
		UCHAR Destination;
		UCHAR Source;
	} Copy;							// 0x25	// 0x00 bytes // Copy
	struct tagCalc {
		UCHAR Opcode;				// 0x26
		UCHAR zAlign;				// 0x00
		UCHAR Operator;
		UCHAR Flag;
		SHORT Value;
	} Calc;							// 0x26	// 0x00 bytes // Calc
	struct tagCalc2 {
		UCHAR Opcode;				// 0x27
		UCHAR Operator;
		UCHAR Flag;					// F_atari, etc
		UCHAR Value;
	} Calc2;							// 0x27	// 0x00 bytes // Calc2
	struct tagSce_rnd {
		UCHAR Opcode;				// 0x28
	} Sce_rnd;						// 0x28	// 0x00 bytes // Sce_rnd
	struct tagCut_chg {
		UCHAR Opcode;				// 0x29
		UCHAR nCut;
	} Cut_chg;						// 0x29	// 0x00 bytes // Cut_chg
	struct tagCut_old {
		UCHAR Opcode;
	} Cut_old;						// 0x2A	// 0x00 bytes // Cut_old
	struct tagMessage_on {
		UCHAR Opcode;
		UCHAR zAlign;
		UCHAR data0;
		UCHAR data1;
		USHORT data2;
	} Message_on;				// 0x2B	// 0x00 bytes // Message_on
	struct tagAot_set {
		UCHAR Opcode;	// 0x2C
		CHAR Aot;		// Aot
		UCHAR SCE;		// Id		/* tagSCE_AOT
		UCHAR SAT;		// Type
		UCHAR nFloor;	// nFloor
		UCHAR Super;	// Super
		SHORT X;		// Position
		SHORT Z;		// Position
		USHORT W;		// Size
		USHORT D;		// Size		*/ tagSCE_AOT

		USHORT Data0;	// Sce_Message
						// byte0	???
						// byte1	MSG Id
						//
						// Sce_Flg_chg
						// Flag Type
						// For example, if(Ck(ROOM, 0x01, OFF))
						// This variable would be 0x0005
						//
						// Sce_Event
						// Always 0x00FF
						//

		USHORT Data1;	// Sce_Message
						// byte0	???
						// byte1	???
						//
						// Sce_Flg_chg
						// Flag Id
						// For example, if(Ck(ROOM, 0x01, OFF))
						// This variable would be 0x0001
						//
						// Sce_Event
						// byte0	Script Id Init
						// byte1	Script Id Complete
						//

		USHORT Data2;	// Sce_Message
						// Always 0xFFFF
						//
	} Aot_set;						// 0x2C	// 0x00 bytes // Aot_set
	struct tagObj_model_set {
		UCHAR Opcode;		// 0x00	// 0x2D
		UCHAR MD1;			// 0x01	// MD1 File Id
		UCHAR Id;			// 0x02	// Global->Ob_model[].Id
		UCHAR Ccol_old;		// 0x03	// CC_WORK structure
		UCHAR Ccol_no;		// 0x04	// CC_WORK structure
		UCHAR Ctex_old;		// 0x05	// CC_WORK structure
		UCHAR nFloor;		// 0x06	//
		UCHAR Super;		// 0x07	//
		USHORT Type;		// 0x08	// Global->Ob_model[].Type
		USHORT BeFlag;		// 0x0A	// Global->Ob_model[].Be_flg
		SHORT Attribute;	// 0x0C	// Global->Ob_model[].Attribute
		SHORT X;			// 0x0E	//
		SHORT Y;			// 0x10	//
		SHORT Z;			// 0x12	//
		SHORT DirX;			// 0x14	//
		SHORT DirY;			// 0x16	//
		SHORT DirZ;			// 0x18	//
		SHORT AtariOffsetX;	// 0x1A	//
		SHORT AtariOffsetY;	// 0x1C	//
		SHORT AtariOffsetZ;	// 0x1E	//
		SHORT AtariSizeX;	// 0x20	//
		SHORT AtariSizeY;	// 0x22	//
		SHORT AtariSizeZ;	// 0x24	//
	} Obj_model_set;			// 0x2D	// 0x00 bytes // Obj_model_set
	struct tagWork_set {
		UCHAR Opcode;
		UCHAR Type;
		CHAR Aot;
	} Work_set;					// 0x2E	// 0x00 bytes // Work_set
	struct tagSpeed_set {
		UCHAR Opcode;
		UCHAR Id;
		USHORT Value;
	} Speed_set;					// 0x2F	// 0x00 bytes // Speed_set
	struct tagAdd_speed {
		UCHAR Opcode;
	} Add_speed;					// 0x30	// 0x00 bytes // Add_speed
	struct tagAdd_aspeed {
		UCHAR Opcode;
	} Add_aspeed;				// 0x31	// 0x00 bytes // Add_aspeed
	struct tagPos_set {
		UCHAR Opcode;
		UCHAR zAlign;
		SHORT X;
		SHORT Y;
		SHORT Z;
	} Pos_set;						// 0x32	// 0x00 bytes // Pos_set
	struct tagDir_set {
		UCHAR Opcode;
		UCHAR zAlign;
		SHORT X;
		SHORT Y;
		SHORT Z;
	} Dir_set;						// 0x33	// 0x00 bytes // Dir_set
	struct tagMember_set {
		UCHAR Opcode;
		UCHAR Destination;
		SHORT Source;
	} Member_set;				// 0x34	// 0x00 bytes // Member_set
	struct tagMember_set2 {
		UCHAR Opcode;
		UCHAR Destination;
		UCHAR Source;
	} Member_set2;				// 0x35	// 0x00 bytes // Member_set2
	struct tagSe_on {
		UCHAR Opcode;	// 0x36
		UCHAR VAB;		// VAB Bank Id
		SHORT EDT;		// EDT Sample Id
		SHORT data0;	// Sound Reverberation, Work Aot/Obj No
		SHORT X;		// Position
		SHORT Y;
		SHORT Z;
	} Se_on;							// 0x36	// 0x00 bytes // Se_on
	struct tagSca_id_set {
		UCHAR Opcode;			// 0x37	// Sca_id_set	
		UCHAR iEntry;			// SCA Collision Entry
		USHORT Id;				// New Collision ID
	} Sca_id_set;				// 0x37	// 0x00 bytes // Sca_id_set
	struct tagFlr_set {
		UCHAR Opcode;			// 0x38
		UCHAR Id;
		UCHAR Flag;
	} Flr_set;						// 0x38	// 0x00 bytes // Flr_set
	struct tagDir_ck {
		UCHAR Opcode;
		UCHAR zAlign;
		SHORT X;
		SHORT Z;
		SHORT Add;
	} Dir_ck;						// 0x39	// 0x00 bytes // Dir_ck
	struct tagSce_espr_on {
		UCHAR Opcode;
		UCHAR zAlign;
		USHORT data0;
		USHORT data1;
		USHORT data2;
		SHORT X;
		SHORT Y;
		SHORT Z;
		SHORT DirY;
	} Sce_espr_on;				// 0x3A	// 0x00 bytes // Sce_espr_on
	struct tagDoor_aot_set {
		UCHAR Opcode;		// 0x00	// 0x3B
		UCHAR Aot;			// 0x01	// Aot
		UCHAR SCE;			// 0x02	// Id		/* tagSCE_AOT
		UCHAR SAT;			// 0x03	// Type
		UCHAR nFloor;		// 0x04	// nFloor
		UCHAR Super;		// 0x05	// Super
		SHORT X;			// 0x06	// Position
		SHORT Z;			// 0x08	// Position
		USHORT W;			// 0x0A	// Size
		USHORT D;			// 0x0C	// Size		*/ tagSCE_AOT
		SHORT Next_pos_x;	// 0x0E	//			/* tagIN_DOOR_WORK
		SHORT Next_pos_y;	// 0x10	//
		SHORT Next_pos_z;	// 0x12	//
		SHORT Next_cdir_y;	// 0x14	//
		UCHAR Next_stage;	// 0x16	//
		UCHAR Next_room;	// 0x17	//
		UCHAR Next_cut;		// 0x18	//
		UCHAR Next_nfloor;	// 0x19	//
		UCHAR Dtex_type;	// 0x1A	// DO2 File Id
		UCHAR Door_type;	// 0x1B	// DO2 Animation Set
		UCHAR Knock_type;	// 0x1C	// Sound
		UCHAR Key_id;		// 0x1D	// 
		UCHAR Key_type;		// 0x1E	// 
		UCHAR Free;			// 0x1F	// 			*/ tagIN_DOOR_WORK
		// sizeof			// 0x20 bytes
	} Door_aot_set;			// 0x3B	// 0x00 bytes // Door_aot_set
	struct tagCut_auto {
		UCHAR Opcode;			// 0x3C
		UCHAR OnOff;			// 00	OFF
								// 01	ON
	} Cut_auto;					// 0x3C	// 0x00 bytes // Cut_auto
	struct tagMember_copy {
		UCHAR Opcode;
		CHAR Destination;
		CHAR Source;
	} Member_copy;				// 0x3D	// 0x00 bytes // Member_copy
	struct tagMember_cmp {
		UCHAR Opcode;			// 0x00	// 0x3E
		UCHAR zAlign;			// 0x01	// 0x00
		UCHAR Flag;				// 0x02	// Load_member_addr_branch() argv[1]
		UCHAR Operator;			// 0x03	// 
		SHORT Value;			// 0x04	// 
	} Member_cmp;				// 0x3E	// 0x00 bytes // Member_cmp
	struct tagPlc_motion {
		UCHAR Opcode;			// 0x3F
		UCHAR Animation;		// EDD/EMR Id
		UCHAR data0;			// 
		UCHAR data1;			// 
	} Plc_motion;				// 0x3F	// 0x00 bytes // Plc_motion
	struct tagPlc_dest {
		UCHAR Opcode;			// 0x40
		UCHAR zAlign;			// 0x00
		UCHAR Animation;		// EDD/EMR Id
		UCHAR Bit;				// Room_flg
		SHORT X;
		SHORT Z;				// Destination
	} Plc_dest;					// 0x40	// 0x00 bytes // Plc_dest
	struct tagPlc_neck {
		UCHAR Opcode;
		UCHAR Op;
		SHORT X;
		SHORT Y;
		SHORT Z;
		UCHAR SpeedX;
		UCHAR SpeedZ;
	} Plc_neck;					// 0x41	// 0x00 bytes // Plc_neck
	struct tagPlc_ret {
		UCHAR Opcode;
	} Plc_ret;						// 0x42	// 0x00 bytes // Plc_ret
	struct tagPlc_flg {
		UCHAR Opcode;		// 0x43
		UCHAR Type;			// 
		USHORT Flag;		// 
	} Plc_flg;						// 0x43	// 0x00 bytes // Plc_flg
	struct tagSce_em_set {
		UCHAR Opcode;			// 0x00	// 0x44
		UCHAR Nop;				// 0x01	// 0x00
		CHAR Em_no;				// 0x02	// Is NOT included in AOT pool !!!
		UCHAR Id;				// 0x03	// EMD File Id for Em_bin_load() function
		USHORT Type;			// 0x04	// 
		UCHAR nFloor;			// 0x06	// nFloor
		UCHAR Sound_flg;		// 0x07	// 
		UCHAR Model_type;		// 0x08	// 
		UCHAR Em_set_flg;		// 0x09	// Enemy_flg or Enemy_flg2 bit, to determine if enemy has been killed
		SHORT Pos_x;			// 0x0A	// Position
		SHORT Pos_y;			// 0x0C	// Position
		SHORT Pos_z;			// 0x0E	// Position
		SHORT Cdir_y;			// 0x10	// Rotation
		SHORT Motion;			// 0x12	// 
		SHORT Ctr_flg;			// 0x14	// 
		// sizeof				// 0x16 bytes
	} Sce_em_set;				// 0x44	// 0x00 bytes // Sce_em_set
	struct tagCol_chg_set {
		UCHAR Opcode;
		UCHAR Data0;
		UCHAR Data1;
		UCHAR Data2;
		UCHAR Data3;
	} Col_chg_set;				// 0x45	// 0x00 bytes // Col_chg_set			// Object Model Modification
	struct tagAot_reset {
		UCHAR Opcode;
		CHAR Aot;
		UCHAR SCE;
		UCHAR SAT;		// Scenario Atari
		SHORT Data0;
		SHORT Data1;
		SHORT Data2;
	} Aot_reset;					// 0x46	// 0x00 bytes // Aot_reset
	struct tagAot_on {
		UCHAR Opcode;
		CHAR Aot;
	} Aot_on;						// 0x47	// 0x00 bytes // Aot_on
	struct tagSuper_set {
		UCHAR Opcode;
		UCHAR zAlign;
		UCHAR Work;			// Work Type
		UCHAR Id;			// Work Aot/Obj No
		SHORT pX, pY, pZ;	// Parent
		SHORT dX, dY, dZ;	// Destination
	} Super_set;					// 0x48	// 0x00 bytes // Super_set
	struct tagSuper_reset {
		UCHAR Opcode;
		UCHAR zAlign;
		SHORT dX;
		SHORT dY;
		SHORT dZ;
	} Super_reset;				// 0x49	// 0x00 bytes // Super_reset
	struct tagPlc_gun {
		UCHAR Opcode;		// 0x4A
		UCHAR Animation;	// EDD/EMR Id
	} Plc_gun;						// 0x4A	// 0x00 bytes // Plc_gun
	struct tagCut_replace {
		UCHAR Opcode;
		UCHAR Id;
		UCHAR Value;
	} Cut_replace;				// 0x4B	// 0x00 bytes // Cut_replace
	struct tagSce_espr_kill {
		UCHAR Opcode;
		UCHAR id;				// Esp_kill() argv[0]
		UCHAR tp;				// Esp_kill() argv[1]
		CHAR WorkKind;			// Get_matrix() argv[0]
		CHAR WorkNo;			// Get_matrix() argv[1]
	} Sce_espr_kill;			// 0x4C	// 0x00 bytes // Sce_espr_kill
	struct tagDoor_model_set {
		UCHAR Opcode;		// 0x00	// 0x4D
		UCHAR data0;		// 0x01	// 
		UCHAR Id;			// 0x02	// DOOR_WORK.Id
		UCHAR OfsY;			// 0x03	// DOOR_WORK.Atd[3]
		UCHAR BeFlg;		// 0x04	// DOOR_WORK.Be_flg
		UCHAR data5;		// 0x05	// 
		USHORT data6;		// 0x06	// 
		SHORT X;			// 0x08	// DOOR_WORK.Atd[3]
		SHORT Y;			// 0x0A	// DOOR_WORK.Atd[3]
		SHORT Z;			// 0x0C	// DOOR_WORK.Atd[3]
		SHORT DirY;			// 0x0E	// DOOR_WORK.Atd[3]
		USHORT data10;		// 0x10	// DOOR_WORK.MATRIX
		USHORT data11;		// 0x12	// DOOR_WORK.MATRIX
		USHORT data12;		// 0x14	// DOOR_WORK.MATRIX
	} Door_model_set;		// 0x4D	// 0x00 bytes // Door_model_set
	struct tagItem_aot_set {
		UCHAR Opcode;		// 0x00	// 0x4E
		UCHAR Aot;			// 0x01	// Aot
		UCHAR SCE;			// 0x02	// Id		/* tagSCE_AOT
		UCHAR SAT;			// 0x03	// Type
		UCHAR nFloor;		// 0x04	// nFloor
		UCHAR Super;		// 0x05	// Super
		SHORT X;			// 0x06	// Position
		SHORT Z;			// 0x08	// Position
		USHORT W;			// 0x0A	// Size
		USHORT D;			// 0x0C	// Size		*/ tagSCE_AOT
		USHORT iItem;		// 0x0E	// Item Id
		USHORT nItem;		// 0x10	// Item Amount
		USHORT Flag;		// 0x12	// Item_flg/2 Bit
		UCHAR MD1;			// 0x14	// MD1 File Id - 0xFF if no MD1
		UCHAR Action;		// 0x15	// Predefined action taken to obtain
	} Item_aot_set;			// 0x4E	// 0x00 bytes // Item_aot_set
	struct tagSce_key_ck {
		UCHAR Opcode;
		UCHAR Flag;
		USHORT Value;
	} Sce_key_ck;				// 0x4F	// 0x00 bytes // Sce_key_ck
	struct tagSce_trg_ck {
		UCHAR Opcode;
		UCHAR Flag;
		USHORT Value;
	} Sce_trg_ck;				// 0x50	// 0x00 bytes // Sce_trg_ck
	struct tagSce_bgm_control {
		UCHAR Opcode;		// 0x51
		UCHAR Id;
		UCHAR Op;
		UCHAR Type;
		UCHAR VolL;			// Volume Left
		UCHAR VolR;			// Volume Right
	} Sce_bgm_control;		// 0x51	// 0x00 bytes // Sce_bgm_control
	struct tagSce_espr_control {
		UCHAR Opcode;	// 0x00	// 0x52
		UCHAR Id;		// 0x01	// 
		UCHAR Type;		// 0x02	// 
		UCHAR Return;	// 0x03	// 
		CHAR WorkKind;	// 0x04	// 
		CHAR WorkNo;	// 0x05	// 
	} Sce_espr_control;	// 0x52	// 0x00 bytes // Sce_espr_control
	struct tagSce_fade_set {
		UCHAR Opcode;
		UCHAR data0;
		UCHAR data1;
		UCHAR data2;
		USHORT data3;
	} Sce_fade_set;			// 0x53	// 0x00 bytes // Sce_fade_set
	struct tagSce_espr3d_on {
		UCHAR Opcode;
		UCHAR zAlign;
		USHORT data0;
		USHORT data1;
		USHORT data2;
		SHORT X;
		SHORT Y;
		SHORT Z;
		SHORT DirX;
		SHORT DirY;
		SHORT DirZ;
		SHORT data3;
	} Sce_espr3d_on;			// 0x54	// 0x00 bytes // Sce_espr3d_on
	struct tagMember_calc {
		UCHAR Opcode;			// 0x00	// 0x55
		UCHAR Operator;				// 0x01	// Calc_branch() argv[0]
		USHORT Flag;			// 0x02	// Load_member_addr_branch() argv[1]
		SHORT Value;				// 0x04	// Calc_branch() argv[2]
	} Member_calc;				// 0x55	// 0x00 bytes // Member_calc
	struct tagMember_calc2 {
		UCHAR Opcode;		// 0x00	// 0x56
		UCHAR Operator;			// 0x01	// Calc_branch() argv[0]
		UCHAR Flag;		// 0x02	// Load_member_addr_branch() argv[1]
		UCHAR Value;			// 0x03	// Calc_branch() argv[2]
	} Member_calc2;			// 0x56	// 0x00 bytes // Member_calc2
	struct tagSce_bgmtbl_set {
		UCHAR Opcode;
		UCHAR zAlign;
		UCHAR Stage;
		UCHAR Room;
		USHORT data1;
		USHORT data2;	// 0x0000, 0x0040, 0x8000, 0x8040, 0xC000 or 0xC040
	} Sce_bgmtbl_set;		// 0x57	// 0x00 bytes // Sce_bgmtbl_set
	struct tagPlc_rot {
		UCHAR Opcode;
		UCHAR Id;
		USHORT Sce_free0;
	} Plc_rot;						// 0x58	// 0x00 bytes // Plc_rot
	struct tagXa_on {
		UCHAR Opcode;
		UCHAR Mode;
		USHORT Number;
	} Xa_on;							// 0x59	// 0x00 bytes // Xa_on
	struct tagWeapon_chg {
		UCHAR Opcode;
		UCHAR Id;
	} Weapon_chg;				// 0x5A	// 0x00 bytes // Weapon_chg
	struct tagPlc_cnt {
		UCHAR Opcode;
		UCHAR Id;
	} Plc_cnt;						// 0x5B	// 0x00 bytes // Plc_cnt
	struct tagSce_shake_on {
		UCHAR Opcode;		// 0x00 // 0x5C
		CHAR Slide_ofs;		// 0x01 // line_trans() argv[1]
		CHAR Copy_ofs;		// 0x02 // line_trans() argv[2]
	} Sce_shake_on;			// 0x5C	// 0x00 bytes // Sce_shake_on
	struct tagMizu_div_set {
		UCHAR Opcode;
		UCHAR Id;
	} Mizu_div_set;			// 0x5D	// 0x00 bytes // Mizu_div_set			// Water_div_set
	struct tagKeep_Item_ck {
		UCHAR Opcode;
		UCHAR Id;
	} Keep_Item_ck;			// 0x5E	// 0x00 bytes // Keep_Item_ck
	struct tagXa_vol {
		UCHAR Opcode;
		UCHAR Value;
	} Xa_vol;						// 0x5F	// 0x00 bytes // Xa_vol
	struct tagKage_set {
		UCHAR Opcode;
		UCHAR Work;
		CHAR Id;
		UCHAR Data0;
		UCHAR Data1;
		UCHAR Data2;
		USHORT Data3;
		USHORT Data4;
		USHORT Data5;
		USHORT Data6;
	} Kage_set;					// 0x60	// 0x00 bytes // Kage_set				// Shadow_set
	struct tagCut_be_set {
		UCHAR Opcode;
		UCHAR Id;
		UCHAR Value;
		UCHAR OnOff;
	} Cut_be_set;				// 0x61	// 0x00 bytes // Cut_be_set
	struct tagSce_Item_lost {
		UCHAR Opcode;
		UCHAR Id;
	} Sce_Item_lost;			// 0x62	// 0x00 bytes // Sce_Item_lost
	struct tagPlc_gun_eff {
		UCHAR Opcode;		// 0x63
	} Plc_gun_eff;				// 0x63	// 0x00 bytes // Plc_gun_eff
	struct tagSce_espr_on2 {
		UCHAR Opcode;		// 0x00	// 0x63
		UCHAR dir_y_id2;	// 0x01	// Esp_call2() parameter
		USHORT data1;		// 0x02	// Esp_call2() parameter
		UCHAR WorkKind;		// 0x04	// Get_matrix() parameter 0
		UCHAR WorkNo;		// 0x05	// Get_matrix() parameter 1
		USHORT data3;		// 0x06	// Esp_call2() parameter
		SHORT X;			// 0x08	// Esp_call2() parameter
		SHORT Y;			// 0x0A	// Esp_call2() parameter
		SHORT Z;			// 0x0C	// Esp_call2() parameter
		USHORT DirY;		// 0x0E	// Esp_call2() parameter
	} Sce_espr_on2;			// 0x64	// 0x00 bytes // Sce_espr_on2
	struct tagSce_espr_kill2 {
		UCHAR Opcode;
		UCHAR Id;
	} Sce_espr_kill2;		// 0x65	// 0x00 bytes // Sce_espr_kill2
	struct tagPlc_stop {
		UCHAR Opcode;
	} Plc_stop;					// 0x66	// 0x00 bytes // Plc_stop
	struct tagAot_set_4p {
		UCHAR Opcode;			// 0x00 // 0x67
		UCHAR Aot;				// 0x01 // Aot
		UCHAR SCE;				// 0x02 // Id		/* tagSCE_AOT2
		UCHAR SAT;				// 0x03 // Type
		UCHAR nFloor;			// 0x04 // nFloor
		UCHAR Super;			// 0x05 // Super
		SHORT X0;				// 0x06 // Size #1
		SHORT Z0;				// 0x08 // Size #1
		SHORT X1;				// 0x0A // Size #2
		SHORT Z1;				// 0x0C // Size #2
		SHORT X2;				// 0x0E // Size #3
		SHORT Z2;				// 0x10 // Size #3
		SHORT X3;				// 0x12 // Size #4
		SHORT Z3;				// 0x14 // Size #4	*/ tagSCE_AOT2
		USHORT Data0;			// 0x16 //			/* tagSCE_AT_DATA
		USHORT Data1;			// 0x18 // 
		USHORT Data2;			// 0x1A //			*/ tagSCE_AT_DATA
		// sizeof				// 0x20 bytes
	} Aot_set_4p;				// 0x67	// 0x00 bytes // Aot_set_4p
	struct tagDoor_aot_set_4p {
		UCHAR Opcode;		// 0x00 // 0x68
		UCHAR Aot;			// 0x01 // Aot
		UCHAR SCE;			// 0x02 // Id		/* tagSCE_AOT2
		UCHAR SAT;			// 0x03 // Type
		UCHAR nFloor;		// 0x04 // nFloor
		UCHAR Super;		// 0x05 // Super
		SHORT X0;			// 0x06 // Size #1
		SHORT Z0;			// 0x08 // Size #1
		SHORT X1;			// 0x0A // Size #2
		SHORT Z1;			// 0x0C // Size #2
		SHORT X2;			// 0x0E // Size #3
		SHORT Z2;			// 0x10 // Size #3
		SHORT X3;			// 0x12 // Size #4
		SHORT Z3;			// 0x14 // Size #4	*/ tagSCE_AOT2
		SHORT Next_pos_x;	// 0x16	//			/* tagIN_DOOR_WORK
		SHORT Next_pos_y;	// 0x18	//
		SHORT Next_pos_z;	// 0x1A	//
		SHORT Next_cdir_y;	// 0x1C	//
		UCHAR Next_stage;	// 0x1E	//
		UCHAR Next_room;	// 0x1F	//
		UCHAR Next_cut;		// 0x20	//
		UCHAR Next_nfloor;	// 0x21	//
		UCHAR Dtex_type;	// 0x22	// DO2 File Id
		UCHAR Door_type;	// 0x23	// DO2 Animation Set
		UCHAR Knock_type;	// 0x24	// Sound
		UCHAR Key_id;		// 0x25	// 
		UCHAR Key_type;		// 0x26	// 
		UCHAR Free;			// 0x27	// 			*/ tagIN_DOOR_WORK
		// sizeof			// 0x28 bytes
	} Door_aot_set_4p;		// 0x68	// 0x00 bytes // Door_aot_set_4p
	struct tagItem_aot_set_4p {
		UCHAR Opcode;		// 0x00 // 0x69
		UCHAR Aot;			// 0x01 // Aot
		UCHAR SCE;			// 0x02 // Id		/* tagSCE_AOT2
		UCHAR SAT;			// 0x03 // Type
		UCHAR nFloor;		// 0x04 // nFloor
		UCHAR Super;		// 0x05 // Super
		SHORT X0;			// 0x06 // Size #1
		SHORT Z0;			// 0x08 // Size #1
		SHORT X1;			// 0x0A // Size #2
		SHORT Z1;			// 0x0C // Size #2
		SHORT X2;			// 0x0E // Size #3
		SHORT Z2;			// 0x10 // Size #3
		SHORT X3;			// 0x12 // Size #4
		SHORT Z3;			// 0x14 // Size #4	*/ tagSCE_AOT2
		USHORT iItem;		// 0x16 // Item Id	/* tagSCE_ITEM_DATA
		USHORT nItem;		// 0x18 // Item Amount
		USHORT Flag;		// 0x1A // Item_flg or Item_flg2 Bit
		UCHAR MD1;			// 0x1C // Om_no File Id (0xFF if no MD1 runtime data)
		UCHAR Action;		// 0x1D // Free		*/ tagSCE_ITEM_DATA
									// 00	Stand (UNTESTED PLACEHOLDER TEXT)
									// 01	Kneel (UNTESTED PLACEHOLDER TEXT)
		// sizeof			// 0x1E bytes
	} Item_aot_set_4p;		// 0x69	// 0x00 bytes // Item_aot_set_4p
	struct tagLight_pos_set {
		UCHAR Opcode;
		UCHAR zAlign;
		UCHAR Index;	// 00, 01 or 02
		UCHAR XYZ;		// 11, 12 or 13
		SHORT Position;
	} Light_pos_set;			// 0x6A	// 0x00 bytes // Light_pos_set
	struct tagLight_kido_set {
		UCHAR Opcode;
		UCHAR Index;	// 00, 01 or 02
		SHORT Luminosity;
	} Light_kido_set;		// 0x6B	// 0x00 bytes // Light_kido_set		// Light_brightness_set
	struct tagRbj_reset {
		UCHAR Opcode;
	} Rbj_reset;					// 0x6C	// 0x00 bytes // Rbj_reset
	struct tagSce_scr_move {
		UCHAR Opcode;
		UCHAR zAlign;
		SHORT Scrl_y;		// 0x02 // G.Scrl_y
	} Sce_scr_move;			// 0x6D	// 0x00 bytes // Sce_scr_move
	struct tagParts_set {
		UCHAR Opcode;
		UCHAR zAlign;
		CHAR Id;
		CHAR Type;
		SHORT Value;
	} Parts_set;					// 0x6E	// 0x00 bytes // Parts_set
	struct tagMovie_on {
		UCHAR Opcode;
		UCHAR Id;
	} Movie_on;					// 0x6F	// 0x00 bytes // Movie_on
	struct tagSplc_ret {
		UCHAR Opcode;
	} Splc_ret;					// 0x70	// 0x00 bytes // Splc_ret
	struct tagSplc_sce {
		UCHAR Opcode;
	} Splc_sce;					// 0x71	// 0x00 bytes // Splc_sce
	struct tagSuper_on {
		UCHAR Opcode;
		UCHAR zAlign;
		UCHAR data0;
		UCHAR data1;
		SHORT data2;
		SHORT data3;
		SHORT data4;
		SHORT data5;
		SHORT data6;
		SHORT data7;
	} Super_on;					// 0x72	// 0x00 bytes // Super_on
	struct tagMirror_set {
		UCHAR Opcode;
		UCHAR Flag;
		USHORT Position;
		USHORT Min;
		USHORT Max;
	} Mirror_set;				// 0x73	// 0x00 bytes // Mirror_set
	struct tagSce_fade_adjust {
		UCHAR Opcode;
		UCHAR data0;
		SHORT data1;
	} Sce_fade_adjust;		// 0x74	// 0x00 bytes // Sce_fade_adjust
	struct tagSce_espr3d_on2 {
		UCHAR Opcode;		// 0x00 // 0x75
		UCHAR dir_y_id2;	// 0x01 // Esp_call3D2() argv[1]
		USHORT bit;			// 0x02 // Esp_call3D2() argv[0]
		USHORT data4;		// 0x04 // Get_matrix() argv[0]
		USHORT data6;
		USHORT data8;
		USHORT dataA;
		USHORT dataC;
		USHORT dataE;
		USHORT data10;
		USHORT data12;
		USHORT data14;
	} Sce_espr3d_on2;		// 0x75	// 0x00 bytes // Sce_espr3d_on2
	struct tagSce_Item_get {
		UCHAR Opcode;
		UCHAR Id;
		UCHAR Num;
	} Sce_Item_get;			// 0x76	// 0x00 bytes // Sce_Item_get
	struct tagSce_line_start {
		UCHAR Opcode;
		UCHAR Id;
		USHORT Value;
	} Sce_line_start;		// 0x77	// 0x00 bytes // Sce_line_start
	struct tagSce_line_main {
		UCHAR Opcode;
		UCHAR Id;
		SHORT Data0;
		SHORT Data1;
	} Sce_line_main;			// 0x78	// 0x00 bytes // Sce_line_main
	struct tagSce_line_end {
		UCHAR Opcode;
	} Sce_line_end;			// 0x79	// 0x00 bytes // Sce_line_end
	struct tagSce_parts_bomb {
		UCHAR Opcode;
		UCHAR zAlign;
		UCHAR data2;
		UCHAR data3;
		UCHAR data4;
		UCHAR data5;
		SHORT data6;
		SHORT data8;
		SHORT dataA;
		SHORT dataC;
		SHORT dataE;
	} Sce_parts_bomb;		// 0x7A	// 0x00 bytes // Sce_parts_bomb
	struct tagSce_parts_down {
		UCHAR Opcode;
		UCHAR Id;
		SHORT X;
		SHORT Y;
		SHORT Z;
		SHORT cDirZ;
		SHORT DirX;
		SHORT DirY;
		SHORT DirZ;
	} Sce_parts_down;		// 0x7B	// 0x00 bytes // Sce_parts_down
	struct tagLight_color_set {
		UCHAR Opcode;
		UCHAR Index;
		UCHAR R;
		UCHAR G;
		UCHAR B;
		UCHAR zAlign;
	} Light_color_set;	 	// 0x7C	// 0x00 bytes // Light_color_set
	struct tagLight_pos_set2 {
		UCHAR Opcode;
		UCHAR nCut;		// Camera Id
		UCHAR Index;	// 00, 01 or 02
		UCHAR XYZ;		// 11, 12 or 13
		SHORT Position;
	} Light_pos_set2;		// 0x7D	// 0x00 bytes // Light_pos_set2
	struct tagLight_kido_set2 {
		UCHAR Opcode;
		UCHAR zAlign;
		UCHAR nCut;
		UCHAR Index;
		USHORT Luminosity;
	} Light_kido_set2;		// 0x7E	// 0x00 bytes // Light_kido_set2
	struct tagLight_color_set2 {
		UCHAR Opcode;
		UCHAR nCut;
		UCHAR Index;
		UCHAR R;
		UCHAR G;
		UCHAR B;
	} Light_color_set2;	// 0x7F	// 0x00 bytes // Light_color_set2
	struct tagSe_vol {
		UCHAR Opcode;
		UCHAR Value;
	} Se_vol;						// 0x80	// 0x00 bytes // Se_vol
	struct tagSce_Item_cmp {
		UCHAR Opcode;
		UCHAR data0;
		UCHAR data1;
	} Sce_Item_cmp;			// 0x81	// 0x00 bytes // Sce_Item_cmp (room60A, only)
	struct tagSce_espr_task {
		UCHAR Opcode;
		CHAR WorkKind;			// Get_matrix() argv[0]
		CHAR WorkNo;			// Get_matrix() argv[1]
	} Sce_espr_task;			// 0x82	// 0x00 bytes // Triggers a Loop_ctr task for ESP
	struct tagPlc_heal {
		UCHAR Opcode;
	} Plc_heal;					// 0x83	// 0x00 bytes // Used only once (room410), disable poison, restore Life
	struct tagSt_map_hint {
		UCHAR Opcode;			// 0x00 // 0x84
		UCHAR DrModeTag;		// 0x01 // St.Dmode[1].tag
	} St_map_hint;				// 0x84	// 0x00 bytes // Trigger an automatic map check
	struct tagSce_em_pos_ck {
		UCHAR Opcode;			// 0x00 // 0x85
		UCHAR Id;				// 0x01 // G.pEnemy Id
		UCHAR data1;			// 0x02 // 
		UCHAR Att;				// 0x03 // Sca_ck_line() argv[2]
		USHORT Flg;				// 0x04 // Sca_ck_line() argv[3]
	} Sce_em_pos_ck;			// 0x85	// 0x00 bytes // Used once (room109), check /player enemy position
	struct tagPoison_ck {
		UCHAR Opcode;
	} Poison_ck;					// 0x86	// 0x00 bytes // Check poison status, used for "Blue Herb is growing here."
	struct tagPoison_clr {
		UCHAR Opcode;
	} Poison_clr;				// 0x87	// 0x00 bytes // Disable poison status, if Blue Herb is used
	struct tagSce_Item_lost2 {
		UCHAR Opcode;
		UCHAR Id;			// 0x01 // Search_item_id() argv[0]
		UCHAR Num;			// 0x02 // G.Save.Item_work.Num
	} Sce_Item_lost2;		// 0x88	// 0x00 bytes // Alternate version of Sce_Item_lost
	struct tagEvt_next2 {
		UCHAR Opcode;
	} Evt_next2;					// 0x89	// 0x00 bytes // Alternate version of Evt_next (modifies G.pEnemy)
	struct tagVib_set0 {
		UCHAR Opcode;
		UCHAR zAlign;
		USHORT data0;
		USHORT data1;
	} Vib_set0;					// 0x8A	// 0x00 bytes // Dual Shock Controller vibration
	struct tagVib_set1 {
		UCHAR Opcode;
		UCHAR Id;
		USHORT data0;
		USHORT data1;
	} Vib_set1;					// 0x8B	// 0x00 bytes // Dual Shock Controller vibration
	struct tagVib_fade_set {
		UCHAR Opcode;
		UCHAR zAlign;
		UCHAR data0;
		UCHAR data1;
		USHORT data2;
		USHORT data3;
	} Vib_fade_set;			// 0x8C	// 0x00 bytes // Dual Shock Controller vibration
	struct tagItem_aot_set2 {
		UCHAR Opcode;			// 0x00	// 0x8D
		UCHAR Aot;				// 0x01	// Id
		UCHAR SCE;				// 0x02	// Type (0x02)
		UCHAR SAT;				// 0x03	// Atari
		UCHAR nFloor;			// 0x04	// Height
		UCHAR Super;			// 0x05	// Matrix
		SHORT X;				// 0x06	// Position
		SHORT Z;				// 0x08	// Position
		USHORT W;				// 0x0A	// Size
		USHORT D;				// 0x0C	// Size
		USHORT iItem;			// 0x0E	// Item Id
		USHORT nItem;			// 0x10	// Item Amount
		USHORT Flag;			// 0x12	// argv[1] for Flg_on() and Flg_ck()
		UCHAR MD1;				// 0x14	// MD1 File Id - 0xFF if no MD1
		UCHAR Action;			// 0x15	// Predefined action taken to obtain
		UCHAR data16;			// 0x16	// 
		UCHAR data17;			// 0x17	// 
	} Item_aot_set2;			// 0x8D	// 0x00 bytes // Alternate version of Item_aot_set2 (EX Battle, only)
	struct tagSce_em_set2 {
		UCHAR Opcode;			// 0x00	// 0x8E
		UCHAR zAlign;			// 0x01	// 0x00
		UCHAR Aot;				// 0x02	// 
		UCHAR EMD;				// 0x03	// 
		USHORT Type;			// 0x04	// 
		UCHAR nFloor;			// 0x06	// 
		UCHAR SeType;			// 0x07	// 
		UCHAR ModelType;		// 0x08	// 
		UCHAR EmSetFlg;			// 0x09	// 
		SHORT X;				// 0x0A	// 
		SHORT Y;				// 0x0C	// 
		SHORT Z;				// 0x0E	// 
		SHORT DirY;				// 0x10	// 
		USHORT Timer0;			// 0x12	// 
		USHORT Timer1;			// 0x14	// 
		USHORT data16;			// 0x16	// 
	} Sce_em_set2;				// 0x8E	// 0x00 bytes // Alternate version of Sce_em_set (EX Battle, only)
} Bio2Bytecode;	    // Bio Hazard 2 Dual Shock
typedef struct tagBio3Bytecode {
	UCHAR Opcode;											// Temporary Buffer
	struct tagNop {
		UCHAR Opcode;
	} Nop;								// 0x00	// Nop
	struct tagEvt_end {
		UCHAR Opcode;
		UCHAR zAlign;
	} Evt_end;						// 0x01	// Evt_end
	struct tagEvt_next {
		UCHAR Opcode;
	} Evt_next;					// 0x02	// Evt_next
	struct tagEvt_chain {
		UCHAR Opcode;
		UCHAR data1;
	} Evt_chain;					// 0x03	// Evt_chain
	struct tagEvt_exec {
		UCHAR Opcode;
		UCHAR data1;
		UCHAR data2;
		UCHAR data3;
	} Evt_exec;					// 0x04	// Evt_exec
	struct tagEvt_kill {
		UCHAR Opcode;
		UCHAR data1;
	} Evt_kill;					// 0x05	// Evt_kill
	struct tagIfel_ck {
		UCHAR Opcode;
		UCHAR zAlign;
		USHORT data2;
	} Ifel_ck;						// 0x06	// Ifel_ck
	struct tagElse_ck {
		UCHAR Opcode;
		UCHAR zAlign;
		USHORT data2;
	} Else_ck;						// 0x07	// Else_ck
	struct tagEndif {
		UCHAR Opcode;
		UCHAR zAlign;
	} Endif;							// 0x08	// Endif
	struct tagSleep {
		UCHAR Opcode;
		UCHAR data1;
		USHORT data2;
	} Sleep;							// 0x09	// Sleep
	struct tagSleeping {
		UCHAR Opcode;
		USHORT data2;
	} Sleeping;					// 0x0A	// Sleeping
	struct tagWsleep {
		UCHAR Opcode;
		UCHAR zAlign;
	} Wsleep;						// 0x0B	// Wsleep
	struct tagWsleeping {
		UCHAR Opcode;
	} Wsleeping;					// 0x0C	// Wsleeping
	struct tagFor {
		UCHAR Opcode;
		UCHAR zAlign;
		SHORT data2;
		USHORT data4;
	} For;								// 0x0D	// For
	struct tagFor2 {
		UCHAR Opcode;
		UCHAR zAlign0;
		SHORT data2;
		UCHAR zAlign1;
		UCHAR data5;
	} For2;							// 0x0E	// For2
	struct tagNext {
		UCHAR Opcode;
		UCHAR zAlign;
	} Next;							// 0x0F	// Next
	struct tagWhile {
		UCHAR Opcode;
		UCHAR zAlign;
		SHORT data1;
	} While;							// 0x10	// While
	struct tagEwhile {
		UCHAR Opcode;
		UCHAR data1;
	} Ewhile;						// 0x11	// Ewhile
	struct tagDo {
		UCHAR Opcode;
		UCHAR zAlign;
		SHORT data2;
	} Do;								// 0x12	// Do
	struct tagEdwhile {
		UCHAR Opcode;
		UCHAR data1;
	} Edwhile;						// 0x13	// Edwhile
	struct tagSwitch {
		UCHAR Opcode;
		UCHAR data1;
		USHORT data2;
	} Switch;						// 0x14	// Switch
	struct tagCase {
		UCHAR Opcode;
		UCHAR zAlign[5];
	} Case;							// 0x15	// Case
	struct tagDefault {
		UCHAR Opcode;
		UCHAR zAlign;
	} Default;						// 0x16	// Default
	struct tagEswitch {
		UCHAR Opcode;
		UCHAR zAlign;
	} Eswitch;						// 0x17	// Eswitch
	struct tagGoto {
		UCHAR Opcode;
		UCHAR data1;
		UCHAR data2;
		UCHAR zAlign;
		SHORT data4;
	} Goto;							// 0x18	// Goto
	struct tagGosub {
		UCHAR Opcode;
		UCHAR data1;
	} Gosub;							// 0x19	// Gosub
	struct tagReturn {
		UCHAR Opcode;
		UCHAR data[3];
	} Return;						// 0x1A	// Return				// WIP
	struct tagBreak {
		UCHAR Opcode;
		CHAR data1;
	} Break;							// 0x1B	// Break
	struct tagBreak_point {
		UCHAR Opcode;
	} Break_point;				// 0x1C	// Break_point
	struct tagWork_copy {
		UCHAR Opcode;
		UCHAR data1;
		UCHAR data2;
		UCHAR data3;
	} Work_copy;					// 0x1D	// Work_copy
	struct tagSave {
		UCHAR Opcode;
		UCHAR data1;
		SHORT data2;
	} Save;							// 0x1E	// Save
	struct tagCopy {
		UCHAR Opcode;
		UCHAR data1;
		UCHAR data2;
	} Copy;							// 0x1F	// Copy
	struct tagCalc {
		UCHAR Opcode;
		UCHAR zAlign;
		USHORT data2;
		SHORT data4;
	} Calc;							// 0x20	// Calc
	struct tagCalc2 {
		UCHAR Opcode;
		UCHAR data1;
		UCHAR data2;
		UCHAR data3;
	} Calc2;							// 0x21	// Calc2
	struct tagEvt_cut {
		UCHAR Opcode;
		UCHAR data1;				// if(data1 != 1) sizeof(tagEvt_cut) == 2 /* do not read data3 */
									// else sizeof(tagEvt_cut) == 4 /* data3 will be read */
		UCHAR zAlign;
		UCHAR data3;
	} Evt_cut;						// 0x22	// Evt_cut
	struct tagOpcode24 {
		UCHAR Opcode;
	} Opcode24;					// 0x23	// Nop
	struct tagChaser_evt_clr {
		UCHAR Opcode;
	} Chaser_evt_clr;		// 0x24	// Chaser_evt_clr
	struct tagMap_open {
		UCHAR Opcode;
		UCHAR zAlign0;
		UCHAR data2;
		UCHAR zAlign1;
	} Map_open;					// 0x25	// Map_open
	struct tagPoint_add {
		UCHAR Opcode;
		UCHAR zAlign;
		USHORT data2;
		USHORT data4;
	} Point_add;					// 0x26	// Point_add
	struct tagDoor_ck {
		UCHAR Opcode;
	} Door_ck;						// 0x27	// Door_ck
	struct tagDiedemo_on {
		UCHAR Opcode;
	} Diedemo_on;				// 0x28	// Diedemo_on
	struct tagDir_ck {
		UCHAR Opcode;
		UCHAR zAlign;
		SHORT data2;
		SHORT data4;
		SHORT data6;
	} Dir_ck;						// 0x29	// Dir_ck
	struct tagParts_set {
		UCHAR Opcode;
		UCHAR zAlign;
		CHAR data2;
		CHAR data3;
		USHORT data4;
	} Parts_set;					// 0x2A	// Parts_set
	struct tagVloop_set {
		UCHAR Opcode;
		UCHAR data1;
	} Vloop_set;					// 0x2B	// Vloop_set
	struct tagOta_be_set {
		UCHAR Opcode;
		UCHAR data1;
		UCHAR data2;
		UCHAR data3;
	} Ota_be_set;				// 0x2C	// Ota_be_set
	struct tagLine_start {
		UCHAR Opcode;
		UCHAR data1;
		USHORT data2;
	} Line_start;				// 0x2D	// Line_start
	struct tagLine_main {
		UCHAR Opcode;
		UCHAR data1;
		SHORT data2;
		SHORT data4;
	} Line_main;					// 0x2E	// Line_main
	struct tagLine_end {
		UCHAR Opcode;
	} Line_end;					// 0x2F	// Line_end
	struct tagLight_pos_set {
		UCHAR Opcode;
		UCHAR data1;
		UCHAR data2;
		UCHAR data3;
		USHORT data4;
	} Light_pos_set;			// 0x30	// Light_pos_set
	struct tagLight_kido_set {
		UCHAR Opcode;
		UCHAR zAlign;
		UCHAR data2;
		UCHAR data3;
		USHORT data4;
	} Light_kido_set;		// 0x31	// Light_kido_set
	struct tagLight_color_set {
		UCHAR Opcode;
		UCHAR data1;
		UCHAR data2;
		UCHAR data3;
		UCHAR data4;
		UCHAR data5;
	} Light_color_set;		// 0x32	// Light_color_set
	struct tagAhead_room_set {
		UCHAR Opcode;
		UCHAR zAlign;
		USHORT data2;
	} Ahead_room_set;		// 0x33	// Ahead_room_set
	struct tagEspr_ctr {
		UCHAR Opcode;
		UCHAR data1;
		UCHAR data2;
		CHAR data3;
		CHAR data4;
		UCHAR data5;
		UCHAR data6;
		UCHAR data7;
		UCHAR data8;
		UCHAR zAlign;
	} Espr_ctr;					// 0x34	// Espr_ctr
	struct tagBgm_tbl_ck {
		UCHAR Opcode;
		UCHAR zAlign;
		UCHAR data2;
		UCHAR data3;
		USHORT data4;
	} Bgm_tbl_ck;				// 0x35	// Bgm_tbl_ck
	struct tagItem_get_ck {
		UCHAR Opcode;
		UCHAR data1;
		UCHAR data2;
	} Item_get_ck;				// 0x36	// Item_get_ck
	struct tagOm_rev {
		UCHAR Opcode;
		UCHAR data1;
	} Om_rev;						// 0x37	// Om_rev
	struct tagChaser_life_init {
		UCHAR Opcode;
		UCHAR data1;
	} Chaser_life_init;	// 0x38	// Chaser_life_init
	struct tagParts_bomb {
		UCHAR Opcode;
		UCHAR data1;
		UCHAR data2;
		UCHAR data3;
		UCHAR data4;
		UCHAR data5;
		USHORT data6;
		USHORT data8;
		USHORT dataA;
		USHORT dataC;
		USHORT dataE;
	} Parts_bomb;				// 0x39	// Parts_bomb
	struct tagParts_down {
		UCHAR Opcode;
		UCHAR data1;
		USHORT data2;
		USHORT data4;
		USHORT data6;
		USHORT data8;
		USHORT dataA;
		USHORT dataC;
		USHORT dataE;
	} Parts_down;				// 0x3A	// Parts_down
	struct tagChaser_item_set {
		UCHAR Opcode;
		UCHAR data1;
		UCHAR data2;
	} Chaser_item_set;		// 0x3B	// Chaser_item_set
	struct tagWeapon_chg_old {
		UCHAR Opcode;
	} Weapon_chg_old;		// 0x3C	// Weapon_chg_old
	struct tagSel_evt_on {
		UCHAR Opcode;
		UCHAR data1;
	} Sel_evt_on;				// 0x3D	// Sel_evt_on
	struct tagItem_lost {
		UCHAR Opcode;
		UCHAR data1;
	} Item_lost;					// 0x3E	// Item_lost
	struct tagFlr_set {
		UCHAR Opcode;
		UCHAR data1;
		UCHAR data2;
	} Flr_set;						// 0x3F	// Flr_set
	struct tagMemb_set {
		UCHAR Opcode;
		UCHAR data1;
		SHORT data2;
	} Memb_set;					// 0x40	// Memb_set
	struct tagMemb_set2 {
		UCHAR Opcode;
		UCHAR data1;
		UCHAR data2;
	} Memb_set2;					// 0x41	// Memb_set2
	struct tagMemb_cpy {
		UCHAR Opcode;
		CHAR data1;
		CHAR data2;
	} Memb_cpy;					// 0x42	// Memb_cpy
	struct tagMemb_cmp {
		UCHAR Opcode;
		UCHAR zAlign;
		USHORT data2;
		SHORT data4;
	} Memb_cmp;					// 0x43	// Memb_cmp
	struct tagMemb_calc {
		UCHAR Opcode;
		UCHAR zAlign;
		USHORT data2;
		SHORT data4;
	} Memb_calc;					// 0x44	// Memb_calc
	struct tagMemb_calc2 {
		UCHAR Opcode;
		UCHAR data1;
		UCHAR data2;
		UCHAR data3;
	} Memb_calc2;				// 0x45	// Memb_calc2
	struct tagFade_set {
		UCHAR Opcode;
		UCHAR data1;
		UCHAR data2;
		UCHAR data3;
		UCHAR data4;
		UCHAR data5;
		UCHAR data6;
		UCHAR data7;
		UCHAR data8;
		UCHAR data9;
		UCHAR dataA;
	} Fade_set;					// 0x46	// Fade_set
	struct tagWork_set {
		UCHAR Opcode;
		UCHAR data1;
		CHAR data2;
	} Work_set;					// 0x47	// Work_set
	struct tagSpd_set {
		UCHAR Opcode;
		UCHAR data1;
		USHORT data2;
	} Spd_set;						// 0x48	// Spd_set
	struct tagAdd_spd {
		UCHAR Opcode;
	} Add_spd;						// 0x49	// Add_spd
	struct tagAdd_aspd {
		UCHAR Opcode;
	} Add_aspd;					// 0x4A	// Add_aspd
	struct tagAdd_vspd {
		UCHAR Opcode;
	} Add_vspd;					// 0x4B	// Add_vspd
	struct tagCk {
		UCHAR Opcode;
		UCHAR data1;
		USHORT data2;
	} Ck;								// 0x4C	// Ck
	struct tagSet {
		UCHAR Opcode;
		UCHAR data1;
		UCHAR data2;
		UCHAR data3;
	} Set;								// 0x4D	// Set
	struct tagCmp {
		UCHAR Opcode;
		UCHAR zAlign;
		USHORT data2;
		SHORT data4;
	} Cmp;								// 0x4E	// Cmp
	struct tagRnd {
		UCHAR Opcode;
	} Rnd;								// 0x4F	// Rnd
	struct tagCut_chg {
		UCHAR Opcode;
		UCHAR data1;
	} Cut_chg;						// 0x50	// Cut_chg
	struct tagCut_old {
		UCHAR Opcode;
	} Cut_old;						// 0x51	// Cut_old
	struct tagCut_auto {
		UCHAR Opcode;
		UCHAR data1;
	} Cut_auto;					// 0x52	// Cut_auto
	struct tagCut_replace {
		UCHAR Opcode;
		UCHAR data1;
		UCHAR data2;
	} Cut_replace;				// 0x53	// Cut_replace
	struct tagCut_be_set {
		UCHAR Opcode;
		UCHAR data1;
		UCHAR data2;
		UCHAR data3;
	} Cut_be_set;				// 0x54	// Cut_be_set
	struct tagPos_set {
		UCHAR Opcode;
		UCHAR zAlign;
		SHORT data2;
		SHORT data4;
		SHORT data6;
	} Pos_set;						// 0x55	// Pos_set
	struct tagDir_set {
		UCHAR Opcode;
		UCHAR zAlign;
		SHORT data2;
		SHORT data4;
		SHORT data6;
	} Dir_set;						// 0x56	// Dir_set
	struct tagSet_vib0 {
		UCHAR Opcode;
		UCHAR zAlign;
		USHORT data2;
		USHORT data4;
	} Set_vib0;					// 0x57	// Set_vib0
	struct tagSet_vib1 {
		UCHAR Opcode;
		UCHAR data1;
		USHORT data2;
		USHORT data4;
	} Set_vib1;					// 0x58	// Set_vib1
	struct tagSet_vib_fade {
		UCHAR Opcode;
		UCHAR zAlign;
		UCHAR data2;
		UCHAR data3;
		USHORT data4;
		USHORT data6;
	} Set_vib_fade;			// 0x59	// Set_vib_fade
	struct tagRbj_set {
		UCHAR Opcode;
		UCHAR data1;
	} Rbj_set;						// 0x5A	// Rbj_set
	struct tagMessage_on {
		UCHAR Opcode;
		UCHAR data1;
		USHORT data2;
		USHORT data4;
	} Message_on;				// 0x5B	// Message_on
	struct tagRain_set {
		UCHAR Opcode;
		UCHAR data1;
	} Rain_set;					// 0x5C	// Rain_set
	struct tagMessage_off {
		UCHAR Opcode;
	} Message_off;				// 0x5D	// Message_off
	struct tagShake_on {
		UCHAR Opcode;
		CHAR data1;
		CHAR data2;
	} Shake_on;					// 0x5E	// Shake_on
	struct tagWeapon_chg {
		UCHAR Opcode;
		UCHAR data1;
	} Weapon_chg;				// 0x5F	// Weapon_chg
	struct tagDoor_model_set {
		UCHAR Opcode;
		UCHAR data1;
		UCHAR data2;
		UCHAR data3;
		UCHAR data4;
		UCHAR data5;
		USHORT data6;
		SHORT data8;
		SHORT dataA;
		SHORT dataC;
		SHORT dataE;
		USHORT data10;
		USHORT data12;
		USHORT data14;
	} Door_model_set;		// 0x60	// Door_model_set
	struct tagDoor_aot_set {
		UCHAR Opcode;		// 0x00 // 0x61
		UCHAR Aot;			// 0x01 // 
		UCHAR SCE;			// 0x02 // 
		UCHAR SAT;			// 0x03 // 
		UCHAR nFloor;		// 0x04 // 
		UCHAR Super;		// 0x05 // 
		SHORT X;			// 0x06 // 
		SHORT Z;			// 0x08 // 
		USHORT W;			// 0x0A // 
		USHORT D;			// 0x0C // 
		SHORT NextPosX;		// 0x0E // 
		SHORT NextPosY;		// 0x10 // 
		SHORT NextPosZ;		// 0x12 // 
		SHORT NextDirY;		// 0x14 // 
		UCHAR NextStage;	// 0x16 // 
		UCHAR NextRoom;		// 0x17 // 
		UCHAR NextCut;		// 0x18 // 
		UCHAR NextnFloor;	// 0x19 // 
		UCHAR DO2;			// 0x1A // 
		UCHAR Animation;	// 0x1B // 
		UCHAR Sound;		// 0x1C // 
		UCHAR KeyId;		// 0x1D // 
		UCHAR KeyType;		// 0x1E // 
		UCHAR Free;			// 0x1F // 
	} Door_aot_set;			// 0x61	// Door_aot_set
	struct tagDoor_aot_set_4p {
		UCHAR Opcode;		// 0x00 // 0x62
		UCHAR Aot;			// 0x01 // Id
		UCHAR SCE;			// 0x02 // Type (0x01)
		UCHAR SAT;			// 0x03 // Atari
		UCHAR nFloor;		// 0x04 // Height
		UCHAR Super;		// 0x05 // Matrix
		SHORT X0, Z0;		// 0x06 // Point #1
		SHORT X1, Z1;		// 0x0A // Point #2
		SHORT X2, Z2;		// 0x0E // Point #3
		SHORT X3, Z3;		// 0x12 // Point #4
		SHORT PosX;			// 0x16 // Player position after entering door
		SHORT PosY;			// 0x18 // Player position after entering door
		SHORT PosZ;			// 0x1A // Player position after entering door
		SHORT DirY;			// 0x1C // Player direction after entering door
		UCHAR Stage;		// 0x1E // Stage after entering door
		UCHAR Room;			// 0x1F // Room after entering door
		UCHAR Cut;			// 0x20 // Camera ID of room after entering door
		UCHAR nFloorNxt;	// 0x21 // 
		UCHAR DO2;			// 0x22 // 
		UCHAR Animation;	// 0x23 // 
		UCHAR Sound;		// 0x24 // 
		UCHAR KeyId;		// 0x25 // 
		UCHAR KeyType;		// 0x26 // 
		UCHAR Free;			// 0x27 // 
	} Door_aot_set_4p;		// 0x62	// Door_aot_set_4p
	struct tagAot_set {
		UCHAR Opcode;				// 0x00 // 0x63
		CHAR Aot;					// 0x01 // 
		UCHAR SCE;					// 0x02 // 
		UCHAR SAT;					// 0x03 // 
		UCHAR nFloor;				// 0x04 // 
		UCHAR Super;				// 0x05 // 
		SHORT X;					// 0x06 // 
		SHORT Z;					// 0x08 // 
		USHORT W;					// 0x0A // 
		USHORT D;					// 0x0C // 
		USHORT Data0;				// 0x0E // 
		USHORT Data1;				// 0x10 // 
		USHORT Data2;				// 0x12 // 
	} Aot_set;						// 0x63	// Aot_set
	struct tagAot_set_4p {
		UCHAR Opcode;			// 0x00 // 0x64
		UCHAR Aot;				// 0x01 // 
		UCHAR SCE;				// 0x02 // 
		UCHAR SAT;				// 0x03 // 
		UCHAR nFloor;			// 0x04 // 
		UCHAR Super;			// 0x05 // 
		SHORT X0;				// 0x06 // 
		SHORT Z0;				// 0x08 // 
		SHORT X1;				// 0x0A // 
		SHORT Z1;				// 0x0C // 
		SHORT X2;				// 0x0E // 
		SHORT Z2;				// 0x10 // 
		SHORT X3;				// 0x12 // 
		SHORT Z3;				// 0x14 // 
		USHORT data0;			// 0x16 // 
		USHORT data1;			// 0x18 // 
		USHORT data2;			// 0x1A // 
	} Aot_set_4p;				// 0x64	// Aot_set_4p
	struct tagAot_reset {
		UCHAR Opcode;
		CHAR data1;
		UCHAR data2;
		UCHAR data3;
		SHORT data4;
		SHORT data6;
		SHORT data8;
	} Aot_reset;					// 0x65	// Aot_reset
	struct tagAot_on {
		UCHAR Opcode;
		UCHAR data1;
	} Aot_on;						// 0x66	// Aot_on
	struct tagItem_aot_set {
		UCHAR Opcode;		// 0x00	// 0x67
		UCHAR Aot;			// 0x01	// Id
		UCHAR SCE;			// 0x02	// Type
		UCHAR SAT;			// 0x03	// Atari
		UCHAR nFloor;		// 0x04	// Height
		UCHAR Super;		// 0x05	// Matrix
		SHORT X;			// 0x06	// Position
		SHORT Z;			// 0x08	// Position
		USHORT W;			// 0x0A	// Size
		USHORT D;			// 0x0C	// Size
		USHORT iItem;		// 0x0E	// Item Id
		USHORT nItem;		// 0x10	// Item Amount
		USHORT Flag;		// 0x12	// Item_flg/2 Bit
		UCHAR MD1;			// 0x14	// MD1 File Id - 0xFF if no MD1
		UCHAR Action;		// 0x15	// Predefined action taken to obtain
	} Item_aot_set;			// 0x67	// Item_aot_set
	struct tagItem_aot_set_4p {
		UCHAR Opcode;		// 0x00 // 0x68
		UCHAR Aot;			// 0x01 // Id
		UCHAR SCE;			// 0x02 // Type (0x02)
		UCHAR SAT;			// 0x03 // Atari
		UCHAR nFloor;		// 0x04 // Height
		UCHAR Super;		// 0x05 // Matrix
		SHORT X0;			// 0x06 // Point #1
		SHORT Z0;			// 0x08 // Point #1
		SHORT X1;			// 0x0A // Point #2
		SHORT Z1;			// 0x0C // Point #2
		SHORT X2;			// 0x0E // Point #3
		SHORT Z2;			// 0x10 // Point #3
		SHORT X3;			// 0x12 // Point #4
		SHORT Z3;			// 0x14 // Point #4
		USHORT iItem;		// 0x16 // Item Id
		USHORT nItem;		// 0x18 // Item Amount
		USHORT Flag;		// 0x1A // Item_flg/2 Bit
		UCHAR MD1;			// 0x1C // MD1 File Id - 0xFF if no MD1
		UCHAR Action;		// 0x1D // Predefined action taken to obtain
	} Item_aot_set_4p;		// 0x68	// Item_aot_set_4p
	struct tagKage_set {
		UCHAR Opcode;
		UCHAR data1;
		CHAR data2;
		UCHAR data3;
		UCHAR data4;
		UCHAR data5;
		USHORT data6;
		USHORT data8;
		USHORT dataA;
		USHORT dataC;
	} Kage_set;					// 0x69	// Kage_set
	struct tagSuper_set {
		UCHAR Opcode;
		UCHAR zAlign;
		UCHAR data2;
		UCHAR data3;
		SHORT data4;
		SHORT data6;
		SHORT data8;
		SHORT dataA;
		SHORT dataC;
		SHORT dataE;
	} Super_set;					// 0x6A	// Super_set
	struct tagKeep_item_ck {
		UCHAR Opcode;
		UCHAR data1;
	} Keep_item_ck;			// 0x6B	// Keep_item_ck
	struct tagKey_ck {
		UCHAR Opcode;
		UCHAR data1;
		USHORT data2;
	} Key_ck;						// 0x6C	// Key_ck
	struct tagTrg_ck {
		UCHAR Opcode;
		UCHAR data1;
		USHORT data2;
	} Trg_ck;						// 0x6D	// Trg_ck
	struct tagScd_id_set {
		UCHAR Opcode;
		UCHAR data1;
		USHORT data2;
	} Scd_id_set;				// 0x6E	// Scd_id_set
	struct tagOm_bomb {
		UCHAR Opcode;
		UCHAR data1;
	} Om_bomb;						// 0x6F	// Om_bomb
	struct tagEspr_on {
		UCHAR Opcode;
		UCHAR data1;
		USHORT data2;
		USHORT data4;
		USHORT data6;
		USHORT data8;
		USHORT dataA;
		USHORT dataC;
		USHORT dataE;
	} Espr_on;						// 0x70	// Espr_on
	struct tagEspr_on2 {
		UCHAR Opcode;
		UCHAR zAlign;
		UCHAR data2;
		UCHAR data3;
		USHORT data4;
		USHORT data6;
		USHORT data8;
		USHORT dataA;
		USHORT dataC;
		USHORT dataE;
		USHORT data10;
	} Espr_on2;					// 0x71	// Espr_on2
	struct tagEspr3d_on {
		UCHAR Opcode;
		UCHAR data1;
		USHORT data2;
		USHORT data4;
		USHORT data6;
		USHORT data8;
		USHORT dataA;
		USHORT dataC;
		USHORT dataE;
		USHORT data10;
		USHORT data12;
		USHORT data14;
	} Espr3d_on;					// 0x72	// Espr3d_on
	struct tagEspr3d_on2 {
		UCHAR Opcode;
		UCHAR zAlign;
		UCHAR data2;
		UCHAR data3;
		USHORT data4;
		USHORT data6;
		USHORT data8;
		USHORT dataA;
		USHORT dataC;
		USHORT dataE;
		USHORT data10;
		USHORT data12;
		USHORT data14;
		USHORT data16;
	} Espr3d_on2;				// 0x73	// Espr3d_on2
	struct tagEspr_kill {
		UCHAR Opcode;
		UCHAR data1;
		UCHAR data2;
		CHAR data3;
		CHAR data4;
	} Espr_kill;					// 0x74	// Espr_kill
	struct tagEspr_kill2 {
		UCHAR Opcode;
		UCHAR data1;
	} Espr_kill2;				// 0x75	// Espr_kill2
	struct tagEspr_kill_all {
		UCHAR Opcode;
		UCHAR data1;
		CHAR data2;
	} Espr_kill_all;			// 0x76	// Espr_kill_all
	struct tagSe_on {
		UCHAR Opcode;
		UCHAR data1;
		SHORT data2;
		SHORT data4;
		SHORT data6;
		SHORT data8;
		SHORT dataA;
	} Se_on;							// 0x77	// Se_on
	struct tagBgm_ctl {
		UCHAR Opcode;
		UCHAR data1;
		UCHAR data2;
		UCHAR data3;
		UCHAR data4;
		UCHAR data5;
	} Bgm_ctl;						// 0x78	// Bgm_ctl
	struct tagXa_on {
		UCHAR Opcode;
		UCHAR data1;
		USHORT data2;
	} Xa_on;							// 0x79	// Xa_on
	struct tagMovie_on {
		UCHAR Opcode;
		UCHAR data1;
	} Movie_on;					// 0x7A	// Movie_on
	struct tagBgm_tbl_set {
		UCHAR Opcode;
		UCHAR zAlign;
		UCHAR data2;
		UCHAR data3;
		USHORT data4;
	} Bgm_tbl_set;				// 0x7B	// Bgm_tbl_set
	struct tagStatus_on {
		UCHAR Opcode;
	} Status_on;					// 0x7C	// Status_on
	struct tagEm_set {
		UCHAR Opcode;
		UCHAR zAlign;
		CHAR data2;
		UCHAR data3;
		USHORT data4;
		USHORT data6;
		UCHAR data8;
		UCHAR data9;
		UCHAR dataA;
		UCHAR dataB;
		USHORT dataC;
		USHORT dataE;
		USHORT data10;
		USHORT data12;
		USHORT data14;
		USHORT data16;
	} Em_set;						// 0x7D	// Em_set
	struct tagMizu_div {
		UCHAR Opcode;
		UCHAR data1;
	} Mizu_div;					// 0x7E	// Mizu_div
	struct tagOm_set {
		UCHAR Opcode;
		UCHAR data1;
		UCHAR data2;
		UCHAR data3;
		USHORT data4;
		USHORT data6;
		UCHAR data8;
		UCHAR data9;
		UCHAR dataA;
		UCHAR dataB;
		USHORT dataC;
		SHORT dataE;
		SHORT data10;
		SHORT data12;
		SHORT data14;
		SHORT data16;
		SHORT data18;
		SHORT data1A;
		SHORT data1C;
		SHORT data1E;
		SHORT data20;
		SHORT data22;
		SHORT data24;
		SHORT data26;
	} Om_set;						// 0x7F	// Om_set
	struct tagPlc_motion {
		UCHAR Opcode;
		UCHAR data1;
		UCHAR data2;
		UCHAR data3;
	} Plc_motion;				// 0x80	// Plc_motion
	struct tagPlc_dest {
		UCHAR Opcode;
		UCHAR zAlign;
		UCHAR data2;
		UCHAR data3;
		USHORT data4;
		USHORT data6;
	} Plc_dest;					// 0x81	// Plc_dest
	struct tagPlc_neck {
		UCHAR Opcode;
		UCHAR data1;
		SHORT data2;
		SHORT data4;
		SHORT data6;
		SHORT data8;
	} Plc_neck;					// 0x82	// Plc_neck
	struct tagPlc_ret {
		UCHAR Opcode;
	} Plc_ret;						// 0x83	// Plc_ret
	struct tagPlc_flg {
		UCHAR Opcode;
		UCHAR data1;
		USHORT data2;
	} Plc_flg;						// 0x84	// Plc_flg
	struct tagPlc_gun {
		UCHAR Opcode;
		UCHAR data1;
	} Plc_gun;						// 0x85	// Plc_gun
	struct tagPlc_gun_eff {
		UCHAR Opcode;
	} Plc_gun_eff;				// 0x86	// Plc_gun_eff
	struct tagPlc_stop {
		UCHAR Opcode;
	} Plc_stop;					// 0x87	// Plc_stop
	struct tagPlc_rot {
		UCHAR Opcode;
		UCHAR data1;
		USHORT data2;
	} Plc_rot;						// 0x88	// Plc_rot
	struct tagPlc_cnt {
		UCHAR Opcode;
		UCHAR data1;
	} Plc_cnt;						// 0x89	// Plc_cnt
	struct tagSplc_ret {
		UCHAR Opcode;
	} Splc_ret;					// 0x8A	// Splc_ret
	struct tagSplc_sce {
		UCHAR Opcode;
	} Splc_sce;					// 0x8B	// Splc_sce
	struct tagPlc_sce {
		UCHAR Opcode;
	} Plc_sce;						// 0x8C	// Plc_sce
	struct tagSpl_weapon_chg {
		UCHAR Opcode;
	} Spl_weapon_chg;		// 0x8D	// Spl_weapon_chg
	struct tagPlc_mot_num {
		UCHAR Opcode;
		UCHAR data1;
		USHORT data2;
	} Plc_mot_num;				// 0x8E	// Plc_mot_num
	struct tagEm_reset {
		UCHAR Opcode;
		UCHAR data1;
	} Em_reset;					// 0x8F	// Em_reset
} Bio3Bytecode;		// Bio Hazard 3 Last Escape
typedef struct tagBio2JumpLabel {
	struct tagGoto {
		UCHAR Opcode;	// 0x00	// 0x17
		UCHAR Ifel_ctr;	// 0x01	// always 0xFF (0x01 on r304-sub05, only)
		UCHAR Loop_ctr;	// 0x02	// always 0xFF (0x00 on r500-sub04 and sub07, only)
		UCHAR zAlign;	// 0x03	// always 0x00
		SHORT Offset;	// 0x04	// Relative Pointer, always references same script
	} Goto;
	ULONG pGoto;		// Absolute pointer of Goto struct
	ULONG pJump;		// Absolute pointer of jump point
} Bio2JumpLabel;	    // Goto statement
typedef struct tagBioScriptScan {
	std::vector <UCHAR> Opcode;		// Opcode Array
	std::vector <ULONG> Pointer;	// Pointer Array
	ULONG Size;						// Script Size (*.scd file)
} BioScriptScan;	    // Complete Initial Scan
#pragma pack(pop)

class Bio_Hazard_2_Script :
	private System_File {
private:
	Bio2Bytecode * Scd;				// Bytecode buffer for Bio Hazard 2 Dual Shock
	Bio2BytecodeT * Trial;			// Bytecode buffer for Bio Hazard 2 Trial Edition
	Bio2BytecodeP * Scd15;			// Bytecode buffer for Bio Hazard 2 Prototype (Nov. 1996)
	Bio2JumpLabel Jump[32];			// Bytecode buffer for Goto statement
	ULONG nJumpLabels;				// Total Goto statement count
	// std::vector <Bio2JumpLabel> Jump;
	BioScriptScan * Scan;
public:

	// Boot
	Bio_Hazard_2_Script(VOID);
	virtual ~Bio_Hazard_2_Script(VOID);

	// Meta
	CHAR * Directory;
	CHAR * NameBase;

	// Flag
	BOOL DebugMode;					// Print helpful statistics for debugging disassembly errors
	BOOL TrialEdition;				// Dis/assembly mode(s) for the Trial Edition
	BOOL PrintNop;					// Nop opcodes will be printed in disassembly

	// Else
	BOOL ElseCk;					// Indication that an else clause is active
	ULONG ElseCnt;					// Amount of active else clauses

	// Print
	ULONG TabCount;					// Text formatting
	BOOL NoTab;						// Disable text formatting
	BOOL NoSemi;					// Disable semi-colon
	BOOL NoRet;						// Disable new line

	// I/O
	ULONG InitScan(_iobuf * BINARY, ULONG _Offset);
	ULONG InitScan(CONST CHAR * _FileName, ...);
	UCHAR ScdRead(_iobuf * BINARY, ULONG _Offset);
	UCHAR ScdPeek(_iobuf * BINARY, ULONG _Offset);

	// If
	ULONG ClausePrint(_iobuf * BINARY, _iobuf * SOURCE, ULONG _Offset, UCHAR OpClause);

	// Goto
	VOID FindJumpLabels(_iobuf * BINARY, ULONG _Offset);
	VOID JumpLabelCk(_iobuf * SOURCE, ULONG _Offset);
	CHAR * GetJumpLabel(ULONG _Offset);

	// Print
	CHAR * GetOnOff(USHORT Flag);
	CHAR * GetAotSet(USHORT AOT);
	CHAR * GetAotSat(USHORT SAT);
	CHAR * GetBgmCtlId(USHORT Id);
	CHAR * GetBgmCtlOp(USHORT Op);
	CHAR * GetBgmCtlType(USHORT Type);
	CHAR * GetCalcOperator(USHORT Operator);
	CHAR * GetCkFlag(USHORT Flag);
	CHAR * GetCmpOperator(USHORT Operator);
	CHAR * GetEmdName(USHORT Id);
	CHAR * GetItemName(USHORT iItem);
	CHAR * GetMemberFlag(USHORT Flag);
	CHAR * GetObjSetId(USHORT Id);
	CHAR * GetObjSetBeFlg(USHORT BeFlg);
	CHAR * GetObjSetAttr(USHORT Attribute);
	CHAR * GetPlcNeck(USHORT Type);
	CHAR * GetSpeedId(USHORT Id);
	CHAR * GetWorkSet(USHORT Type);
	VOID ScdPrint(_iobuf * BINARY, _iobuf * SOURCE, ULONG &_Offset);

	// Disassemble
	ULONG Disassemble(_iobuf * BINARY, _iobuf * SOURCE, ULONG _Offset);
	ULONG Disassemble(CONST CHAR * _FileName, ...);

	// RDT
	ULONG Room(CONST CHAR * _FileName, ...);

	// Prototype
	BOOL ExScdContainer(CONST CHAR * _FileName, ...);
	ULONG InitScanProto(_iobuf * BINARY, ULONG _Offset);
	ULONG InitScanProto(CONST CHAR * _FileName, ...);
	UCHAR GetSceTypeProto(ULONG Value);
	ULONG RoomProto(CONST CHAR * _FileName, ...);
	BOOL UpdatePrototype(CONST CHAR * _FileName, ...);

};