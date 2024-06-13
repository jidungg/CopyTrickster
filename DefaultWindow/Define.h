#pragma once

#define			PURE	= 0

#define			WINCX	800
#define			WINCY	600

#define			OBJ_NOEVENT			0
#define			OBJ_DEAD			1

#define			PI					3.141592f
#define			VK_MAX				0xff

#define			TILECX  32
#define			TILECY  32

#define			SLOT_CX 27	
#define			SLOT_CY 27
#define			SKILL_SLOT_CX 27
#define			SKILL_SLOT_CY 27

#define			MAGENTA RGB(255, 0, 255)

#define			UP_RAD (-PI / 4 * 2)
#define			DOWN_RAD (PI / 4 * 2)
#define			LU_RAD (-PI / 4 * 3)
#define			LD_RAD (PI / 4 * 3)
#define			RU_RAD (-PI / 4 * 1)
#define			RD_RAD (PI / 4 * 1)
#define			RIGHT_RAD (PI / 4 * 0)
#define			LEFT_RAD (PI / 4 * 4)

#define			DOUBLE_CLICK_TIME 500 
#define			ILLUST_X 306
#define			ILLUST_Y 306
#define			NPC_BALLOON_X 304
#define			NPC_BALLOON_Y 262
#define			SEC(x) 1000*(x)

template<typename T>
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

enum DIRECTION
{
	DIR_UP, 
	DIR_LU,
	DIR_LEFT,
	DIR_LD,
	DIR_DOWN,
	DIR_RD,
	DIR_RIGHT,
	DIR_RU,
	DIR_END
};

enum OBJ_ID
{
	OBJ_PLAYER,
	OBJ_MONSTER,
	OBJ_NPC,
	OBJ_PORTAL,
	OBJ_ITEM,
	OBJ_P_BULLET,
	OBJ_M_BULLET,
	OBJ_ENV,
	OBJ_END
};

enum RENDERID
{
	RENDER_PORTAL,
	RENDER_BULLET,
	RENDER_GAMEOBJECT,
	RENDER_END
};
enum class EVENT_TYPE
{
	DAMAGE,
	RECOVER,
	HIT,
	DEAD,
	END
};
enum class UI_TYPE
{
	WINDOW,
	BUTTON,
	ICON,
	TEXT,
	SLOT,
	END
};
enum class WINDOW_ID
{
	SKILL,
	INVENTORY,
	QUEST,
	EQUIP,  
	END
};
enum class BUTTON_STATE { NORMAL, HOVER, PRESSED, END };
enum class SCENE_ID
{
	INTRO,
	TOWN,
	MAGMA,
	ROAD,
	RYTHM,
	END
};
enum class NPC_ID
{
	MAID,
	MONSTER_GIRL,
	END
};
enum class MONSTER_ID
{
	MUMMY,
	ARMORED_DRAGON,
	OCTOPUS,
	UNARMORED_DRAGON,
	END
};
enum class ANIM_TYPE
{
	EIGHT_DIR,
	FOUR_DIR,
	TWO_DIR,
	ONE_DIR,
	END
};
enum class EFFECT_ID
{
	NORMAL_HIT,
	CROSS_EXPLODE,
	SHOCK_WAVE,
	THUNDER,
	ELECTRIC_SHOCK,
	BIG_EXPLODE,
	ENERGY_PUNCH,

	PLAYER_DAMAGE_COUNT,
	PLAYER_DAMAGE_COUNT_CRITICAL,
	MONSTER_DAMAGE_COUNT,
	HP_RECOVER_COUNT,
	MP_RECOVER_COUNT,
	PLAYER_CRITICAL,
	PLAYER_MISS,
	PLAYER_DAMAGE_COUNT_CRITICAL_BACK,
	MONSTER_CIRTICAL,
	MONSTER_MISS,

	END
};
enum class SKILL_ID
{
	BASIC_ATTACK,
	ENERGY_PUNCH,
	THUNDER_PUNCH,
	TRIPLE_PUNCH,
	CROSS_BOMB,
	LAVA_ERUPTION,
	END
};
enum CHANNELID
{
	SOUND_EFFECT,
	SOUND_DRILL,
	SOUND_BGM,
	SOUND_CLICK,
	SOUND_UI,
	SOUND_CHIDORI,
	SOUND_RASENGAN,
	MAXCHANNEL

};

enum class ITEM_TYPE
{
	EQUIP,
	CONSUMABLE,
	ETC,
	END
};
enum class EQUIP_TYPE
{
	WEAPON,
	SHIELD,
	HAT,
	EAR,
	DRILL,
	END
};
enum class ITEM_ID
{
	DAGGER,
	SWORD,
	TURTLE_BACK,
	SHIELD,
	HAT,
	HELMET,
	BUNNY_EAR,
	DRILL,

	PINK_POTION,
	BLUE_POTION,
	CRAB_FLESH,
	STAR_CANDY,
	OCTO_LEG,

