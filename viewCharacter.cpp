#include "viewCharacter.h"



viewCharacter::viewCharacter()
{
}


viewCharacter::~viewCharacter()
{
}

void viewCharacter::init(textureObj * _texObj)
{
	currCharacter = nullptr;
	currInventory.setUp(_texObj, "Shader/BlankSpot.png", 10, 3, 0.1f, 0.1f, 0.1f, 0.1f, "Shader/border_sprite1.png", 1.2f, 2.0f);
	characterList.setUp(_texObj, "Shader/BlankSpot_1.png", MAX_CHARACTER_ROW, MAX_CHARACTER_COL, 0.3f, 0.1f, 0.3f, 0.1f, "Shader/border_sprite1.png", 0.5f, 1.6f);
	characterPageUpID = _texObj->setPNGTextureID("Shader/Kenney/PNG/Black/1x/arrowLeft.png");
	characterPageDownID = _texObj->setPNGTextureID("Shader/Kenney/PNG/Black/1x/arrowRight.png");

	movingItem.first = -1;
	movingItem.second = -1;
}

void viewCharacter::updateMouseCord(float mousex, float mousey)
{
	mouseCord.x = mousex;
	mouseCord.y = mousey;
}

void viewCharacter::setTranslateValue(float windowx, float windowy)
{
	translateInvenotory.x = windowx / windowy - 1.1f;
	translateInvenotory.y = -0.4f;
	translateInvenotory.borderx = windowx / windowy - 1.2f;
	translateInvenotory.bordery = 0.9f;

	translateEquipment.x = windowx / windowy - 1.0f;
	translateEquipment.y = 0.7f;
	translateEquipment.borderx = windowx / windowy - 1.1f;
	translateEquipment.bordery = 0.8f;

	translateCharacter.x = windowx / windowy - 1.6f;
	translateCharacter.y = 0.8f;
	translateCharacter.borderx = windowx / windowy - 1.7f;
	translateCharacter.bordery = 0.9f;

	float test = ((float)MAX_CHARACTER_ROW * (float)MAX_CHARACTER_COL * 0.1f);
	characterPageUpSprite.setSprite(windowx / windowy - 1.6f, 0.8f - ((float)MAX_CHARACTER_ROW * (float)MAX_CHARACTER_COL * 0.1f), 0.1f, 0.1f, 0.0f, 0.0f, 1.0f, 1.0f);
	characterPageDownSprite.setSprite(windowx / windowy - 1.4f, 0.8f - ((float)MAX_CHARACTER_ROW * (float)MAX_CHARACTER_COL * 0.1f), 0.1f, 0.1f, 0.0f, 0.0f, 1.0f, 1.0f);
}

void viewCharacter::setFont(gameFont * _gameFont)
{
	displayGameFont = _gameFont;
}

void viewCharacter::setCurrCharacter(int _index)
{
	currCharacter = characterList.findClassObjList(_index);
}

bool viewCharacter::insertItem(int _index, objItem* _item)
{
	return currInventory.insertClassObjList(_index,_item);
}

bool viewCharacter::insertItem(objItem * _item)
{
	return currInventory.insertClassObjListToEmpty(_item);
}

bool viewCharacter::insertEquipment(objItem * _item)
{
	if (currCharacter->getCharacterEquipment()->findClassObjList(_item->getObjType()) == nullptr)
		return currCharacter->getCharacterEquipment()->insertClassObjList(_item->getObjType(), _item);
}

bool viewCharacter::insertCharacter(objCharacter* _character)
{
	if (characterList.insertClassObjListToEmpty(_character)) {
		currCharacter = _character;
		return true;
	}
	return false;
}

bool viewCharacter::eraseItem(int _index)
{
	return currInventory.eraseClassObjList(_index);
}

bool viewCharacter::eraseEquipment(int _index)
{
	return currCharacter->getCharacterEquipment()->eraseClassObjList(_index);
}

