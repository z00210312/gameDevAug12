#include "gameWindow.h"
//#define WaitPullMode 0;

gameWindow::gameWindow(const char *title, int &width, int &height)
{
	_DefaultColorProgram = new GLSL();
	m_texObj = new textureObj();

	// window variables
	m_title = title;
	m_width = width;
	m_height = height;

	// openGL variables
	init();
	glClearColor(0.5, 0.5f, 0.5, 1.0f);
	glViewport(0, 0, m_width, m_height);
	glfwPollEvents();
	glfwSwapBuffers(m_window);

	// game variables
	newState = loading;

	lastTime = 0.0;
	CurrentSpritesLocation_x = 0.0f;
	CurrentSpritesLocation_y = 0.0f;
	light_pos_z = -1.0f;

	testScaleValue = 1.0f;
	testDegree = 0.0f;

	// GLSL
	_DefaultColorProgram->setGLSL("Shader/newShader.vert", "Shader/newShader.frag", "Shader/newShader.attr");

	setMainScene();
	setCrusor();

	// finish loading 
	newState = mainScene;
	MenuSprites[0].setSprite((float)-width / height + 0.1f, 0.7f, 0.6f, 0.2f, 0.0f, (float)0 / 3, 1.0f, (float)1 / 3);
	MenuSprites[1].setSprite((float)-width / height + 0.1f, 0.5f, 0.6f, 0.2f, 0.0f, (float)1 / 3, 1.0f, (float)2 / 3);
	MenuSprites[2].setSprite((float)-width / height + 0.1f, 0.3f, 0.6f, 0.2f, 0.0f, (float)2 / 3, 1.0f, (float)3 / 3);
	MenuTexture = m_texObj->setPNGTextureID("Shader/gameMenu.png");

	/////////////////
	// game variables
	/////////////////

	// init
	newClassTest.setUp(m_texObj, "Shader/BlankSpot.png", 10, 3, 0.1f, 0.1f, 0.1f, 0.1f, "Shader/border_sprite1.png", 1.2f, 2.0f);
	// setUP
	newItem0.init(m_texObj, "Shader/ring_1/ring_7.png", "Shader/ring_1/ring_1.png");
	newItem0.Once_setSpriteIcon(0.0f, 0.0f, 0.1f, 0.1f, 0.0f, 0.0f, 1.0f, 1.0f);
	newItem0.setObjType(4);

	newItem1.init(m_texObj, "Shader/ring_1/ring_5.png", "Shader/ring_1/ring_5.png");
	newItem1.Once_setSpriteIcon(0.0f, 0.0f, 0.1f, 0.1f, 0.0f, 0.0f, 1.0f, 1.0f);
	newItem1.setObjType(4);
	// add items
	//newClassTest.insertClassObjList(3,&newItem0);
	//newClassTest.sortingClassObjList();
	// add characters
	newCharacter.setUpEquipment(m_texObj, "Shader/BlankSpot.png", 0.2f, 0.1f, 0.1f, 0.1f, "Shader/border_sprite1.png", 0.5f, 0.5f);
	//newCharacter.getCharacterEquipment()->insertClassObjList(3, &newItem0);
	newCharacter.init(m_texObj, "Shader/J. W. Bjerk/frame-6-royal.png", "Shader/J. W. Bjerk/frame-6-royal.png");
	// !! NOTED: display play the grid sprite instead of actual sprite
	//newCharacter.Once_setSpriteIcon(0.0f, 0.0f, 0.3f, 0.1f, 0.0f, 0.0f, 1.0f, 2.0f);
	newCharacter2.setUpEquipment(m_texObj, "Shader/BlankSpot.png", 0.2f, 0.1f, 0.1f, 0.1f, "Shader/border_sprite1.png", 0.5f, 0.5f);
	newCharacter2.init(m_texObj, "Shader/J. W. Bjerk/frame-2-orange.png", "Shader/J. W. Bjerk/frame-6-royal.png");

	int teamMember_row = 4;
	int teamMember_col = 1;
	float teamMember_row_d = 0.3f;
	float teamMember_col_d = 0.1f;

	newTeam.setUpTeamMember(m_texObj, "Shader/BlankSpot.png", teamMember_row, teamMember_col, teamMember_row_d, teamMember_col_d, teamMember_row_d, teamMember_col_d, "Shader/J. W. Bjerk/frame-4-sky.png", (float)teamMember_row*teamMember_row_d + 0.2f, (float)teamMember_col*teamMember_col_d + 0.2f);
	newTeam.getTeamMember()->insertClassObjList(1,&newCharacter);

	newSound = new soundSystem();
	newBG = new soundSystem();
	newBG->playSound("bg1.wav", true);
	newSound->incVolume();
	newBG->incVolume();
	newBG->incVolume();


	testMovingX = 0.0f;
	testMovingY = 0.0f;
	testMovingObj.setSprite(0.0f, 0.0f, testMovingX, testMovingY, 0.0f, 0.0f, testMovingX, testMovingY);

	itemCounter = 0;
	newGameFont = new gameFont((float)m_width, (float)m_height);
	newViewCharacter.init(m_texObj);
	newViewCharacter.setTranslateValue((float)m_width, (float)m_height);
	newViewCharacter.insertCharacter(&newCharacter);
	newViewCharacter.insertEquipment(&newItem0);
	newViewCharacter.insertItem(&newItem1);
	newViewCharacter.insertCharacter(&newCharacter2);
	newViewCharacter.eraseCharacter(0);
	newViewCharacter.insertCharacter(&newCharacter);
}