	LAPIS,
	SCALES,
	SPOON,
	VINIL,
	SHOVEL,
	STONE,
	STICKER,
	DRAGON_EGG,
	END
};
enum class SLOT_TYPE
{
	INVEN,
	EQUIP,
	SKILL,
	QUICK,
	END
};
enum class QUEST_TYPE
{
	MONSTER,
	ITEM,
	END
};
enum class QUEST_ID
{
	MAID_01,
	MAID_02,
	MONSTER_01,
	MONSTER_02,
	END
};
enum class CONV_OPTION_TYPE
{
	BYE,
	QUEST,
	STORE,
	ACCEPT,
	COMPLETE,
	END
};
enum class CURSOR_STATE
{
	UI, ATTACK, SKILL, DOOR,NORMAL, GRAB, TALK, QUEST, DRILL, BLOCKED, END
};
enum class COMMON_STATE {IDLE,MOVE,BATTLE, BASIC_ATTACK,CRITICAL_ATTACK, STRONG_ATTACK, HIT, DODGE,DRILL, DEAD, END};
enum class PLAYER_STATE { IDLE, WALK, RUN, BATTLE, CRITICAL_ATTACK, NORMAL_ATTACK, SNAP_ATTACK,CHARGE_ATTACK ,DRILL, HIT, DODGE, DEAD,GROOMING, ST_END };
enum class DRAGON_STATE { IDLE, WALK, ATTACK, BREAK, ST_END };
enum class UNARMORED_DRAGON_STATE { IDLE, WALK, ATTACK,  DEAD, ST_END };
enum class MONSTER_STATE { IDLE, WALK, ATTACK, HIT, DEAD, ST_END };
typedef struct tagInfo
{
	float	fX;		// 중점 X
	float	fY;		// 중점 Y

	float	fRX;	// 가로 렌더 사이즈
	float	fRY;	// 세로 렌더 사이즈
	float	fCX;	// 가로 충돌 사이즈
	float	fCY;	// 세로 충돌 사이즈

}INFO;

typedef	struct tagLinePoint
{
	float	fX;
	float	fY;

	tagLinePoint() { ZeroMemory(this, sizeof(tagLinePoint)); }
	tagLinePoint(float _fX, float _fY) : fX(_fX), fY(_fY){}

}LINEPOINT;

typedef	struct tagLine
{
	tagLinePoint		tLeft;
	tagLinePoint		tRight;

	tagLine() { ZeroMemory(this, sizeof(tagLine)); }
	tagLine(tagLinePoint& _tLeft, tagLinePoint& _tRight) : tLeft(_tLeft), tRight(_tRight) {}

}LINE;

typedef struct tagFrame
{
	bool    Is_Frame_End()
	{
		return iFrameStart > iFrameEnd;
	}
	TCHAR* pFrameKey;
	int		iFrameStart;		// 어디에서부터 시작(인덱스)
	int		iFrameEnd;			// 어디까지(끝 인덱스)
	int		iMotion;			// 어떤 모션
	DWORD	dwSpeed;			// 스프라이트 속도
	DWORD	dwTime =0;				// 스프라이트 전환 시간	
	bool	bRepeat = true;			// 반복 여부
	bool    bMotionCancelable = true;
	vector<int>* vecFuncFrame;
	int			iCurFuncIdx = 0;
}FRAME;
typedef struct tagAnimationData
{
	FRAME tFrame;
	bool	bRepeat = true;			// 반복 여부
}ANIM_DATA;

struct DeleteObj
{
	template<typename T>
	void operator()(T& Temp)
	{
		if (Temp)
		{
			delete Temp;
			Temp = nullptr;
		}
	}

};

struct DeleteMap
{
	template<typename T>
	void operator()(T& Temp)
	{
		if (Temp.second)
		{
			delete Temp.second;
			Temp.second = nullptr;
		}
	}

};
typedef struct tagCharacterStat
{
	float	_fAttackRange = 0;
	int		_iAttak = 0;
	int		_iDefense = 0;
	int		_iMagicAttack = 0;
	int     _iHP = 0;
	int     _iMaxHP = 0;
	int		_iMP = 0;
	int     _iMaxMP = 0;
	float	_fSpeed = 0;
	int		_iCritChance = 0;
	float   _fCritMultiplier = 0;
	int		_iDodgeChance = 0;
	DWORD	_dwAttackDelay = 0;
}STAT;


typedef struct tagCharacterData
{
	~tagCharacterData() { 
		Safe_Delete(vecAnimData); 
	}
	STAT tStat;
	INFO tInfo;
	vector<pair<ANIM_TYPE,FRAME>>* vecAnimData;
	int	iRenderOffsetX = 0;
	int	iRenderOffsetY = 0;
	int m_eID;
	TCHAR* pName;
}CHARACTER_DATA;
typedef struct tagNPCData : public tagCharacterData
{
	wstring strConversation;
	list<QUEST_ID> QuestList;
	list<ITEM_ID> StoreItems;
	HDC hNPCLiustDC;
}NPC_DATA;
typedef struct tagEffectData
{
	EFFECT_ID eID;
	int iRX;
	int iRY;
	int	iRenderOffsetX = 0;
	int	iRenderOffsetY = 0;
	HDC hMemDC;
	FRAME tFrame;
}EFFECT_DATA;
typedef struct tagOptionData
{
	CONV_OPTION_TYPE eOptType;
	QUEST_ID eQuestID = QUEST_ID::END;
	wstring strText;
}OPTION;
typedef struct EnvObjData
{
	HDC hDC;
	int iRX;
	int iRY;
	int iROffX;
	int iROffY;


	EnvObjData(const HDC& hDC, int iRX, int iRY, int iROffX, int iROffY)
		: hDC(hDC), iRX(iRX), iRY(iRY), iROffX(iROffX), iROffY(iROffY)
	{
	}
}ENV_DATA;

extern HWND g_hWnd;
extern DWORD g_dwTime;
extern bool g_bEditMode;