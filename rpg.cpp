/* 
Dan's Quest
A Beginners RPG
(c)2002 Daniel Reichert
Written and Coded by Daniel Reichert
Start Date: October 3, 2002
Revision 1.9 - May 18, 2003
*/

// Header files
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
#define NUM_MONSTERS 10

// function declarations
void TitleMenu();
void DisplayStory();
void RunBattle();
void FightBattle();
void GetPlayerName(struct CharStats&);
void PlayerType(struct CharStats&);
void InitArcher(struct CharStats&);
void InitSwords(struct CharStats&);
void InitWizard(struct CharStats&);
void InitWarlock(struct CharStats&);
void ContinueQuest(struct CharStats&);
void SearchArea(struct CharStats&);
void MoveBack(struct CharStats&);
void GamePlay(struct CharStats&);
void DisplayInfo(struct CharStats&);
void InitWeaps(struct CharStats&, struct WeaponStats&, struct WeaponStats&, struct WeaponStats&, struct WeaponStats&, struct WeaponStats&, struct WeaponStats&);
void InitArmor(struct CharStats&, struct ArmorStats&, struct ArmorStats&, struct ArmorStats&, struct ArmorStats&, struct ArmorStats&);
void InitMonsters();

// character information structure
struct CharStats {
    char    name[21], typeclass[21];  // name = player's name, typeclass = the class of the player
    double  health, mana;             // The player's health and mana             
    double  max_health, max_mana;	  // The maximum health and mana
    double	archery, swords, magic;   // Player's skills
	int		armor;					  // Player's armor
    int		gold;                     // Amount of gold
    int		time_passed;              // Amount of turns taken
    int		steps_in, furthest_steps; // Furthest step into the dungeon and current location
    bool	con_game;                 // TRUE to continue
    int		str, intel, dext;         // Player's attributes
    int		level;                    // Player's level
    int		monster_kills;            // Amount of monsters killed
};
    CharStats player;				  // creates the player

// weapon information structure
struct WeaponStats {
	char   WeapName[21];
	char   WeapType[7];
    bool   TwoHanded;
	double power;
	int    mana_change;
	int    hp_change;
	int    str_change;
	int    dext_change;
	int    intel_change;
	double archery_change, swords_change, magic_change;
};

//  WeaponStats instances
	WeaponStats fists;         
    WeaponStats long_sword;     
    WeaponStats dagger;
    WeaponStats katana;
    WeaponStats axe;
    WeaponStats spear;
	WeaponStats bow;


// armor information structure
struct ArmorStats {
	char   ArmorName[21];
	char   ArmorType[7];
	int    defense_change;
	int    mana_change;
	int    hp_change;
	int    str_change;
	int    dext_change;
	int    intel_change;
	double archery_change, swords_change, magic_change;
};
   
//  ArmorStats instances
    ArmorStats helmet;
    ArmorStats torso;
    ArmorStats arms;
    ArmorStats gloves;
    ArmorStats legs;



// monster information structure
struct Monster{
    char      MonsterName[21];
    int       hp;
    int       power;
    int       loot;
    double    skill_gain;
};
    
