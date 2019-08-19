#include "objComponent.h"

void objComponent::init(textureObj* _texObj, const char* _spriteIconFilePath, const char* _spritePortraitFilePath)
{
	texObj = _texObj;
	m_spriteIconID = texObj->setPNGTextureID(_spriteIconFilePath);
	m_spritePortraitID = texObj->setPNGTextureID(_spritePortraitFilePath);
	m_isInUse = true;
	m_ObjID = 0;
	m_ObjType = 0;
}

void objComponent::Once_setSpriteIconID(textureObj * _texObj, const char * _filePath)
{
	m_spriteIconID = texObj->setPNGTextureID(_filePath);
}

void objComponent::Once_setSpritePortraitID(textureObj * _texObj, const char * _filePath)
{
	m_spritePortraitID = texObj->setPNGTextureID(_filePath);
}

void objComponent::Once_setSpriteIcon(float posx, float posy, float posWidth, float posHeight, float u, float v, float uvWidth, float uvHeight)
{
	m_spriteIcon.setSprite(posx, posy, posWidth, posHeight, u, v, uvWidth, uvHeight);
}

void objComponent::Once_setSpritePortrait(float posx, float posy, float posWidth, float posHeight, float u, float v, float uvWidth, float uvHeight)
{
	m_spritePortrait.setSprite(posx, posy, posWidth, posHeight, u, v, uvWidth, uvHeight);
}

void objComponent::Once_drawSpriteIcon()
{
	m_spriteIcon.drawSprite();
}

void objComponent::Once_drawSpritePortrait()
{
	m_spritePortrait.drawSprite();
}

void objComponent::setSpriteIconUV(float u, float v, float uvWidth, float uvHeight)
{
	m_spriteIcon.setSpriteUV(u, v, uvWidth, uvHeight);
}

void objComponent::setSpriteProtraitUV(float u, float v, float uvWidth, float uvHeight)
{
	m_spritePortrait.setSpriteUV(u, v, uvWidth, uvHeight);
}
