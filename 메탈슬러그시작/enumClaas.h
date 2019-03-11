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
	FISH, CHICKEN, FRUIT, HEAVY, GRENADE, CRAB
};

// =========================================
// ############ 포로 종류 ###########
// =========================================
enum class CAPTIVE : int {
	TIED, MOVE
};

// =========================================
// ############ 포로 행동 ###########
// =========================================
enum class CAPTIVESTATE : int {
	TIED, UNTIED, WALK, RUN, THANKU, ITEM 
};


