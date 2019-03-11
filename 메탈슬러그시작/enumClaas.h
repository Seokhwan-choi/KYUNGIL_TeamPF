#pragma once
// =========================================
// ############ 플레이어 무기 상태 ###########
// =========================================
enum class WEAPON : int
{
	NORMAL, HEAVY, SWORD, GRENADE
};

// =========================================
// ############ 아이템 종류 ###########
// =========================================
enum class ITEM : int {
	HEAVY, GRENADE, FISH, CHICKEN, FRUIT, CRAB, MONKEY
};

// =========================================
// ############ 포로 상태처리 ###########
// =========================================
enum class CAPTIVESTATE {
	R_IDLE, L_IDLE,
	R_MOVE ,L_MOVE,
	R_THANKU, L_THANKU,
	END
};