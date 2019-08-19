#pragma once
#include "objCharacter.h"
class objTeam:public objComponent
{
private:
	_objInventory<objCharacter> teamMember;
	textureObj* texObj;
public:
	objTeam();
	~objTeam();

	void setUpTeamMember(textureObj* _texObj, const char* _emptyIconFilePath, unsigned short _row, unsigned short _col, float _row_distance, float _col_distance, float gridWidth, float gridHeight, const char* _boarderFilePath, float boarderWidth, float boarderHeight);

	_objInventory<objCharacter>* getTeamMember();
	void displayTeamMemberGrid(GLSL * _colorProgram, float _transPosx, float _transPosy);
	void displayTeamMemberBoarder(GLSL * _colorProgram, float _transPosx, float _transPosy);
	void displayTeamMemberList(GLSL * _colorProgram, float _transPosx, float _transPosy);
};

