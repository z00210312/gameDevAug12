#pragma once
#include "objCharacter.h"
#include "gameFont.h"
class viewCharacter
{
private:
	// class variables
	const static int MAX_CHARACTER_ROW = 1;
	const static int MAX_CHARACTER_COL = 10;
	const static int MAX_CHARACTER_PAGE = 3;
	struct TranslateInvenotory {
		float x;
		float y;
		float borderx;
		float bordery;
	}translateInvenotory;
	struct TranslateEquipment {
		float x;
		float y;
		float borderx;
		float bordery;
	}translateEquipment;
	struct TranslateCharacter {
		float x;
		float y;
		float borderx;
		float bordery;
	}translateCharacter;
	struct MouseCord {
		float x;
		float y;
	}mouseCord;

	gameFont* displayGameFont;

	_objInventory<objItem> currInventory;
	_objInventory<objCharacter> characterList;

	objCharacter* currCharacter;
	int currCharacterPage;

	spriteObj movingSprite;
	std::pair<int, int> movingItem;

	float slidingDistance;
	float slidingDistanceDefualt;
	float slidingSpeed;

	GLuint characterPageUpID;
	GLuint characterPageDownID;
	spriteObj characterPageUpSprite;
	spriteObj characterPageDownSprite;
public:
	viewCharacter();
	~viewCharacter();

	// class init
	void init(textureObj* _texObj);

	// class variables functions
	void updateMouseCord(float mousex, float mousey);
	void setTranslateValue(float windowx, float windowy);
	void setFont(gameFont* _gameFont);
	void setCurrCharacter(int _index);

	bool insertItem(int _index, objItem* _item);
	bool insertItem(objItem* _item);
	bool insertEquipment(objItem* _item);
	bool insertCharacter(objCharacter* _character);

	bool eraseItem(int _index);
	bool eraseEquipment(int _index);
	bool eraseCharacter(int _index);

	objItem* findItem(int _index);
	objItem* findEquipment(int _index);
	objCharacter* findCharacter(int _index);

	void moveItemToInventory();
	void moveItemToEquipment();

	int isCollisionWithInventory();
	int isCollisionWithEquipment();
	int isCollisionWithCharacter();

	void inventorySorting();
	void characterSorting();
	void displayAllObjects(textureObj * _texObj, GLSL * _colorProgram);

	void nextCharacterPage();
	void prevCharacterPage();

	void setMovingSprite();
	void setMovingItem(int _Objtype, int _ObjIndex);
};