Monster stats[NUM_MONSTERS];
enum {orc, skeleton, ghost, giant_spider, daemon, zombie, dragon, king_cobra, vampire, evil_npc};
void InitMonsters()
{    
	strcpy(stats[orc].MonsterName, "Orc");    
	stats[orc].hp = 200;
    stats[orc].power = 10;
    stats[orc].loot = rand()%20 + 10;
    stats[orc].skill_gain = .025;

	strcpy(stats[skeleton].MonsterName, "Skeleton");
	stats[skeleton].hp = 150;
	stats[skeleton].power = 9;
	stats[skeleton].loot = rand()%10 + 10;
	stats[skeleton].skill_gain = .015;

	strcpy(stats[ghost].MonsterName, "Ghost");
	stats[ghost].hp = 250;
	stats[ghost].power = 15;
	stats[ghost].loot = rand()%35 + 9;
	stats[ghost].skill_gain = .021;

	strcpy(stats[giant_spider].MonsterName, "Giant Spider");
	stats[giant_spider].hp = 100;
	stats[giant_spider].power = 5;
	stats[giant_spider].loot = rand()%10 + 1;
	stats[giant_spider].skill_gain = .005;

	strcpy(stats[daemon].MonsterName, "Daemon");
	stats[daemon].hp = 700;
	stats[daemon].power = 55;
	stats[daemon].loot = rand()%50 + 500;
	stats[daemon].skill_gain = .05;

	strcpy(stats[zombie].MonsterName, "Zombie");
	stats[zombie].hp = 210;
	stats[zombie].power = 11;
	stats[zombie].loot = rand()%5 + 10;
	stats[zombie].skill_gain = .019;

	strcpy(stats[dragon].MonsterName, "Dragon");
	stats[dragon].hp = 800;
	stats[dragon].power = 65;
	stats[dragon].loot = rand()%50 + 600;
	stats[dragon].skill_gain = .06;

	strcpy(stats[king_cobra].MonsterName, "King Cobra");
	stats[king_cobra].hp = 350;
	stats[king_cobra].power = 30;
	stats[king_cobra].loot = rand()%20 + 30;
	stats[king_cobra].skill_gain = .04;

	strcpy(stats[vampire].MonsterName, "Vampire");
	stats[vampire].hp = 400;
	stats[vampire].power = 35;
	stats[vampire].loot = rand()%20 + 40;
	stats[vampire].skill_gain = .045;

	strcpy(stats[evil_npc].MonsterName, "Evil NPC");
	stats[evil_npc].hp = 300;
	stats[evil_npc].power = 25;
	stats[evil_npc].loot = rand()%20 + 20;
	stats[evil_npc].skill_gain = .028;
    }


// main function
int main()
{       
    srand(time(0));     
     
    TitleMenu();
    GetPlayerName(player);
    PlayerType(player);
    InitMonsters(/*player, orc, skeleton, ghost, giant_spider, daemon, zombie, dragon, king_cobra, vampire, evil_npc*/);
    DisplayStory();
    
    do
    {
        GamePlay(player);
    }while(player.con_game != 0);

    return 0;
}

// initializes all of the weapons
void InitWeaps(struct CharStats& player, struct WeaponStats& fists, struct WeaponStats& long_sword, struct WeaponStats& dagger, struct WeaponStats& katana, struct WeaponStats& axe, struct WeaponStats& spear, struct WeaponStats& bow)
{
    strcpy(fists.WeapName, "Fists");    // tells the name of the weapon
    strcpy(fists.WeapType, "fists");    // tells the type of weapon (fists, weap, shield)
    fists.TwoHanded = 0;                // two handed?
    fists.power = player.str * .25;     // the amount of damage it will cause
    fists.mana_change = 0;              // the amount of mana it will add (magical)
    fists.hp_change = 0;                // the amount of hp it will add (magical)
    fists.str_change = 0;               // the amount of str it will add (magical)
    fists.dext_change = 0;              // the amount of dext it will add (magical and determines faster weapons)
    fists.intel_change = 0;             // the amount of intel. it will add (magical)
    fists.archery_change = 0;           // the amount of archery it will add (magical)
    fists.swords_change = 0;            // the amount of swordsmanship it will add (magical)
    fists.magic_change = 0;             // the amount of magic it will add (magical)

    strcpy(long_sword.WeapName, "Long Sword");
    strcpy(long_sword.WeapType, "weap");
    long_sword.TwoHanded = 0;
    long_sword.power = (player.str * .25) + 5;
    long_sword.mana_change = 0;
    long_sword.hp_change = 0;
    long_sword.str_change = 0;
    long_sword.dext_change = 0;
    long_sword.intel_change = 0;
    long_sword.archery_change = 0;
    long_sword.swords_change = 0;
    long_sword.magic_change = 0;
    
    strcpy(dagger.WeapName, "Dagger");
    strcpy(dagger.WeapType, "weap");
    dagger.TwoHanded = 0;
    dagger.power = (player.str * .25) + 1;
    dagger.mana_change = 0;
    dagger.hp_change = 0;
    dagger.str_change = 0;
    dagger.dext_change = 0;
    dagger.intel_change = 0;
    dagger.archery_change = 0;
    dagger.swords_change = 0;
    dagger.magic_change = 0;
    
    strcpy(katana.WeapName, "Katana");
    strcpy(katana.WeapType, "weap");
    katana.TwoHanded = 0;
    katana.power = (player.str * .25) + 4;
    katana.mana_change = 0;
    katana.hp_change = 0;
    katana.str_change = 0;
    katana.dext_change = 1;
    katana.intel_change = 0;
    katana.archery_change = 0;
    katana.swords_change = 0;
    katana.magic_change = 0;    
    
    strcpy(axe.WeapName, "Axe");
    strcpy(axe.WeapType, "weap");
    axe.TwoHanded = 1;
    axe.power = (player.str * .25) + 8;
    axe.mana_change = 0;
    axe.hp_change = 0;
    axe.str_change = 0;
    axe.dext_change = -1;
    axe.intel_change = 0;
    axe.archery_change = 0;
    axe.swords_change = 0;
    axe.magic_change = 0;

    strcpy(spear.WeapName, "Spear");
    strcpy(spear.WeapType, "weap");
    spear.TwoHanded = 1;
    spear.power = (player.str * .25) + 6;
    spear.mana_change = 0;
    spear.hp_change = 0;
    spear.str_change = 0;
    spear.dext_change = 1;
    spear.intel_change = 0;
    spear.archery_change = 0;
    spear.swords_change = 0;
    spear.magic_change = 0;

	strcpy(bow.WeapName, "Bow");
    strcpy(bow.WeapType, "weap");
    bow.TwoHanded = 1;
    bow.power = (player.dext * .25) + 15;
    bow.mana_change = 0;
    bow.hp_change = 0;
    bow.str_change = 0;
    bow.dext_change = 0;
    bow.intel_change = 0;
    bow.archery_change = 0;
    bow.swords_change = 0;
    bow.magic_change = 0;


    
}

