#pragma once
#include <stdio.h>
#include <unordered_map>
#include "spriteObj.h"
#include "textureObj.h"
#include "GLSL.h"
//#include <iostream>
template <class _extendClass>
class _objInventory
{
private:
	unsigned short MAX_CLASS_ROW;
	unsigned short MAX_CLASS_COL;
	unsigned short MAX_CLASS_SIZE;
	std::unordered_map<int, _extendClass*> _classObjList;

	textureObj* texObj;

	GLuint emptyClassIconID;
	spriteObj* classObjGrid;

	GLuint boarderID;
	spriteObj boarderSprite[9];
public:
	_objInventory();
	~_objInventory();
	void setUp(textureObj* _texObj, const char* _emptyIconFilePath, unsigned short _MAX_ROW, unsigned short _MAX_COL, float _row_distance, float _col_distance, float gridWidth, float gridHeight, const char* _boarderFilePath, float boarderWidth, float boarderHeight);
	void Once_setTextureObj(textureObj* _texObj);
	void Once_setClassObjGridEmptyIcon(const char* _emptyIconFilePath);
	void Once_setClassObjGrid(unsigned short _MAX_ROW, unsigned short _MAX_COL, float _row_distance, float _col_distance, float gridWidth, float gridHeight);
	void Once_setBoarderID(const char* _boarderFilePath);
	void Once_setBoarderSprite(float boarderWidth, float boarderHeight);

	bool insertClassObjList(int _index, _extendClass* _obj);
	bool insertClassObjListToEmpty(_extendClass* _obj);
	_extendClass* findClassObjList(int _index);
	bool eraseClassObjList(int _index);

	void displayClassObjList(GLSL * _colorProgram, float _transPosx, float _transPosy);
	void displayClassObjGrid(GLSL * _colorProgram, float _transPosx, float _transPosy);
	void displayClassObjBoarder(GLSL * _colorProgram, float _transPosx, float _transPosy);

	void sortingClassObjList();

	// !! NOTE !!
	int isCollisionWithGrid(float posx,float posy);

	unsigned short getMaxRow() { return MAX_CLASS_ROW; };
	unsigned short getMaxCol() { return MAX_CLASS_COL; };
	unsigned short getMaxSize() { return MAX_CLASS_SIZE; };
	void func1();

	spriteObj* getObjGrid(int _index);
};


