#include "_objInventory.h"

template <class _extendClass>
_objInventory<_extendClass>::_objInventory()
{
	//_classObj = new _extendClass[_size]();
}

template <class _extendClass>
_objInventory<_extendClass>::~_objInventory()
{
}

template<class _extendClass>
void _objInventory<_extendClass>::setUp(textureObj * _texObj, const char * _emptyIconFilePath, unsigned short _MAX_ROW, unsigned short _MAX_COL, float _row_distance, float _col_distance, float gridWidth, float gridHeight, const char * _boarderFilePath, float boarderWidth, float boarderHeight)
{
	Once_setTextureObj(_texObj);
	Once_setClassObjGridEmptyIcon(_emptyIconFilePath);
	Once_setClassObjGrid(_MAX_ROW, _MAX_COL, _row_distance, _col_distance, gridWidth, gridHeight);
	Once_setBoarderID(_boarderFilePath);
	Once_setBoarderSprite(boarderWidth, boarderHeight);
}

template<class _extendClass>
void _objInventory<_extendClass>::Once_setTextureObj(textureObj * _texObj)
{
	texObj = _texObj;
}

template<class _extendClass>
void _objInventory<_extendClass>::Once_setClassObjGridEmptyIcon(const char * _emptyIconFilePath)
{
	emptyClassIconID = texObj->setPNGTextureID(_emptyIconFilePath);
}

template<class _extendClass>
void _objInventory<_extendClass>::Once_setClassObjGrid(unsigned short _MAX_ROW, unsigned short _MAX_COL, float _row_distance, float _col_distance, float gridWidth, float gridHeight)
{
	MAX_CLASS_ROW = _MAX_ROW;
	MAX_CLASS_COL = _MAX_COL;
	MAX_CLASS_SIZE = MAX_CLASS_ROW * MAX_CLASS_COL;

	classObjGrid = new spriteObj[MAX_CLASS_SIZE];

	float temp_x = 0.0f;
	float temp_y = 0.0f;
	for (int colIndex = 0; colIndex < MAX_CLASS_COL; colIndex++) {
		for (int rowIndex = 0; rowIndex < MAX_CLASS_ROW; rowIndex++) {
			classObjGrid[colIndex*MAX_CLASS_ROW + rowIndex].setSprite(temp_x, temp_y, gridWidth, gridHeight, 0.0f, 0.0f, 1.0f, 1.0f);
			temp_x += _row_distance;
		}
		temp_x = 0.0f;
		temp_y -= _col_distance;
	}
}

template<class _extendClass>
void _objInventory<_extendClass>::Once_setBoarderID(const char * _boarderFilePath)
{
	boarderID = texObj->setPNGTextureID(_boarderFilePath);
}

template<class _extendClass>
void _objInventory<_extendClass>::Once_setBoarderSprite(float boarderWidth, float boarderHeight)
{
	boarderSprite[0].setSprite(0.0f, 0.0f, 0.1f, 0.1f, (float)0 / 3, (float)0 / 3, (float)1 / 3, (float)1 / 3);
	boarderSprite[1].setSprite(0.1f, 0.0f, boarderWidth - 0.2f, 0.1f, (float)1 / 3, (float)0 / 3, (float)2 / 3, (float)1 / 3);
	boarderSprite[2].setSprite(boarderWidth - 0.1f, 0.0f, 0.1f, 0.1f, (float)2 / 3, (float)0 / 3, (float)3 / 3, (float)1 / 3);

	boarderSprite[3].setSprite(0.0f, 0.2f - boarderHeight, 0.1f, boarderHeight - 0.2f, (float)0 / 3, (float)1 / 3, (float)1 / 3, (float)2 / 3);
	boarderSprite[4].setSprite(0.1f, 0.2f - boarderHeight, boarderWidth - 0.2f, boarderHeight - 0.2f, (float)1 / 3, (float)1 / 3, (float)2 / 3, (float)2 / 3);
	boarderSprite[5].setSprite(boarderWidth - 0.1f, 0.2f - boarderHeight, 0.1f, boarderHeight - 0.2f, (float)2 / 3, (float)1 / 3, (float)3 / 3, (float)2 / 3);

	boarderSprite[6].setSprite(0.0f, 0.1f - boarderHeight, 0.1f, 0.1f, (float)0 / 3, (float)2 / 3, (float)1 / 3, (float)3 / 3);
	boarderSprite[7].setSprite(0.1f, 0.1f - boarderHeight, boarderWidth - 0.2f, 0.1f, (float)1 / 3, (float)2 / 3, (float)2 / 3, (float)3 / 3);
	boarderSprite[8].setSprite(boarderWidth - 0.1f, 0.1f - boarderHeight, 0.1f, 0.1f, (float)2 / 3, (float)2 / 3, (float)3 / 3, (float)3 / 3);
}