// initializes all of the armor
void InitArmor(struct CharStats& player, struct ArmorStats &helmet, struct ArmorStats &torso, struct ArmorStats &arms, struct ArmorStats &gloves, struct ArmorStats &legs)
{
    strcpy(helmet.ArmorName, "Helmet");
	strcpy(helmet.ArmorType, "helm");
	helmet.defense_change = 5;
	helmet.mana_change = 0;
	helmet.hp_change = 0;
	helmet.str_change = 0;
	helmet.dext_change = 0;
	helmet.intel_change = 0;
	helmet.archery_change = 0;
	helmet.swords_change = 0;
	helmet.magic_change = 0;

	strcpy(torso.ArmorName, "Chest Armor");
	strcpy(torso.ArmorType, "torso");
	torso.defense_change = 10;
	torso.mana_change = 0;
	torso.hp_change = 0;
	torso.str_change = 0;
	torso.dext_change = 0;
	torso.intel_change = 0;
	torso.archery_change = 0;
	torso.swords_change = 0;
	torso.magic_change = 0;

	strcpy(arms.ArmorName, "Arm Armor");
	strcpy(arms.ArmorType, "arms");
	arms.defense_change = 5;
	arms.mana_change = 0;
	arms.hp_change = 0;
	arms.str_change = 0;
	arms.dext_change = 0;
	arms.intel_change = 0;
	arms.archery_change = 0;
	arms.swords_change = 0;
	arms.magic_change = 0;

	strcpy(legs.ArmorName, "Leg Armor");
	strcpy(legs.ArmorType, "legs");
	legs.defense_change = 5;
	legs.mana_change = 0;
	legs.hp_change = 0;
	legs.str_change = 0;
	legs.dext_change = 0;
	legs.intel_change = 0;
	legs.archery_change = 0;
	legs.swords_change = 0;
	legs.magic_change = 0;

	strcpy(gloves.ArmorName, "Gloves");
	strcpy(gloves.ArmorType, "gloves");
	gloves.defense_change = 3;
	gloves.mana_change = 0;
	gloves.hp_change = 0;
	gloves.str_change = 0;
	gloves.dext_change = 0;
	gloves.intel_change = 0;
	gloves.archery_change = 0;
	gloves.swords_change = 0;
	gloves.magic_change = 0;


}


