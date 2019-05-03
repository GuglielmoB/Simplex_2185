#include "AppClass.h"
using namespace Simplex;
void Application::InitVariables(void)
{
	//Set the position and target of the camera
	m_pCameraMngr->SetPositionTargetAndUpward(
		vector3(0.0f, 5.0f, 25.0f), //Position
		vector3(0.0f, 0.0f, 0.0f),	//Target
		AXIS_Y);					//Up

	m_pLightMngr->SetPosition(vector3(0.0f, 3.0f, 13.0f), 1); //set the position of first light (0 is reserved for ambient light)


#ifdef DEBUG
	uint uInstances = 50;
#else
	uint uInstances = 30;
#endif



	m_pEntityMngr->AddEntity("Minecraft\\Steve.obj", "Steve");
	m_v3Player = vector3(1, 0, 1);
    mSteve = glm::translate(m_v3Player) * ToMatrix4(m_qPlayer) * ToMatrix4(m_qArcBall);
	m_pEntityMngr->SetModelMatrix(mSteve, "Steve");
	m_pEntityMngr->UsePhysicsSolver();
	


	//m_pEntityMngr->ApplyForce(vector3(0, 10, 0), "Steve");

	for (int i = 25; i < 35; i++) {
		m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Platform_1_Line1_" + std::to_string(i));
		m_v3Platform = vector3(i, -1, -12);
		mPlatform = glm::translate(m_v3Platform) * ToMatrix4(m_qPlatform) * ToMatrix4(m_qArcBall);
		m_pEntityMngr->SetModelMatrix(mPlatform , "Platform_1_Line1_" + std::to_string(i));
		//m_pEntityMngr->SetPosition(vector3(i, -2, -4), "Platform_1_" + std::to_string(i));
	}

	for (int i = 25; i < 35; i++) {
		m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Platform_1_Line2_" + std::to_string(i));
		m_v3Platform = vector3(i, -1, -13);
		mPlatform = glm::translate(m_v3Platform) * ToMatrix4(m_qPlatform) * ToMatrix4(m_qArcBall);
		m_pEntityMngr->SetModelMatrix(mPlatform, "Platform_1_Line2_" + std::to_string(i));
		//m_pEntityMngr->SetPosition(vector3(i, -2, -4), "Platform_1_" + std::to_string(i));
	}

	for (int i = 25; i < 35; i++) {
		m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Platform_1_Line3_" + std::to_string(i));
		m_v3Platform = vector3(i, -1, -14);
		mPlatform = glm::translate(m_v3Platform) * ToMatrix4(m_qPlatform) * ToMatrix4(m_qArcBall);
		m_pEntityMngr->SetModelMatrix(mPlatform, "Platform_1_Line3_" + std::to_string(i));
		//m_pEntityMngr->SetPosition(vector3(i, -2, -4), "Platform_1_" + std::to_string(i));
	}

	for (int i = 25; i < 35; i++) {
		m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Platform_1_Line4_" + std::to_string(i));
		m_v3Platform = vector3(i, -1, -15);
		mPlatform = glm::translate(m_v3Platform) * ToMatrix4(m_qPlatform) * ToMatrix4(m_qArcBall);
		m_pEntityMngr->SetModelMatrix(mPlatform, "Platform_1_Line4_" + std::to_string(i));
		//m_pEntityMngr->SetPosition(vector3(i, -2, -4), "Platform_1_" + std::to_string(i));
	}

	for (int i = 25; i < 35; i++) {
		m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Platform_1_Line5_" + std::to_string(i));
		m_v3Platform = vector3(i, -1, -16);
		mPlatform = glm::translate(m_v3Platform) * ToMatrix4(m_qPlatform) * ToMatrix4(m_qArcBall);
		m_pEntityMngr->SetModelMatrix(mPlatform, "Platform_1_Line5_" + std::to_string(i));
		//m_pEntityMngr->SetPosition(vector3(i, -2, -4), "Platform_1_" + std::to_string(i));
	}


	for (int i = 25; i < 35; i++) {
		m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Platform_1_Line6_" + std::to_string(i));
		m_v3Platform = vector3(i, -1, -17);
		mPlatform = glm::translate(m_v3Platform) * ToMatrix4(m_qPlatform) * ToMatrix4(m_qArcBall);
		m_pEntityMngr->SetModelMatrix(mPlatform, "Platform_1_Line6_" + std::to_string(i));
		//m_pEntityMngr->SetPosition(vector3(i, -2, -4), "Platform_1_" + std::to_string(i));
	}


	for (int i = 25; i < 35; i++) {
		m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Platform_1_Line7_" + std::to_string(i));
		m_v3Platform = vector3(i, -1, -18);
		mPlatform = glm::translate(m_v3Platform) * ToMatrix4(m_qPlatform) * ToMatrix4(m_qArcBall);
		m_pEntityMngr->SetModelMatrix(mPlatform, "Platform_1_Line7_" + std::to_string(i));
		//m_pEntityMngr->SetPosition(vector3(i, -2, -4), "Platform_1_" + std::to_string(i));
	}

	for (int i = 25; i < 35; i++) {
		m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Platform_1_Line8_" + std::to_string(i));
		m_v3Platform = vector3(i, -1, -19);
		mPlatform = glm::translate(m_v3Platform) * ToMatrix4(m_qPlatform) * ToMatrix4(m_qArcBall);
		m_pEntityMngr->SetModelMatrix(mPlatform, "Platform_1_Line8_" + std::to_string(i));
		//m_pEntityMngr->SetPosition(vector3(i, -2, -4), "Platform_1_" + std::to_string(i));
	}


	for (int i = 25; i < 35; i++) {
		m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Platform_2_Line1_" + std::to_string(i));
		m_v3Platform = vector3(i, -1, -24);
		mPlatform = glm::translate(m_v3Platform) * ToMatrix4(m_qPlatform) * ToMatrix4(m_qArcBall);
		m_pEntityMngr->SetModelMatrix(mPlatform, "Platform_2_Line1_" + std::to_string(i));
		//m_pEntityMngr->SetPosition(vector3(i, -2, -4), "Platform_1_" + std::to_string(i));
	}

	for (int i = 25; i < 35; i++) {
		m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Platform_2_Line2_" + std::to_string(i));
		m_v3Platform = vector3(i, -1, -25);
		mPlatform = glm::translate(m_v3Platform) * ToMatrix4(m_qPlatform) * ToMatrix4(m_qArcBall);
		m_pEntityMngr->SetModelMatrix(mPlatform, "Platform_2_Line2_" + std::to_string(i));
		//m_pEntityMngr->SetPosition(vector3(i, -2, -4), "Platform_1_" + std::to_string(i));
	}


	for (int i = 25; i < 35; i++) {
		m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Platform_2_Line3_" + std::to_string(i));
		m_v3Platform = vector3(i, -1, -26);
		mPlatform = glm::translate(m_v3Platform) * ToMatrix4(m_qPlatform) * ToMatrix4(m_qArcBall);
		m_pEntityMngr->SetModelMatrix(mPlatform, "Platform_2_Line3_" + std::to_string(i));
		//m_pEntityMngr->SetPosition(vector3(i, -2, -4), "Platform_1_" + std::to_string(i));
	}

	for (int i = 25; i < 35; i++) {
		m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Platform_2_Line4_" + std::to_string(i));
		m_v3Platform = vector3(i, -1, -27);
		mPlatform = glm::translate(m_v3Platform) * ToMatrix4(m_qPlatform) * ToMatrix4(m_qArcBall);
		m_pEntityMngr->SetModelMatrix(mPlatform, "Platform_2_Line4_" + std::to_string(i));
		//m_pEntityMngr->SetPosition(vector3(i, -2, -4), "Platform_1_" + std::to_string(i));
	}


	for (int i = 25; i < 35; i++) {
		m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Platform_2_Line5_" + std::to_string(i));
		m_v3Platform = vector3(i, -1, -28);
		mPlatform = glm::translate(m_v3Platform) * ToMatrix4(m_qPlatform) * ToMatrix4(m_qArcBall);
		m_pEntityMngr->SetModelMatrix(mPlatform, "Platform_2_Line5_" + std::to_string(i));
		//m_pEntityMngr->SetPosition(vector3(i, -2, -4), "Platform_1_" + std::to_string(i));
	}

	for (int i = 25; i < 35; i++) {
		m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Platform_2_Line6_" + std::to_string(i));
		m_v3Platform = vector3(i, -1, -29);
		mPlatform = glm::translate(m_v3Platform) * ToMatrix4(m_qPlatform) * ToMatrix4(m_qArcBall);
		m_pEntityMngr->SetModelMatrix(mPlatform, "Platform_2_Line6_" + std::to_string(i));
		//m_pEntityMngr->SetPosition(vector3(i, -2, -4), "Platform_1_" + std::to_string(i));
	}

	for (int i = 25; i < 35; i++) {
		m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Platform_2_Line7_" + std::to_string(i));
		m_v3Platform = vector3(i, -1, -30);
		mPlatform = glm::translate(m_v3Platform) * ToMatrix4(m_qPlatform) * ToMatrix4(m_qArcBall);
		m_pEntityMngr->SetModelMatrix(mPlatform, "Platform_2_Line7_" + std::to_string(i));
		//m_pEntityMngr->SetPosition(vector3(i, -2, -4), "Platform_1_" + std::to_string(i));
	}

	for (int i = 25; i < 35; i++) {
		m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Platform_2_Line8_" + std::to_string(i));
		m_v3Platform = vector3(i, -1, -31);
		mPlatform = glm::translate(m_v3Platform) * ToMatrix4(m_qPlatform) * ToMatrix4(m_qArcBall);
		m_pEntityMngr->SetModelMatrix(mPlatform, "Platform_2_Line8_" + std::to_string(i));
		//m_pEntityMngr->SetPosition(vector3(i, -2, -4), "Platform_1_" + std::to_string(i));
	}

	
	for (int i = 0; i < 60; i++) {

	m_pEntityMngr->AddEntity("Minecraft\\Cow.obj", "Cow_1_" + std::to_string(i));
	m_v3Cow = vector3(0, 0, 0);
	mCow = glm::translate(m_v3Player) * ToMatrix4(m_qPlayer) * ToMatrix4(m_qArcBall);
	m_pEntityMngr->SetModelMatrix(mCow, "Cow");
	m_pEntityMngr->SetPosition(vector3(i, 0, 1), "Cow_1_"+ std::to_string(i));
	m_pEntityMngr->UsePhysicsSolver();
	m_pEntityMngr->SetMass(1);
	}

	
	optimalPath = ConstructPath();

	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 30; j++) {
			bool isPath = false;


			if (!isPath) {
				m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Floor_" + std::to_string(i) + "_" + std::to_string(j)); //the other floor is there too i guess
				m_v3Player = vector3(i * 2.01f, -2.01f, j * 2.01f);
			}

			mSteve = glm::translate(m_v3Player);
			m_pEntityMngr->SetModelMatrix(mSteve * glm::scale(vector3(2.0f)));
		}
	}


	/*
	m_v3Creeper = vector3(30.0f, 0.0f, 0.0f);
	matrix4 mCreeper = glm::translate(m_v3Creeper);
	m_pEntityMngr->AddEntity("Minecraft\\Creeper.obj", "Creeper");
	m_pEntityMngr->SetModelMatrix(mCreeper, "Creeper");
	m_pEntityMngr->UsePhysicsSolver();
	m_pEntityMngr->SetPosition(m_v3Creeper,"Creeper");


	m_v3Elk = vector3(20.0f, 0.0f, 0.0f);
	matrix4 mElk = glm::translate(m_v3Elk);
	m_pEntityMngr->AddEntity("Minecraft\\elk.obj", "Elk");
	m_pEntityMngr->SetModelMatrix(mElk, "Elk");
	m_pEntityMngr->UsePhysicsSolver();
	m_pEntityMngr->SetPosition(m_v3Elk, "Elk");
	

	for (uint i = 0; i < uInstances; i++) {
		m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Cube"+i);
		vector3 v3Position = vector3(0.0f, 2.0f, 0.0f + (float)i * 10);
		matrix4 m4Position = glm::translate(v3Position);
		m_pEntityMngr->SetModelMatrix(m4Position, "Cube"+i);
		m_pEntityMngr->SetPosition(v3Position, "Cube"+i);
		m_pEntityMngr->UsePhysicsSolver();
		m_pEntityMngr->SetMass(.8);
	}
	*/


	//m_uOctantLevels = 1;
	//m_pRoot = new MyOctant(m_uOctantLevels, 5);
	//m_pEntityMngr->Update();
}
void Application::Update(void)
{
	bool colliding = false;
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the ArcBall active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();
	//m_v3PlayerVelo.y += 1;
	mSteve = glm::translate(m_v3Player) * ToMatrix4(m_qPlayer) * ToMatrix4(m_qArcBall);
	m_pEntityMngr->SetModelMatrix(mSteve, "Steve");

	//Update Entity Manager
	m_pEntityMngr->Update();
	m_pEntityMngr->SetModelMatrix(glm::translate(m_v3Player), "Steve");

	//Add objects to render list
	m_pEntityMngr->AddEntityToRenderList(-1, true);

	m_v3Player += m_v3PlayerVelo * .5;

	


	// clamp player to ground
	if (m_v3Player.y < 0)
		m_v3Player.y = 0;

	// check if player is on ground
	m_bIsPlayerOnGround = m_v3Player.y == 0;

	m_v3PlayerVelo += m_v3Gravity * .5;

	if (colliding == true && m_v3Player.y > 5) {
		m_v3Player.y = m_v3Player.y;
	}

	
	



	for (int i = 0; i < 60; i++) {

		if (m_pEntityMngr->GetPosition("Cow_1_" + std::to_string(i)).z < 0) {
			m_pEntityMngr->ApplyForce(vector3(0, 0, -10), "Cow_1_" + std::to_string(i));
		}

		if (m_pEntityMngr->GetPosition("Cow_1_" + std::to_string(i)).x < 0) {
			m_pEntityMngr->ApplyForce(vector3(-10, 0, 0), "Cow_1_" + std::to_string(i));
		}
		if (m_pEntityMngr->GetPosition("Cow_1_" + std::to_string(i)).x > 60) {
			m_pEntityMngr->ApplyForce(vector3(10, 0, 0), "Cow_1_" + std::to_string(i));
		}

	
	}
	

}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	/*
	if (m_uOctantID == -1) 
	{
		m_pRoot->Display();
	}
	else {
		m_pRoot->Display(m_uOctantID);
	}
	*/
	//display octree
	//m_pRoot->Display();
	
	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList("Skybox_01.png");
	
	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();
	
	//draw gui,
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}

std::vector<vector2> Application::ConstructPath(void) { //makes the path
	std::vector<vector2> path;
	int x = 0;
	int y = 0;

	while (vector2(x, y) != vector2(6, 6)) {
		path.push_back(vector2(x, y));

		if (x < 6 && !blocks[x + 1][y]) //steve tries to go through unblocked terrain first
			x++;

		else if (y < 6 && !blocks[x][y + 1])
			y++;

		else if (x < 6) { //eventually he pushes through
			x++;

			for (int i = 1; i < 7 - x; i++) { //steve is smart and tries to avoid terrain he just pushed in front of himself
				if (!blocks[x + i][y]) {
					blocks[x + i][y] = true;
					i = 7;
				}
			}
			blocks[x][y] = false;
		}
		else {
			y++;

			for (int i = 1; i < 7 - y; i++) {
				if (!blocks[x][y + i]) {
					blocks[x][y + i] = true;
					i = 7;
				}
			}
			blocks[x][y] = false;
		}
	}

	path.push_back(vector2(6, 6));

	return path;
}



void Application::Release(void)
{
	MyEntityManager::ReleaseInstance();

	// delete(m_pRoot);
	//release GUI
	ShutdownGUI();
}