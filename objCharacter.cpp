#include "objCharacter.h"



objCharacter::objCharacter()
{
}


objCharacter::~objCharacter()
{
}

void objCharacter::setUpEquipment(textureObj * _texObj, const char * _emptyEquipmentFilePath, float _row_distance, float _col_distance, float gridWidth, float gridHeight, const char * _boarderFilePath, float boarderWidth, float boarderHeight)
{
	texObj = _texObj;
	characterEquipment.setUp(_texObj, _emptyEquipmentFilePath, 2, 3, _row_distance, _col_distance, gridWidth, gridHeight, _boarderFilePath, boarderWidth, boarderHeight);
	emptyEquipmentIconID[0] = _texObj->setPNGTextureID("Shader/equipment/neck.png");
	emptyEquipmentIconID[1] = _texObj->setPNGTextureID("Shader/equipment/head.png");
	emptyEquipmentIconID[2] = _texObj->setPNGTextureID("Shader/equipment/hands_right.png");
	emptyEquipmentIconID[3] = _texObj->setPNGTextureID("Shader/equipment/chest.png");
	emptyEquipmentIconID[4] = _texObj->setPNGTextureID("Shader/equipment/ring.png");
	emptyEquipmentIconID[5] = _texObj->setPNGTextureID("Shader/equipment/feet.png");
}

_objInventory<objItem>* objCharacter::getCharacterEquipment()
{
	return &characterEquipment;
}

void objCharacter::displayEquipmentGrid(GLSL * _colorProgram, float _transPosx, float _transPosy)
{
	for (int i = 0; i < 6; i++) {
		_colorProgram->enable();
		_colorProgram->setTranslateMatrix(_transPosx, _transPosy, 0.0f);
		texObj->enable(_colorProgram->getUniformLocation("sampler_1"), emptyEquipmentIconID[i]);
		characterEquipment.getObjGrid(i)->drawSprite();
		texObj->disable();
		_colorProgram->disable();
	}
}

void objCharacter::displayEquipmentBoarder(GLSL * _colorProgram, float _transPosx, float _transPosy)
{
	characterEquipment.displayClassObjBoarder(_colorProgram, _transPosx, _transPosy);
}

void objCharacter::displayEquipmentList(GLSL * _colorProgram, float _transPosx, float _transPosy)
{
	characterEquipment.displayClassObjList(_colorProgram, _transPosx, _transPosy);
}