bool viewCharacter::eraseCharacter(int _index)
{
	if (characterList.eraseClassObjList(_index)) {
		currCharacter = nullptr;
		return true;
	}
	return false;
}

objItem * viewCharacter::findItem(int _index)
{
	return currInventory.findClassObjList(_index);
}

objItem * viewCharacter::findEquipment(int _index)
{
	return currCharacter->getCharacterEquipment()->findClassObjList(_index);
}

objCharacter* viewCharacter::findCharacter(int _index)
{
	return characterList.findClassObjList(_index);
}

void viewCharacter::moveItemToInventory()
{
	int _movingType = movingItem.first;
	int _movingIndex = movingItem.second;
	int _collisionIndex;
	objItem* Item1;
	objItem* Item2;
	//if the item is in the inventory
	if ((_collisionIndex = isCollisionWithInventory()) >= 0) {
		//if no item found on distination
		if (currInventory.findClassObjList(_collisionIndex) == nullptr) {
			setMovingItem(-1, -1);
			if (_movingType == 0) {
				currInventory.insertClassObjList(
					_collisionIndex,
					currInventory.findClassObjList(_movingIndex)
				);
				currInventory.eraseClassObjList(_movingIndex);
			}
			else if (_movingType == 1) {
				currInventory.insertClassObjList(
					_collisionIndex,
					currCharacter->getCharacterEquipment()->findClassObjList(_movingIndex)
				);
				currCharacter->getCharacterEquipment()->eraseClassObjList(_movingIndex);
			}
		}
		//if item found on distination
		else {
			setMovingItem(-1, -1);

			if (_movingType == 0) {
				Item1 = currInventory.findClassObjList(_movingIndex);
				Item2 = currInventory.findClassObjList(_collisionIndex);

				currInventory.eraseClassObjList(_movingIndex);
				currInventory.eraseClassObjList(_collisionIndex);

				currInventory.insertClassObjList(_collisionIndex, Item1);
				currInventory.insertClassObjList(_movingIndex, Item2);
			}
			else if (_movingType == 1) {
				if (currInventory.findClassObjList(_collisionIndex)->getObjType() == _movingIndex){
					Item1 = currCharacter->getCharacterEquipment()->findClassObjList(_movingIndex);
					Item2 = currInventory.findClassObjList(_collisionIndex);

					currCharacter->getCharacterEquipment()->eraseClassObjList(_movingIndex);
					currInventory.eraseClassObjList(_collisionIndex);

					currInventory.insertClassObjList(_collisionIndex, Item1);
					currCharacter->getCharacterEquipment()->insertClassObjList(_movingIndex, Item2);
				}
			}
		}
	}
}

void viewCharacter::moveItemToEquipment()
{
	int _movingType = movingItem.first;
	int _movingIndex = movingItem.second;
	int _collisionIndex;
	objItem* Item1;
	objItem* Item2;
	if ((_collisionIndex = isCollisionWithEquipment()) >= 0) {
		//if no item found on distination
		if (currCharacter->getCharacterEquipment()->findClassObjList(_collisionIndex) == nullptr) {
			setMovingItem(-1, -1);
			if (_movingType == 0) {
				if (currInventory.findClassObjList(_movingIndex)->getObjType() == _collisionIndex) {
					currCharacter->getCharacterEquipment()->insertClassObjList(
						_collisionIndex,
						currInventory.findClassObjList(_movingIndex)
					);
					currInventory.eraseClassObjList(_movingIndex);
				}
			}
			else if (_movingType == 1) {
			}
		}
		//if item found on distination
		else {
			setMovingItem(-1, -1);
			if (_movingType == 0) {
				Item1 = currInventory.findClassObjList(_movingIndex);
				Item2 = currCharacter->getCharacterEquipment()->findClassObjList(_collisionIndex);

				currInventory.eraseClassObjList(_movingIndex);
				currCharacter->getCharacterEquipment()->eraseClassObjList(_collisionIndex);

				currCharacter->getCharacterEquipment()->insertClassObjList(_collisionIndex, Item1);
				currInventory.insertClassObjList(_movingIndex, Item2);
			}
			else if (_movingType == 1) {
			}
		}
	}
}