// Initializes a new swordsman
void InitSwords(struct CharStats &player)
{
    player.gold = 0;
    player.time_passed = 0;
    player.steps_in = 0;
    player.furthest_steps = 0;
    player.con_game = 1;
    player.archery = 10;
    player.swords = 100;
    player.magic = 0;
	player.armor = 0;
    player.str = 80;
    player.intel = 10;
    player.dext = 20;
    player.level = 1;
    player.monster_kills = 0;
    player.max_health = (player.str + player.dext) * 1.5;
    player.max_mana = player.intel * 1.25;
    player.mana = 12.5;
    player.health = 150;
}

// Initializes a new archer
void InitArcher(struct CharStats &player)
{
    player.gold = 0;
    player.time_passed = 0;
    player.steps_in = 0;
    player.furthest_steps = 0;
    player.con_game = 1;
    player.archery = 100;
    player.swords = 10;
    player.magic = 0;
	player.armor = 0;
    player.str = 50;
    player.intel = 10;
    player.dext = 50;
    player.level = 1;
    player.monster_kills = 0;
    player.max_health = (player.str + player.dext) * 1.5;
    player.max_mana = player.intel * 1.25;
    player.mana = 12.5;
    player.health = 150;
}

// Initializes a new wizard
void InitWizard(struct CharStats &player)
{
    player.gold = 0;
    player.time_passed = 0;
    player.steps_in = 0;
    player.furthest_steps = 0;
    player.con_game = 1;
    player.archery = 0;
    player.swords = 0;
    player.magic = 100;
	player.armor = 0;
    player.str = 30;
    player.intel =80;
    player.dext = 10;
    player.level = 1;
    player.monster_kills = 0;
    player.max_health = (player.str + player.dext) * 1.5;
    player.max_mana = player.intel * 1.25;
    player.mana = 100;
    player.health = 60;
}

// Initializes a new warlock
void InitWarlock(struct CharStats &player)
{
    player.gold = 0;
    player.time_passed = 0;
    player.steps_in = 0;
    player.furthest_steps = 0;
    player.con_game = 1;
    player.archery = 27.5;
    player.swords = 27.5;
    player.magic = 55;
	player.armor = 0;
    player.str = 25;
    player.intel = 60;
    player.dext = 25;
    player.level = 1;
    player.monster_kills = 0;
    player.max_health = (player.str + player.dext) * 1.5;
    player.max_mana = player.intel * 1.25;
    player.health = 75;
    player.mana = 60;
}

/* This function receives from the player what he wants to do.  It calls either 
   the SearchArea() function to do some hunting, the ContinueQuest() function 
   to move further in, the MoveBack() function to move back, the DisplayInfo() 
   function to display the players info, or quit to end the game.*/

void GamePlay(struct CharStats &player)
{
        int choice;
        char YesNo;
        do{
                cout << "\n\t\tWhat would you like to do?" << endl;
                cout << "\t\t1. Proceed onward." << endl;
                cout << "\t\t2. Move back." << endl;
                cout << "\t\t3. Search the general vacinity." << endl;
                cout << "\t\t4. Display Status." << endl;
                cout << "\t\t5. Quit." << endl;
                cout << "\nYour Selection:\t";                
                cin >> choice;
       
                switch(choice)
                {
                                case 1:
                                ContinueQuest(player);
                                player.time_passed++;
                                DisplayInfo(player);                                
                                break;
                
                                case 2:
                                if(player.steps_in > 0)
                                {
                                      MoveBack(player);
                                      player.time_passed++;
                                      DisplayInfo(player);
                                }
                                else
                                {     
                                      system("CLS");
                                      cout << "\nYou must be at least 1 step in the cave to back.  Otherwise, you will leave the cave!\n";
                                      cout << "Are you sure you want to finish your adventure? (Y)es / (N)o \n";
                                      cin >> YesNo;
                                      if (YesNo == 'Y' || YesNo == 'y')
                                      {
                                            player.con_game = 0;
                                            player.time_passed++;
                                      }
                                      else if (YesNo == 'N' || YesNo == 'n')
                                            player.con_game = 1;
                                      else
                                            choice = 5;
                                      DisplayInfo(player);
                                }
                                break;
                
                                case 3:
                                if(player.steps_in > 0)
                                {
                                      SearchArea(player);
                                      player.time_passed++;
                                }
                                else
                                {
                                      system("CLS"); 
                                      cout << "\nYou must be at least 1 step in the cave to perform a search of the area!\n\n";
                                      system("PAUSE");
                                      system("CLS");
                                }
                                DisplayInfo(player);
                                break;
                                
                                case 4:
                                DisplayInfo(player);
                                break;
                                
                                case 5:
                                player.con_game = 0;
                                DisplayInfo(player);
                                break;
                                
                                default:
                                break;
                }
                
        }while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5);
                       
}

