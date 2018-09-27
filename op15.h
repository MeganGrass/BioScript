#pragma once

ULONG Bio_Hazard_2_Proto_Script_Bytecode_Size[0x6A] = {
	{ sizeof(tagBio2BytecodeP::tagNop) },				// 0x00	// Nop
	{ sizeof(tagBio2BytecodeP::tagEvt_end) },			// 0x01	// Evt_end
	{ sizeof(tagBio2BytecodeP::tagEvt_next) },			// 0x02	// Evt_next
	{ sizeof(tagBio2BytecodeP::tagEvt_chain) },			// 0x03	// Evt_chain
	{ sizeof(tagBio2BytecodeP::tagEvt_exec) },			// 0x04	// Evt_exec
	{ sizeof(tagBio2BytecodeP::tagEvt_kill) },			// 0x05	// Evt_kill
	{ sizeof(tagBio2BytecodeP::tagIfel_ck) },			// 0x06	// Ifel_ck
	{ sizeof(tagBio2BytecodeP::tagElse_ck) },			// 0x07	// Else_ck
	{ sizeof(tagBio2BytecodeP::tagEndif) },				// 0x08	// Endif
	{ sizeof(tagBio2BytecodeP::tagSleep) },				// 0x09	// Sleep
	{ sizeof(tagBio2BytecodeP::tagSleeping) },			// 0x0A	// Sleeping
	{ sizeof(tagBio2BytecodeP::tagWsleep) },			// 0x0B	// Wsleep
	{ sizeof(tagBio2BytecodeP::tagWsleeping) },			// 0x0C	// Wsleeping
	{ sizeof(tagBio2BytecodeP::tagFor) },				// 0x0D	// For
	{ sizeof(tagBio2BytecodeP::tagNext) },				// 0x0E	// Next
	{ sizeof(tagBio2BytecodeP::tagWhile) },				// 0x0F	// While
	{ sizeof(tagBio2BytecodeP::tagEwhile) },			// 0x10	// Ewhile
	{ sizeof(tagBio2BytecodeP::tagDo) },				// 0x11	// Do
	{ sizeof(tagBio2BytecodeP::tagEdwhile) },			// 0x12	// Edwhile
	{ sizeof(tagBio2BytecodeP::tagSwitch) },			// 0x13	// Switch
	{ sizeof(tagBio2BytecodeP::tagCase) },				// 0x14	// Case
	{ sizeof(tagBio2BytecodeP::tagDefault) },			// 0x15	// Default
	{ sizeof(tagBio2BytecodeP::tagEswitch) },			// 0x16	// Eswitch
	{ sizeof(tagBio2BytecodeP::tagGoto) },				// 0x17	// Goto
	{ sizeof(tagBio2BytecodeP::tagGosub) },				// 0x18	// Gosub
	{ sizeof(tagBio2BytecodeP::tagReturn) },			// 0x19	// Return
	{ sizeof(tagBio2BytecodeP::tagBreak) },				// 0x1A	// Break
	{ sizeof(tagBio2BytecodeP::tagFor2) },				// 0x1B	// For2
	{ sizeof(tagBio2BytecodeP::tagBreak_point) },		// 0x1C	// Break_point
	{ sizeof(tagBio2BytecodeP::tagOpcode1D) },			// 0x1D	// Nop
	{ sizeof(tagBio2BytecodeP::tagOpcode1E) },			// 0x1E	// Nop
	{ sizeof(tagBio2BytecodeP::tagOpcode1F) },			// 0x1F	// Nop
	{ sizeof(tagBio2BytecodeP::tagOpcode20) },			// 0x20	// Nop
	{ sizeof(tagBio2BytecodeP::tagCk) },				// 0x21 // Ck
	{ sizeof(tagBio2BytecodeP::tagSet) },				// 0x22	// Set
	{ sizeof(tagBio2BytecodeP::tagCmp) },				// 0x23	// Cmp
	{ sizeof(tagBio2BytecodeP::tagSave) },				// 0x24	// Save
	{ sizeof(tagBio2BytecodeP::tagCopy) },				// 0x25	// Copy
	{ sizeof(tagBio2BytecodeP::tagCalc) },				// 0x26	// Calc
	{ sizeof(tagBio2BytecodeP::tagCalc2) },				// 0x27	// Calc2
	{ sizeof(tagBio2BytecodeP::tagSce_rnd) },			// 0x28	// Sce_rnd
	{ sizeof(tagBio2BytecodeP::tagCut_chg) },			// 0x29	// Cut_chg
	{ sizeof(tagBio2BytecodeP::tagCut_old) },			// 0x2A	// Cut_old
	{ sizeof(tagBio2BytecodeP::tagMessage_on) },		// 0x2B	// Message_on
	{ sizeof(tagBio2BytecodeP::tagAot_set) },			// 0x2C	// Aot_set				// if(SAT & 0x80) = 0
//	{ sizeof(tagBio2BytecodeP::tagAot_set_4p) },		// 0x2C	// Aot_set_4p			// if(SAT & 0x80) = 1
	{ sizeof(tagBio2BytecodeP::tagObj_model_set) },		// 0x2D	// Obj_model_set
	{ sizeof(tagBio2BytecodeP::tagWork_set) },			// 0x2E	// Work_set
	{ sizeof(tagBio2BytecodeP::tagSpeed_set) },			// 0x2F	// Speed_set
	{ sizeof(tagBio2BytecodeP::tagAdd_speed) },			// 0x30	// Add_speed
	{ sizeof(tagBio2BytecodeP::tagAdd_aspeed) },		// 0x31	// Add_aspeed
	{ sizeof(tagBio2BytecodeP::tagPos_set) },			// 0x32	// Pos_set
	{ sizeof(tagBio2BytecodeP::tagDir_set) },			// 0x33	// Dir_set
	{ sizeof(tagBio2BytecodeP::tagMember_set) },		// 0x34	// Member_set
	{ sizeof(tagBio2BytecodeP::tagMember_set2) },		// 0x35	// Member_set2
	{ sizeof(tagBio2BytecodeP::tagSe_on) },				// 0x36	// Se_on
	{ sizeof(tagBio2BytecodeP::tagSca_id_set) },		// 0x37	// Sca_id_set
	{ sizeof(tagBio2BytecodeP::tagSca_xzwd_set) },		// 0x38	// Sca_xzwd_set
	{ sizeof(tagBio2BytecodeP::tagSca_type_set) },		// 0x39	// Sca_type_set
	{ sizeof(tagBio2BytecodeP::tagSce_espr_on) },		// 0x3A	// Sce_espr_on
	{ sizeof(tagBio2BytecodeP::tagDoor_aot_set) },		// 0x3B	// Door_aot_set			// if(SAT & 0x80) = 0	// WIP
//	{ sizeof(tagBio2BytecodeP::tagDoor_aot_set_4p) },	// 0x3B	// Door_aot_set_4p		// if(SAT & 0x80) = 1	// WIP
	{ sizeof(tagBio2BytecodeP::tagCut_auto) },			// 0x3C	// Cut_auto
	{ sizeof(tagBio2BytecodeP::tagMember_copy) },		// 0x3D	// Member_copy
	{ sizeof(tagBio2BytecodeP::tagMember_cmp) },		// 0x3E	// Member_cmp
	{ sizeof(tagBio2BytecodeP::tagPlc_motion) },		// 0x3F	// Plc_motion
	{ sizeof(tagBio2BytecodeP::tagPlc_dest) },			// 0x40	// Plc_dest
	{ sizeof(tagBio2BytecodeP::tagPlc_neck) },			// 0x41	// Plc_neck
	{ sizeof(tagBio2BytecodeP::tagPlc_ret) },			// 0x42	// Plc_ret
	{ sizeof(tagBio2BytecodeP::tagPlc_flg) },			// 0x43	// Plc_flg
	{ sizeof(tagBio2BytecodeP::tagSce_em_set) },		// 0x44	// Sce_em_set
	{ sizeof(tagBio2BytecodeP::tagOpcode45) },			// 0x45	// UNKNOWN OPCODE
	{ sizeof(tagBio2BytecodeP::tagAot_reset) },			// 0x46	// Aot_reset
	{ sizeof(tagBio2BytecodeP::tagAot_on) },			// 0x47	// Aot_on
	{ sizeof(tagBio2BytecodeP::tagSuper_set) },			// 0x48	// Super_set
	{ sizeof(tagBio2BytecodeP::tagSuper_reset) },		// 0x49	// Super_reset
	{ sizeof(tagBio2BytecodeP::tagPlc_gun) },			// 0x4A	// Plc_gun
	{ sizeof(tagBio2BytecodeP::tagCut_replace) },		// 0x4B	// Cut_replace
	{ sizeof(tagBio2BytecodeP::tagOpcode4C) },			// 0x4C	// UNKNOWN OPCODE
	{ sizeof(tagBio2BytecodeP::tagOpcode4D) },			// 0x4D	// UNKNOWN OPCODE
	{ sizeof(tagBio2BytecodeP::tagSce_espr_kill) },		// 0x4E	// Sce_espr_kill
	{ sizeof(tagBio2BytecodeP::tagDoor_model_set) },	// 0x4F	// Door_model_set
	{ sizeof(tagBio2BytecodeP::tagItem_aot_set) },		// 0x50	// Item_aot_set			// if(SAT & 0x80) = 0
//	{ sizeof(tagBio2BytecodeP::tagItem_aot_set_4p) },	// 0x50	// Item_aot_set_4p		// if(SAT & 0x80) = 1
	{ sizeof(tagBio2BytecodeP::tagSce_key_ck) },		// 0x51	// Sce_key_ck
	{ sizeof(tagBio2BytecodeP::tagSce_trg_ck) },		// 0x52	// Sce_trg_ck
	{ sizeof(tagBio2BytecodeP::tagWork_set2) },			// 0x53	// Work_set2
	{ sizeof(tagBio2BytecodeP::tagSce_bgm_control) },	// 0x54	// Sce_bgm_control
	{ sizeof(tagBio2BytecodeP::tagSce_espr_control) },	// 0x55	// Sce_espr_control
	{ sizeof(tagBio2BytecodeP::tagSce_fade_set) },		// 0x56	// Sce_fade_set
	{ sizeof(tagBio2BytecodeP::tagSce_fade_adjust) },	// 0x57	// Sce_fade_adjust
	{ sizeof(tagBio2BytecodeP::tagCk2) },				// 0x58	// Ck2
	{ sizeof(tagBio2BytecodeP::tagSet2) },				// 0x59	// Set2
	{ sizeof(tagBio2BytecodeP::tagMember_calc) },		// 0x5A	// Member_calc
	{ sizeof(tagBio2BytecodeP::tagMember_calc2) },		// 0x5B	// Member_calc2
	{ sizeof(tagBio2BytecodeP::tagSce_bgmtbl_set) },	// 0x5C	// Sce_bgmtbl_set
	{ sizeof(tagBio2BytecodeP::tagPlc_rot) },			// 0x5D	// Plc_rot
	{ sizeof(tagBio2BytecodeP::tagXa_on) },				// 0x5E	// Xa_on
	{ sizeof(tagBio2BytecodeP::tagNop) },				// 0x5F	// Nop
	{ sizeof(tagBio2BytecodeP::tagNop) },				// 0x60	// Nop
	{ sizeof(tagBio2BytecodeP::tagNop) },				// 0x61	// Nop
	{ sizeof(tagBio2BytecodeP::tagNop) },				// 0x62	// Nop
	{ sizeof(tagBio2BytecodeP::tagNop) },				// 0x63	// Nop
	{ sizeof(tagBio2BytecodeP::tagNop) },				// 0x64	// Nop
	{ sizeof(tagBio2BytecodeP::tagNop) },				// 0x65	// Nop
	{ sizeof(tagBio2BytecodeP::tagNop) },				// 0x66	// Nop
	{ sizeof(tagBio2BytecodeP::tagAot_set_4p) },		// 0x67	// Aot_set_4p
	{ sizeof(tagBio2BytecodeP::tagDoor_aot_set_4p) },	// 0x68	// Door_aot_set_4p
	{ sizeof(tagBio2BytecodeP::tagItem_aot_set_4p) }	// 0x69	// Item_aot_set_4p
};