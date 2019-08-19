#include "objTeam.h"



objTeam::objTeam()
{
}


objTeam::~objTeam()
{
}

void objTeam::setUpTeamMember(textureObj * _texObj, const char * _emptyIconFilePath, unsigned short _row, unsigned short _col, float _row_distance, float _col_distance, float gridWidth, float gridHeight, const char * _boarderFilePath, float boarderWidth, float boarderHeight)
{
	texObj = _texObj;
	teamMember.setUp(_texObj, _emptyIconFilePath, _row, _col, _row_distance, _col_distance, gridWidth, gridHeight, _boarderFilePath, boarderWidth, boarderHeight);
}

_objInventory<objCharacter>* objTeam::getTeamMember()
{
	return &teamMember;
}

void objTeam::displayTeamMemberGrid(GLSL * _colorProgram, float _transPosx, float _transPosy)
{
	teamMember.displayClassObjGrid(_colorProgram, _transPosx, _transPosy);
}

void objTeam::displayTeamMemberBoarder(GLSL * _colorProgram, float _transPosx, float _transPosy)
{
	teamMember.displayClassObjBoarder(_colorProgram, _transPosx, _transPosy);
}

void objTeam::displayTeamMemberList(GLSL * _colorProgram, float _transPosx, float _transPosy)
{
	teamMember.displayClassObjList(_colorProgram, _transPosx, _transPosy);
}