/* Player searches the area and will randomley fight a monster, pick up gold, 
   run into a trap, or find nothing.*/
void SearchArea(struct CharStats &player)
{
    int random_event, random_gold, random_trap;
    int random_trapdmg;
    random_trap = rand()%16+1;
    random_event = rand()%14;
    random_gold = rand()%11+1;
    if(random_event >= 0 && random_event <= 2)
    {
        cout << "monster attack\n";
        system("PAUSE");
        system("CLS");
    }
    
    else if (random_event >= 3 && random_event <= 4)
    {
        if(random_trap >= 0 && random_trap <= 7)
        {
                random_trapdmg = rand()%4+1;
                cout << "\nYou received " << random_trapdmg << " damage from a rock trap!\n" << endl;
                player.health -= random_trapdmg;
        }
        else if(random_trap >=8 && random_trap <= 14)
        {
                random_trapdmg = rand()%5+5;
                cout << "\nYou received " << random_trapdmg << " damage from an arrow trap!\n" << endl;
                player.health -= random_trapdmg;
        }
        else if(random_trap >= 15 && random_trap <= 17)
        {
                random_trapdmg = rand()%5+10;
                cout << "\nYou received " << random_trapdmg << " damage from a swinging axe trap!\n" << endl;
                player.health -= random_trapdmg;
        }
                
                
        system("PAUSE");
        system("CLS");
    }

    else if (random_event >= 5 && random_event <=  7)
    {
        player.gold += random_gold;
        cout << "\nYou found " << random_gold << " gold pieces on the the floor.\n" << endl;
        system("PAUSE");
        system("CLS");
    }
    
    else if (random_event >= 8 && random_event <=  14)
    {
        cout << "\nYou find nothing";
        int maybe_move = rand()%2;
        if(player.steps_in > 0)
        {
                if(maybe_move == 1)
                {
                                cout << ", but while in the process of searching, you move back 1 space.\n" << endl;
                                player.steps_in--;
                }
                else
                                cout << ".\n" << endl;
        }
        else 
                cout << ".\n" << endl;
                
        system("PAUSE");
        system("CLS");
    }
}

/* Player moves further into the cave.  He can fight a monster, pick up gold, run into a trap, 
   or find nothing at all.  He will move forward a number of steps depending on the action. */
void ContinueQuest(struct CharStats &player)
{
    int random_event, random_gold, random_trap;
    int random_trapdmg;
    random_event = rand()%14;
    random_gold = rand()%19+3;
    random_trap = rand()%16+1;
    if(random_event >= 0 && random_event <= 4)
    {
        cout << "monster attack\n";
        FightBattle();
        system("PAUSE");
        system("CLS");
    }
    
    else if (random_event >= 5 && random_event <= 7)
    {
        cout << '\n';
        if(random_trap >= 0 && random_trap <= 10)
        {
                random_trapdmg = rand()%4+1;
                cout << "You received " << random_trapdmg << " damage from a rock trap!" << endl;
                player.health -= random_trapdmg;
        }
        else if(random_trap >=11 && random_trap <= 15)
        {
                random_trapdmg = rand()%5+5;
                cout << "You received " << random_trapdmg << " damage from an arrow trap!" << endl;
                player.health -= random_trapdmg;
        }
        else if(random_trap >= 16 && random_trap <= 17)
        {
                random_trapdmg = rand()%5+10;
                cout << "You received " << random_trapdmg << " damage from a swinging axe trap!" << endl;
                player.health -= random_trapdmg;
        }
                
        cout << "You continue on 1 space.\n" << endl;
        player.steps_in += 1;
        
        system("PAUSE");
        system("CLS");
    }
    
    else if (random_event >= 8 && random_event <=  10)
    {
        player.gold += random_gold;
        cout << "\nYou find " << random_gold << " gold pieces on the the floor." << endl;
        
        cout << "You continue on 2 spaces.\n" << endl;
        player.steps_in += 2;
        
        system("PAUSE");
        system("CLS");
    }
    
    else if (random_event >= 11 && random_event <=  14)
    {
        cout << "\nYou continue on 2 spaces without finding anything.\n" << endl;
        player.steps_in += 2;
        system("PAUSE");
        system("CLS");
    }
}       

