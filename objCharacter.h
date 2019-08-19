#pragma once
#include "objItem.h"
#include "_objInventory.h"
#include "_objInventory.cpp"
class objCharacter:public objComponent
{
private:
	_objInventory<objItem> characterEquipment;
	GLuint emptyEquipmentIconID[6];
	textureObj* texObj;
public:
	objCharacter();
	~objCharacter();
	void setUpEquipment(textureObj* _texObj, const char* _emptyIconFilePath, float _row_distance, float _col_distance, float gridWidth, float gridHeight, const char* _boarderFilePath, float boarderWidth, float boarderHeight);

	_objInventory<objItem>* getCharacterEquipment();
	void displayEquipmentGrid(GLSL * _colorProgram, float _transPosx, float _transPosy);
	void displayEquipmentBoarder(GLSL * _colorProgram, float _transPosx, float _transPosy);
	void displayEquipmentList(GLSL * _colorProgram, float _transPosx, float _transPosy);
};