gameWindow::~gameWindow()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();

	delete _DefaultColorProgram;
	delete m_texObj;
}

bool gameWindow::init()
{
	if (!glfwInit()) {
		std::cout << "GLFW error" << std::endl;
		return false;
	}
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	m_window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);
	if (!m_window) {
		std::cout << "window error" << std::endl;
		return false;
	}

	glfwMakeContextCurrent(m_window);
	glfwSetWindowPos(m_window, 100, 100);

	if (glewInit() != GLEW_OK) {
		std::cout << "GLEW error" << std::endl;
		return false;
	}

	initKeys();
	initCallbacks();


	return true;
}

void gameWindow::initKeys()
{
	for (bool i : m_key)
		i = false;
	for (bool j : m_mouseButton)
		j = false;
}

void gameWindow::initCallbacks()
{
	glfwSetWindowUserPointer(m_window, this);
	glfwSetKeyCallback(m_window, key_callback);
	glfwSetMouseButtonCallback(m_window, mouse_button_callback);
	glfwSetCursorPosCallback(m_window, cursor_position_callback);
	glfwSetWindowSizeCallback(m_window, resize_callback);
}

void gameWindow::gameLoop()
{
	while (!gameClose()) {
		time = glfwGetTime();
		deltaTime = time - lastTime;
		if (deltaTime >= maxPeriod) {
			lastTime = time;
			gameClear();
			gameUpdate();
		}
	}
}