int viewCharacter::isCollisionWithInventory()
{
	return currInventory.isCollisionWithGrid(mouseCord.x - translateInvenotory.x, mouseCord.y- translateInvenotory.y);
}

int viewCharacter::isCollisionWithEquipment()
{
	if (currCharacter) {
		return currCharacter->getCharacterEquipment()->isCollisionWithGrid(mouseCord.x - translateEquipment.x, mouseCord.y - translateEquipment.y);
	}
	return -1;
}

int viewCharacter::isCollisionWithCharacter()
{
	return characterList.isCollisionWithGrid(mouseCord.x - translateCharacter.x, mouseCord.y - translateCharacter.y);
}

void viewCharacter::inventorySorting()
{
	currInventory.sortingClassObjList();
}

void viewCharacter::characterSorting()
{
	characterList.sortingClassObjList();
}

void viewCharacter::displayAllObjects(textureObj * _texObj, GLSL * _colorProgram)
{
	currInventory.displayClassObjBoarder(_colorProgram, translateInvenotory.borderx, translateInvenotory.bordery);
	characterList.displayClassObjBoarder(_colorProgram, translateCharacter.borderx, translateCharacter.bordery);

	currInventory.displayClassObjGrid(_colorProgram, translateInvenotory.x, translateInvenotory.y);
	characterList.displayClassObjGrid(_colorProgram, translateCharacter.x, translateCharacter.y);

	currInventory.displayClassObjList(_colorProgram, translateInvenotory.x, translateInvenotory.y);
	characterList.displayClassObjList(_colorProgram, translateCharacter.x, translateCharacter.y);

	if (currCharacter) {
		currCharacter->displayEquipmentBoarder(_colorProgram, translateEquipment.borderx, translateEquipment.bordery);
		currCharacter->displayEquipmentGrid(_colorProgram, translateEquipment.x, translateEquipment.y);
		currCharacter->displayEquipmentList(_colorProgram, translateEquipment.x, translateEquipment.y);
	}

	_colorProgram->enable();
	_colorProgram->setTranslateMatrix(0.0f, 0.0f, 0.0f);
	_texObj->enable(_colorProgram->getUniformLocation("sampler_1"), characterPageUpID);
	characterPageUpSprite.drawSprite();
	_texObj->disable();
	_colorProgram->disable();

	_colorProgram->enable();
	_colorProgram->setTranslateMatrix(0.0f, 0.0f, 0.0f);
	_texObj->enable(_colorProgram->getUniformLocation("sampler_1"), characterPageDownID);
	characterPageDownSprite.drawSprite();
	_texObj->disable();
	_colorProgram->disable();
}

void viewCharacter::setMovingSprite()
{
	movingSprite.setSprite(-0.05f, -0.05f, 0.1f, 0.1f, 0.0f, 0.0f, 1.0f, 1.0f);
}

void viewCharacter::setMovingItem(int _Objtype, int _ObjIndex)
{
	if (movingItem.first == -1) {
		movingItem.first = _Objtype;
		movingItem.second = _ObjIndex;

		if (_Objtype == 0) {
			currInventory.findClassObjList(movingItem.second)->disable();
		}
		else if (_Objtype == 1) {
			currCharacter->getCharacterEquipment()->findClassObjList(movingItem.second)->disable();
		}
	}
	else {
		if (movingItem.first == 0) {
			currInventory.findClassObjList(movingItem.second)->enable();
		}
		else if (movingItem.first == 1) {
			currCharacter->getCharacterEquipment()->findClassObjList(movingItem.second)->enable();
		}
		movingItem.first = _Objtype;
		movingItem.second = _ObjIndex;
	}
}