/* Player moves further out to the opening of the cave.  He can fight a monster, run into a trap, 
  or find nothing at all.  He will always move backward 1 step.  */
void MoveBack(struct CharStats &player)
{
    int random_event, random_gold;
    random_event = rand()%14;
    random_gold = rand()%9;
    if(random_event >= 0 && random_event <= 3)
    {
        cout << "monster attack\n";
        cout << "You move back 1 space." << endl;
        
        player.steps_in -= 1;
        system("PAUSE");
        system("CLS");
    }
    
    else if (random_event == 4)
    {
        cout << "run into trap\n";
        cout << "You move back 1 space." << endl;
        player.steps_in -= 1;
        system("PAUSE");
        system("CLS");
    }
    
    else if (random_event >= 5 && random_event <= 7)
    {
        player.gold += random_gold;
        cout << "\nYou find " << random_gold << " gold pieces on the the floor." << endl;
        cout << "You move back 1 space.\n" << endl;
        player.steps_in -= 1;
        system("PAUSE");
        system("CLS");
    }
    
    else if (random_event >= 8 && random_event <=  14)
    {
        cout << "\nYou move back 1 space without finding anything.\n" << endl;
        player.steps_in -= 1;
        system("PAUSE");
        system("CLS");
    }
}   

/* Player runs from a battle.  He will drop a small random amount of gold, lose 10 steps from 
   the furtherst spot he has gone to, and will lose 1 from the total number of monsters killed. */
void RunBattle() 
{
    cout << "RunBattle() function" << endl;
    system("PAUSE");
    system("CLS");
}

/* Player chooses to go into battle.  He will gain a random amount of gold, he will move forward 
   10 steps, and he will add 1 to the total number of monsters killed. */
void FightBattle()
{
    int temp = rand()%player.level;
	Monster m = stats[rand()%NUM_MONSTERS];
	m.hp += (player.level * .25) + temp;
	m.loot += temp * 1.5;
	m.power += temp * 1.1;
	m.skill_gain += temp * .1;
    cout << m.MonsterName << '\n' << m.hp << '\n' << m.power << '\n' << m.loot << '\n' << m.skill_gain << '\n';


    system("PAUSE");
    system("CLS");
}

// Shows all of the stats, attributes, skills, etc of the character
void DisplayInfo(struct CharStats &player)
{
    if(player.steps_in >= player.furthest_steps)
    {
        player.furthest_steps = player.steps_in;
    }
    if(player.archery > player.swords && player.archery > player.magic)
        strcpy(player.typeclass, "Archer");
    else if (player.swords > player.archery && player.swords > player.magic)
        strcpy(player.typeclass, "Swordsman");
    else if (player.magic > player.archery && player.magic > player.swords)
        strcpy(player.typeclass, "Magician");
    
    system("CLS");
    cout << "\n****Status for " << player.name << ", level " << player.level << " " << player.typeclass << "****\n" << endl;
    cout << "Health:\t\t\t" << player.health << '/' << player.max_health << endl;
    cout << "Mana:\t\t\t" << player.mana << '/' << player.max_mana << endl;
    cout << "Gold:\t\t\t" << player.gold << endl;
    cout << "Monsters Killed:\t" << player.monster_kills << endl;
    cout << "Time Passed:\t\t" << player.time_passed << endl;
    cout << "Current Steps In:\t" << player.steps_in << endl;
    cout << "Furtherst Step In:\t" << player.furthest_steps << endl;
    cout << "\n**Skills:\n";
    cout << "Archery:\t\t" << player.archery << endl;
    cout << "Swords:\t\t\t" << player.swords << endl;
    cout << "Magic:\t\t\t" << player.magic << endl;
    cout << "\n**Attributes:\n";
    cout << "Strength:\t\t" << player.str << endl;
    cout << "Dexterity:\t\t" << player.dext << endl;
    cout << "Intelligence:\t\t" << player.intel << endl << endl;

    system("PAUSE");
    system("CLS");

}

