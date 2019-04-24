#include "AppClass.h"
using namespace Simplex;
void Application::InitVariables(void)
{
	//Set the position and target of the camera
	m_pCameraMngr->SetPositionTargetAndUpward(
		vector3(0.0f, 5.0f, 100.0f), //Position
		vector3(0.0f, 0.0f, 0.0f),	//Target
		AXIS_Y);					//Up

	MyRigidBody* m_pSteveRB = nullptr; //Rigid Body of the model
	m_pLightMngr->SetPosition(vector3(0.0f, 3.0f, 13.0f), 1); //set the position of first light (0 is reserved for ambient light)

#ifdef DEBUG
	uint uInstances = 30;
#else
	uint uInstances = 30;
#endif
	m_v3Player = vector3(0.0f, 0.0f, 0.0f);
	matrix4 mSteve = glm::translate(m_v3Player);
	m_pEntityMngr->AddEntity("Minecraft\\Steve.obj", "Steve");
	m_pEntityMngr->SetModelMatrix(mSteve, "Steve");
	m_pEntityMngr->UsePhysicsSolver();

	
	for (uint i = 0; i < uInstances; i++) {
		m_pEntityMngr->AddEntity("Minecraft\\Cube.obj");
		vector3 v3Position = vector3(0.0f, -1.0f, 0.0f + (float)i * 10);
		matrix4 m4Position = glm::translate(v3Position);
		m_pEntityMngr->SetModelMatrix(m4Position);
		m_pEntityMngr->UsePhysicsSolver(true);
		m_pEntityMngr->SetMass(1);
	}
	m_uOctantLevels = 1;
	m_pRoot = new MyOctant(m_uOctantLevels, 5);
	//m_COffset = m_pCameraMngr->GetPosition() - m_v3Player;
	//m_pCameraMngr->SetPosition(m_v3Player - m_COffset);
	//glm::lookAt(m_pCameraMngr->GetPosition(), m_pCameraMngr->GetPosition() + m_v3Player, vector3(0.0f, 0.0f, 0.0f));
	m_pEntityMngr->Update();
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the ArcBall active?
	ArcBall();

	//Is the first person camera active?
	//m_COffset = m_pCameraMngr->GetPosition() - m_v3Player;
	//m_pCameraMngr->SetPosition(m_v3Player - m_COffset);
	CameraRotation();


	//Update Entity Manager
	m_pEntityMngr -> SetModelMatrix(glm::translate(m_v3Player), "Steve");
	m_pEntityMngr->Update();

	//Add objects to render list
	m_pEntityMngr->AddEntityToRenderList(-1, true);
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	
	if (m_uOctantID == -1) 
	{
		m_pRoot->Display();
	}
	else {
		m_pRoot->Display(m_uOctantID);
	}
	
	//display octree
	m_pRoot->Display();
	
	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();
	
	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();
	
	//draw gui,
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	//release the Entity

	// delete(m_pRoot);
	//release GUI
	ShutdownGUI();
}