void gameWindow::gameClear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void gameWindow::gameUpdate()
{
	glfwPollEvents();

	resetDrawProgram();

	newGameFont->RenderText(std::to_string(deltaTime), -1.5f, -1.0f, 0.001f, glm::vec3(0.5f, 0.4f, 0.3f));
	switch (newState) {
	case mainScene:
		spriteMainScene();
		break;
	case playScene:
		_DefaultColorProgram->enable();
		m_texObj->enable(_DefaultColorProgram->getUniformLocation("sampler_1"), MenuTexture);
		MenuSprites[0].drawSprite();
		m_texObj->disable();
		_DefaultColorProgram->disable();

		_DefaultColorProgram->enable();
		m_texObj->enable(_DefaultColorProgram->getUniformLocation("sampler_1"), MenuTexture);
		MenuSprites[1].drawSprite();
		m_texObj->disable();
		_DefaultColorProgram->disable();

		_DefaultColorProgram->enable();
		m_texObj->enable(_DefaultColorProgram->getUniformLocation("sampler_1"), MenuTexture);
		MenuSprites[2].drawSprite();
		m_texObj->disable();
		_DefaultColorProgram->disable();

		testMovingX = 0.0f;
		testMovingY = 0.0f;
		break;
	case characterMenuScene:
		if (isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {

		}
		newViewCharacter.updateMouseCord(getWindowMousePosx(), getWindowMousePosy());
		newViewCharacter.displayAllObjects(m_texObj,_DefaultColorProgram);
		/*
		newClassTest.displayClassObjBoarder(_DefaultColorProgram, 0.3f, 0.9f);
		newClassTest.displayClassObjGrid(_DefaultColorProgram, 0.4f, -0.4f);
		newClassTest.displayClassObjList(_DefaultColorProgram, 0.4f, -0.4f);
		
		newCharacter.displayEquipmentBoarder(_DefaultColorProgram, -0.1f, 0.1f);
		newCharacter.displayEquipmentGrid(_DefaultColorProgram, 0.0f, 0.0f);
		newCharacter.displayEquipmentList(_DefaultColorProgram, 0.0f, 0.0f);

		newTeam.displayTeamMemberBoarder(_DefaultColorProgram, -0.1f, 0.1f);
		newTeam.displayTeamMemberGrid(_DefaultColorProgram, 0.0f, 0.0f);
		newTeam.displayTeamMemberList(_DefaultColorProgram, 0.0f, 0.0f);
		*/
		break;
	case teamMenuScene:
		if (isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
		}
		if (testMovingX < 1.0f) {
			testMovingX += 0.01f;
			testMovingY += 0.01f;
			testMovingObj.setSprite(1.0f-testMovingX, 0.0f, testMovingX, 1.0f, 0.0f, 0.0f, testMovingX, 1.0f);
		}
		_DefaultColorProgram->enable();
		_DefaultColorProgram->setTranslateMatrix(0.0f,0.0f,0.0f);
		m_texObj->enable(_DefaultColorProgram->getUniformLocation("sampler_1"), crusorTexture);
		testMovingObj.drawSprite();
		m_texObj->disable();
		_DefaultColorProgram->disable();
		break;
	case missionScene:
		break;
	default:
		break;
	}
	spriteCrusor();
	glfwSwapBuffers(m_window);
}

bool gameWindow::isKeyPressed(unsigned int key) const
{
	if (key>KEY_MAX)
		return false;
	return m_key[key];
}

bool gameWindow::isMouseButtonPressed(unsigned int button) const
{
	if (button>MOUSE_BUTTON_MAX)
		return false;
	return m_mouseButton[button];
}

void gameWindow::key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	gameWindow* win = (gameWindow*)glfwGetWindowUserPointer(window);
	switch (win->newState) {
	case playScene:
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			win->newState = mainScene;
		break;
	case characterMenuScene:
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			win->newState = playScene;
		else if (key == GLFW_KEY_KP_0 && action == GLFW_PRESS) {
		}
		else if (key == GLFW_KEY_KP_1 && action == GLFW_PRESS) {
		}
		else if (key == GLFW_KEY_KP_ADD && action == GLFW_PRESS) {
			win->newSound->incVolume();
		}
		else if (key == GLFW_KEY_KP_SUBTRACT && action == GLFW_PRESS) {
			win->newSound->decVolume();
		}
		else if (key == GLFW_KEY_KP_9 && action == GLFW_PRESS) {
		}
		break;
	case teamMenuScene:
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			win->newState = playScene;
		break;
	case missionScene:
		break;
	default:
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		break;
	}

	win->m_key[key] = action != GLFW_RELEASE;
}