template<class _extendClass>
bool _objInventory<_extendClass>::insertClassObjList(int _index, _extendClass* _obj)
{
	if (_index < 0 || _index >= MAX_CLASS_SIZE)
		return false;
	else if (findClassObjList(_index) == nullptr) {
		std::pair<int, _extendClass*> newItem(_index, _obj);
		_classObjList.insert(newItem);
		return true;
	}
	return false;
}

template<class _extendClass>
bool _objInventory<_extendClass>::insertClassObjListToEmpty(_extendClass* _obj)
{
	for (int i = 0; i < MAX_CLASS_SIZE; i++) {
		if (!findClassObjList(i)) {
			insertClassObjList(i, _obj);
			return true;
		}
	}
	return false;
}

template<class _extendClass>
_extendClass * _objInventory<_extendClass>::findClassObjList(int _index)
{
	if (_classObjList.find(_index) == _classObjList.end())
		return nullptr;
	else
		return *&(_classObjList.find(_index)->second);
}

template<class _extendClass>
bool _objInventory<_extendClass>::eraseClassObjList(int _index)
{
	if (_classObjList.erase(_index) == 1)
		return true;
	else
		return false;
}

template<class _extendClass>
void _objInventory<_extendClass>::displayClassObjList(GLSL * _colorProgram, float _transPosx, float _transPosy)
{
	for (int i = 0; i < MAX_CLASS_SIZE; i++) {
		if (findClassObjList(i)) {
			_colorProgram->enable();
			_colorProgram->setTranslateMatrix(_transPosx, _transPosy, 0.0f);
			texObj->enable(_colorProgram->getUniformLocation("sampler_1"), findClassObjList(i)->getIconID());
			classObjGrid[i].drawSprite();
			texObj->disable();
			_colorProgram->disable();
		}
	}
}

template<class _extendClass>
void _objInventory<_extendClass>::displayClassObjGrid(GLSL * _colorProgram, float _transPosx, float _transPosy)
{
	for (int i = 0; i < MAX_CLASS_SIZE; i++) {
		_colorProgram->enable();
		_colorProgram->setTranslateMatrix(_transPosx, _transPosy, 0.0f);
		texObj->enable(_colorProgram->getUniformLocation("sampler_1"), emptyClassIconID);
		classObjGrid[i].drawSprite();
		texObj->disable();
		_colorProgram->disable();
	}
}

template<class _extendClass>
void _objInventory<_extendClass>::displayClassObjBoarder(GLSL * _colorProgram, float _transPosx, float _transPosy)
{
	for (int i = 0; i < 9; i++) {
		_colorProgram->enable();
		_colorProgram->setTranslateMatrix(_transPosx, _transPosy, 0.0f);
		texObj->enable(_colorProgram->getUniformLocation("sampler_1"), boarderID);
		boarderSprite[i].drawSprite();
		texObj->disable();
		_colorProgram->disable();
	}
}

template<class _extendClass>
void _objInventory<_extendClass>::sortingClassObjList()
{
	std::map<int, _extendClass*> ordered(_classObjList.begin(), _classObjList.end());
	_classObjList.clear();

	int i = 0;
	for (auto it = ordered.begin(); it != ordered.end(); ++it) {
		insertClassObjList(i++, it->second);
	}
}

template<class _extendClass>
int _objInventory<_extendClass>::isCollisionWithGrid(float posx, float posy)
{
	for (int i = 0; i < MAX_CLASS_SIZE; i++) {
		if (posx > classObjGrid[i].getVexPosx() && posx < classObjGrid[i].getVexPosx() + classObjGrid[i].getVexWidth()) {
			if (posy > classObjGrid[i].getVexPosy() && posy < classObjGrid[i].getVexPosy() + classObjGrid[i].getVexHeight()) {
				return i;
			}
		}
	}
	return -1;
}

template <class _extendClass>
void _objInventory<_extendClass>::func1()
{
	printf("Helloworld!");
}

template<class _extendClass>
spriteObj* _objInventory<_extendClass>::getObjGrid(int _index)
{
	if (_index < 0 || _index >= MAX_CLASS_SIZE) {
		return nullptr;
	}
	return &classObjGrid[_index];
}