void GetPlayerName(struct CharStats &player) // This function gets the players name 
{
    cout << "\nEnter your name (Max 20 characters): ";
    cin.getline(player.name, 21);
}

// Determines the class of the player which will call the initilization of the stats
void PlayerType(struct CharStats &player)
{
    int choice, choice2;
    do{
        system("CLS");
        cout << "\n***Class Selection***\n";
        cout << "1. Warrior\n";
        cout << "2. Mage\n";
        cout << "Select your class: ";
        cin >> choice;
        switch(choice)
        {
                case 1:
                      system("CLS");
                      cout << "\n***Warrior Selection***\n";
                      cout << "1. Archer\n";
                      cout << "2. Swordsman\n";
                      cout << "Select the type of warrior: ";
                      cin >> choice2;
                      switch(choice2)
                      {
                             case 1:
                             InitArcher(player);
                             break;
                                                   
                             case 2:
                             InitSwords(player);
                             break;
                             
                             default:
                             choice = 5;
                             break;
                      }
                      break;                
                case 2:
                      system("CLS");
                      cout << "\n***Mage Selection***\n";
                      cout << "1. Wizard\n";
                      cout << "2. Warlock\n";
                      cout << "Select the type of mage: ";
                      cin >> choice2;
                      switch(choice2)
                      {                
                             case 1:
                             InitWizard(player);
                             break;
                      
                             case 2:
                             InitWarlock(player);
                             break;
                             
                             default:
                             choice = 5;
                             break;
                      }
                      break;
        }
    }while (choice != 1 && choice != 2);
}

/*  Everything past this point is simply functions with no passing.  This includes
    the stories, titles, etc.  No data is manipulated beyond this point! */


void TitleMenu() // This function displays the title screen for the game 
{
    system("CLS");
    cout << "\n\t\t************************************************" << endl;
    cout << "\t\t*                                              *" << endl;
    cout << "\t\t*                                              *" << endl;
    cout << "\t\t*               Dan's Quest                *" << endl;
    cout << "\t\t*             A Beginners C++ RPG              *" << endl;
    cout << "\t\t*           (c)2002 Daniel Reichert            *" << endl;
    cout << "\t\t*                                              *" << endl;
    cout << "\t\t*     Written and Coded by Daniel Reichert     *" << endl;
    cout << "\t\t*                                              *" << endl;
    cout << "\t\t*                                              *" << endl;
    cout << "\t\t************************************************" << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    system("PAUSE");
    system("CLS");
}
    
void DisplayStory() // Displays the story
{
    system("CLS");
    cout << "\n\tYou enter the dark cave talked about for ages." << endl;
    cout << "So the story goes, you will be known as a legend in the books " << endl;
    cout << "should you be able to survive.  In this quest, you will only become" << endl;
    cout << "a legend only if you acheive a higher score than the previous" << endl;
    cout << "adventurers.  This is done by slaying monsters, collecting gold, " << endl;
    cout << "and surviving.  The longer you spend in the cave, the higher your " << endl;
    cout << "score will be." << endl;
    cout << "\n\tYou must be warned though!  This is NOT an easy task!  Much evil" << endl;
    cout << "has been seen lurking throughout the cave.  Evil such as giant" << endl;
    cout << "insects, walking skeletons, zombies, ape men, and other such" << endl;
    cout << "gruesome creatures await to tear you to shreds as soon as possible."  << endl;
    cout << "\n\n";
    system("PAUSE");
    system("CLS");
    cout << "\n\tAlthough your senses tell you to go back, you know it will be an" << endl;
    cout << "adventure that will make you a hero to all.  You decide to" << endl;
    cout << "proceed, hoping you will make it out alive..." << endl;
    cout << "\n\n";
    system("PAUSE");
    system("CLS");
} 