void gameWindow::mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
{
	gameWindow* win = (gameWindow*)glfwGetWindowUserPointer(window);
	switch (win->newState) {
	case mainScene:
		if (action == GLFW_PRESS) {
			if (button == GLFW_MOUSE_BUTTON_LEFT) {
				win->newState = playScene;
				win->newSound->playSound("wave2.wav", false);
			}
			else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
			}
		}
		else if (action == GLFW_RELEASE) {
			if (button == GLFW_MOUSE_BUTTON_LEFT) {
			}
			else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
			}
		}
		break;
	case playScene:
		if (action == GLFW_PRESS) {
			if (button == GLFW_MOUSE_BUTTON_LEFT) {
				if (win->MenuSprites[0].isCollision(win->getWindowMousePosx(), win->getWindowMousePosy(), 0.0f, 0.0f)) {
					win->newState = characterMenuScene;
				}
				else if (win->MenuSprites[1].isCollision(win->getWindowMousePosx(), win->getWindowMousePosy(), 0.0f, 0.0f))
					win->newState = teamMenuScene;
				else if (win->MenuSprites[2].isCollision(win->getWindowMousePosx(), win->getWindowMousePosy(), 0.0f, 0.0f))
					win->newState = missionScene;
			}
			else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
				win->newState = mainScene;
			}
		}
		else if (action == GLFW_RELEASE) {
			if (button == GLFW_MOUSE_BUTTON_LEFT) {

			}
			else if (button == GLFW_MOUSE_BUTTON_RIGHT) {

			}
		}
		break;
	case loading:
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
			win->CurrentSpritesLocation_x = 0.0f;
			win->CurrentSpritesLocation_y = 0.0f;
			win->newState = mainScene;
		}
		break;
	case characterMenuScene:
		int __index;
		int _collisionIndex;
		if (action == GLFW_PRESS) {
			if (button == GLFW_MOUSE_BUTTON_LEFT) {
				if ((__index = win->newViewCharacter.isCollisionWithInventory()) >= 0) {
					if (win->newViewCharacter.findItem(__index) != nullptr) {
						win->newViewCharacter.setMovingItem(0, __index);
					}
				}
				else if ((__index = win->newViewCharacter.isCollisionWithEquipment()) >= 0) {
					if (win->newViewCharacter.findEquipment(__index) != nullptr) {
						win->newViewCharacter.setMovingItem(1, __index);
					}
				}
				else if ((__index = win->newViewCharacter.isCollisionWithCharacter()) != -1) {
					win->newViewCharacter.setCurrCharacter(__index);
				}

			}
			else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
				if ((__index = win->newViewCharacter.isCollisionWithEquipment()) != -1) {
					if (win->newViewCharacter.findEquipment(__index)) {
						win->newViewCharacter.insertItem(win->newViewCharacter.findEquipment(__index));
						win->newViewCharacter.eraseEquipment(__index);
					}
				}
				else if ((__index = win->newViewCharacter.isCollisionWithInventory()) != -1) {
					if (win->newViewCharacter.findItem(__index)) {
						objItem* _item1 = win->newViewCharacter.findItem(__index);
						objItem* _item2 = win->newViewCharacter.findEquipment(_item1->getObjType());
						if (_item2) {
							win->newViewCharacter.eraseItem(__index);
							win->newViewCharacter.eraseEquipment(_item1->getObjType());
							win->newViewCharacter.insertItem(__index, _item2);
							win->newViewCharacter.insertEquipment(_item1);
						}
						else {
							win->newViewCharacter.insertEquipment(_item1);
							win->newViewCharacter.eraseItem(__index);
						}
					}
				}
				else {
					win->newState = playScene;
				}
			}
		}
		else if (action == GLFW_RELEASE) {
			if (button == GLFW_MOUSE_BUTTON_LEFT) {
				if ((_collisionIndex = win->newViewCharacter.isCollisionWithInventory()) >= 0) {
					win->newViewCharacter.moveItemToInventory();
				}
				//if the item is in the equipment
				else if ((_collisionIndex = win->newViewCharacter.isCollisionWithEquipment()) >= 0) {
					win->newViewCharacter.moveItemToEquipment();
				}
				//if the item is in invalid place
				else {
					win->newViewCharacter.setMovingItem(-1, -1);
				}
			}
			else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
			}
		}
		break;
	case teamMenuScene:
		if (action == GLFW_PRESS) {
			if (button == GLFW_MOUSE_BUTTON_LEFT) {
			}
			else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
				win->newState = playScene;
			}
		}
		else if (action == GLFW_RELEASE) {
			if (button == GLFW_MOUSE_BUTTON_LEFT) {
			}
			else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
			}
		}
		break;
	case missionScene:
		if (action == GLFW_PRESS) {
			if (button == GLFW_MOUSE_BUTTON_LEFT) {

			}
			else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
				win->newState = playScene;
			}
		}
		else if (action == GLFW_RELEASE) {
			if (button == GLFW_MOUSE_BUTTON_LEFT) {

			}
			else if (button == GLFW_MOUSE_BUTTON_RIGHT) {

			}
		}
		break;
	default:
		break;
	}
	win->m_mouseButton[button] = action != GLFW_RELEASE;
}

void gameWindow::cursor_position_callback(GLFWwindow * window, double xpos, double ypos)
{
	gameWindow* win = (gameWindow*)glfwGetWindowUserPointer(window);
	win->m_cursor_xpos = (float)xpos;
	win->m_cursor_ypos = (float)ypos;
}

void gameWindow::resize_callback(GLFWwindow * window, int width, int height)
{
	gameWindow* win = (gameWindow*)glfwGetWindowUserPointer(window);
	glViewport(0, 0, width, height);
	win->m_width = width;
	win->m_height = height;
}

