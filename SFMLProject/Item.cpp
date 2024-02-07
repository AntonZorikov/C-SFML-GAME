#include <iostream>
#include <math.h>
#include <fstream> 

using namespace std;

class Item {
public:
	string tag = "none", description = "", name = "", PropertiesDescription = "";
	int id;
	int AddHP = 0, MaxHPAdd = 0, MinDMG = 0, MaxDMG = 0, ShieldDMG = 0, ShieldMagicDMG = 0, Shield = 0, MagicShield = 0, AttackDistance = 1, Rarity = 0, Effect = 0, EffectTime = 0;
	float AttackSpeed = 0;
	void ItemFunction(int ItemId) {
		ResetToZero();
		
		switch (ItemId)
		{
			case -3: {
				tag = "plpotion";
				description = "";
				name = "Sense of Life Potion";
				Rarity = 0;
				Effect = 3;
				break;
			}
			case -2: {
				tag = "plpotion";
				description = "Fills your mind with knoeledge";
				name = "Knowledge Potion";
				Rarity = 0;
				Effect = 2;
				break;
			}
			case -1: {
				tag = "plpotion";
				description = "It heals";
				name = "Healing Potion";
				Rarity = 0;
				Effect = 1;
				break;
			}
			case 0: {
				tag = "none";
				description = "none";
				name = "";
				Rarity = 0;
				break;
			}
			case 1: {
				tag = "weapon";
				description = "It is a very small sword. You like this sword. You are not going to throw it away, are you?\n";
				name = "Small Sword";
				MinDMG = 3;
				MaxDMG = 5;
				ShieldDMG = 2;
				AttackSpeed = 1;
				PropertiesDescription = "DMG = 4-7, ShieldDMG = 2, AttackSpeed = 0.5";
				Rarity = 0;
				break;
			}
			case 2: {
				tag = "weapon";
				description = "A small but sharp dagger, probably good for cutting cheese with.\n";
				name = "Dagger";
				MinDMG = 2;
				MaxDMG = 4;
				ShieldDMG = 1;
				AttackSpeed = 0.4f;
				PropertiesDescription = "DMG = 2-4, ShieldDMG = 1, AttackSpeed = 0.4";
				Rarity = 0;
				break;
			}
			case 3: {
				tag = "weapon";
				description = "Old rusty sword but heavy.\n";
				name = "Rusted Sword";
				MinDMG = 5;
				MaxDMG = 8;
				ShieldDMG = 3;
				AttackSpeed = 2;
				PropertiesDescription = "DMG = 6-10, ShieldDMG = 3, AttackSpeed = 2";
				Rarity = 0;
				break;
			}
			case 4: {
				tag = "weapon";
				description = "The staff is made of wood with strange luminous blue letters\n";
				name = "Runic Staff";
				MinDMG = 2;
				MaxDMG = 5;
				ShieldDMG = 2;
				ShieldMagicDMG = 1;
				AttackSpeed = 1;
				PropertiesDescription = "DMG = 2-7, ShieldDMG = 2, ShieldMagicDMG = 1, AttackSpeed = 1";
				Rarity = 1;
				break;
			}
			case 5: {
				tag = "weapon";
				description = "A whip made of suspicious leather...\n";
				name = "Leather Whip";
				MinDMG = 2;
				MaxDMG = 5;
				ShieldDMG = 0;
				AttackSpeed = 1;
				AttackDistance = 3;
				PropertiesDescription = "DMG = 2-6, ShieldDMG = 0, AttackSpeed = 1, AttackDistance = 3";
				Rarity = 2;
				break;
			}
			case 6: {
				tag = "weapon";
				description = "A steel saber with a black scabbard and a silver hilt is quite light\n";
				name = "Sabre";
				MinDMG = 4;
				MaxDMG = 7;
				ShieldDMG = 1;
				AttackSpeed = 0.5f;
				PropertiesDescription = "DMG = 4-8, ShieldDMG = 1, AttackSpeed = 0.5";
				Rarity = 2;
				break;
			}
			case 7: {
				tag = "weapon";
				description = "It is hard to call it a spear, rather a long sharpned stick\n";
				name = "Wood Spear";
				MinDMG = 3;
				MaxDMG = 7;
				ShieldDMG = 1;
				AttackSpeed = 1.3f;
				AttackDistance = 2;
				PropertiesDescription = "DMG = 3-8, ShieldDMG = 2, AttackSpeed = 1.3, AttackDistance = 2";
				Rarity = 0;
				break;
			}
			case 8: {
				tag = "weapon";
				description = "A long scarlet saber with a serrated blade, the sight of it makes you afraid \n and tempted to cut yourself. Inflicts a bleeding effects on the enemy.\n";
				name = "Bloody Sabre";
				MinDMG = 4;
				MaxDMG = 10;
				ShieldDMG = 2;
				AttackSpeed = 0.7f;
				PropertiesDescription = "DMG = 4-14, ShieldDMG = 2, AttackSpeed = 0.7, ";
				Rarity = 3;
				Effect = 1;
				break;
			}

			default: {
				break;
			}
		}
	}
	void ResetToZero() {
		id = 0;
		AddHP = 0;
		MaxHPAdd = 0;
		MinDMG = 0;
		MaxDMG = 0;
		ShieldDMG = 0;
		ShieldMagicDMG = 0;
		Shield = 0;
		MagicShield = 0;
		AttackSpeed = 0;
		AttackDistance = 1;
		Rarity = 0;
		Effect = 0;
		EffectTime = 0;
	}
};