void gameWindow::resetDrawProgram()
{
	_DefaultColorProgram->enable();
	_DefaultColorProgram->setOrthoMatrix((float)-m_width / m_height, (float)m_width / m_height, -1.0f, 1.0f, -3.0f, 3.0f);
	_DefaultColorProgram->setScaleMatrix(glm::vec3(testScaleValue, testScaleValue, testScaleValue));
	_DefaultColorProgram->setRotateMatrix(0.0f, 0.0f, 0.0f, 1.0f);
	//m_colorProgram.setColorAndEffect(1.0f, 1.0f, 1.0f, 1.0f, 0.0000001f, 0.0000001f, light_pos_z);
	_DefaultColorProgram->setColorAndEffect(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	_DefaultColorProgram->setTranslateMatrix(0.0f, 0.0f, 0.0f);
	_DefaultColorProgram->disable();
}

void gameWindow::spriteCrusor()
{
	////////// crusor //////////
	////////////////////////////

	//resetDrawProgram();
	_DefaultColorProgram->enable();
	_DefaultColorProgram->setTranslateMatrix(
		-0.5f*(2.0f * crusorSprite.getVexPosx() + crusorSprite.getVexWidth()) + getWindowMousePosx(),
		-0.5f*(2.0f * crusorSprite.getVexPosy() + crusorSprite.getVexHeight()) + getWindowMousePosy(),
		0.0f
	);
	//m_colorProgram.setColorAndEffect(1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, light_pos_z);
	_DefaultColorProgram->setColorAndEffect(0.5f, 0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f);

	m_texObj->enable(_DefaultColorProgram->getUniformLocation("sampler_1"), crusorTexture);
	crusorSprite.drawSprite();
	m_texObj->disable();

	_DefaultColorProgram->disable();

	////////////////////////////
	/////////// end ////////////
}

void gameWindow::spriteMainScene()
{
	//resetDrawProgram();
	_DefaultColorProgram->enable();
	_DefaultColorProgram->setTranslateMatrix((float)-m_width / m_height - (float)std::fmod(time, 8.0f) / 2, -1.0f, 0.0f);
	m_texObj->enable(_DefaultColorProgram->getUniformLocation("sampler_1"), backgroundTexture);
	backgroundSprite.drawSprite();
	m_texObj->disable();
	_DefaultColorProgram->disable();
}

void gameWindow::setCrusor()
{
	crusorSprite.setSprite(0.0f, 0.0f, 0.1f, 0.1f, 0.0f, 0.0f, 1.0f, 1.0f);
	crusorTexture = m_texObj->setPNGTextureID("Shader/CharacterLeft_Standing.png");
}

void gameWindow::setMainScene()
{
	backgroundTexture = m_texObj->setPNGTextureID("Shader/sky/Daylight Box_0.png");
	backgroundSprite.setSprite(0.0f, 0.0f, 4.0f * 2.0f * (float)m_width / m_height / testScaleValue, 2.0f * (float)m_height / m_height / testScaleValue, 0.0f, 0.0f, 3.0f, 1.0f);
}

float gameWindow::getWindowMousePosx()
{
	return (1.0f / testScaleValue) * ((m_cursor_xpos - (m_width / 2.0f)) / m_width) * 2.0f * m_width / m_height;
}

float gameWindow::getWindowMousePosy()
{
	return (1.0f / testScaleValue) * ((-m_cursor_ypos + (m_height / 2.0f)) / m_height) * 2.0f * m_height / m_height;
}

void gameWindow::testSceneKeyEvnts()
{
	if (isKeyPressed(GLFW_KEY_A)) {
	}
	if (isKeyPressed(GLFW_KEY_D)) {
	}
	if (isKeyPressed(GLFW_KEY_W)) {
	}
	if (isKeyPressed(GLFW_KEY_S)) {
	}

	if (isKeyPressed(GLFW_KEY_PERIOD)) {
		//std::cout << testDegree << std::endl;
		testDegree += 0.1f;
	}

	if (isKeyPressed(GLFW_KEY_COMMA)) {
		//std::cout << testDegree << std::endl;
		testDegree -= 0.1f;
	}

	if (isKeyPressed(GLFW_KEY_R)) {
		testDegree = 0.0f;
		light_pos_z = 1.0f;
		CurrentSpritesLocation_x = 0.0f;
		CurrentSpritesLocation_y = 0.0f;
	}

	if (isKeyPressed(GLFW_KEY_F)) {
	}

	if (isKeyPressed(GLFW_KEY_Z)) {
		light_pos_z++;
	}

	if (isKeyPressed(GLFW_KEY_C)) {
		light_pos_z--;
	}

	if (isKeyPressed(GLFW_KEY_X)) {
	}
}