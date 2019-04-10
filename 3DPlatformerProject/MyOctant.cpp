#include "MyOctant.h"
namespace Simplex {

	uint MyOctant::m_uOctantCount = 0;
	uint MyOctant::m_uMaxLevel = 0;
	uint MyOctant::m_uIdealEntityCount = 0;

#pragma region Constructors and Initializers
	MyOctant::MyOctant(uint a_nMaxLevel, uint a_nIdealEntityCount)
	{
		// Initialize
		Init();

		m_uOctantCount = 0;
		m_uMaxLevel = a_nMaxLevel;
		m_uIdealEntityCount = a_nIdealEntityCount;
		m_uID = m_uOctantCount;

		m_uOctantCount++;

		m_pRoot = this;
		m_lChild.clear();


#pragma region Octant Calculations

		std::vector<vector3> AllEntityMinandMax;

		for (uint i = 1; i < m_pEntityMngr->GetEntityCount(); i++) // Loop to get the min and max values from all the entities to calculate octant size
		{
			MyEntity* pEntity = m_pEntityMngr->GetEntity(i);
			MyRigidBody* pRigidBody = pEntity->GetRigidBody();
			AllEntityMinandMax.push_back(pRigidBody->GetMinGlobal());
			AllEntityMinandMax.push_back(pRigidBody->GetMaxGlobal());
		}

		MyRigidBody* pRigidBody = new MyRigidBody(AllEntityMinandMax); // Rigid body container of the values for the new octant

		vector3 m_v3HalfWidth = pRigidBody->GetHalfWidth(); // Gets haldwidth of the octant

		float fMax = std::numeric_limits<float>::lowest(); // This was mentioned to me by a friend of mine who took DSA2 last year, almost used the standard min here instead.
		for (uint i = 0; i < 3; i++) // Loop to get the max float within the vector
		{
			if (fMax < m_v3HalfWidth[i])
			{
				fMax = m_v3HalfWidth[i];
			}
		}

		m_fSize = fMax * 2.0f; // sets octant size
		m_v3Center = pRigidBody->GetCenterLocal(); // sets octant's center to the local center of our rigidbody container
		m_v3Min = m_v3Center - vector3(m_fSize) / 2.0f; // Sets Minimum
		m_v3Max = m_v3Center + vector3(m_fSize) / 2.0f; // Sets Maximum
#pragma endregion

		ConstructTree(m_uMaxLevel); // Constructor for the tree of octants
		AllEntityMinandMax.clear(); // clears the vector
		delete(pRigidBody); // deletes the pointer for our rigidbody container
	}

	MyOctant::MyOctant(vector3 a_v3Center, float a_fSize)
	{
		Init();
		m_v3Center = a_v3Center;
		m_fSize = a_fSize;

		m_v3Min = m_v3Center - vector3(m_fSize) / 2.0f;
		m_v3Max = m_v3Center + vector3(m_fSize) / 2.0f;

		m_uOctantCount++;
	}

	MyOctant::MyOctant(MyOctant const & other) // Gives this octant the values of the other's octant
	{
		m_uChildren = other.m_uChildren;
		m_v3Center = other.m_v3Center;
		m_v3Min = other.m_v3Min;
		m_v3Max = other.m_v3Max;

		m_fSize = other.m_fSize;
		m_uID = other.m_uID;
		m_uLevel = other.m_uLevel;
		m_pParent = other.m_pParent;

		m_pRoot = other.m_pRoot;
		m_lChild = other.m_lChild;

		m_pMeshMngr = MeshManager::GetInstance();
		m_pEntityMngr = MyEntityManager::GetInstance();

		for (uint i = 0; i < 8; i++)
		{
			m_pChild[i] = other.m_pChild[i];
		}
	}

	MyOctant & MyOctant::operator=(MyOctant const & other)
	{
		if (this != &other)
		{
			Release();
			Init();
			MyOctant SwapOctant = MyOctant(other);
			Swap(SwapOctant);
		}
		return *this;
	}

	MyOctant::~MyOctant(void)
	{
		Release();
	}


	void MyOctant::Init(void)
	{
		m_uChildren = 0;

		m_fSize = 0.0f;

		m_uID = m_uOctantCount;
		m_uLevel = 0;

		m_v3Center = ZERO_V3;
		m_v3Min = ZERO_V3;
		m_v3Max = ZERO_V3;

		m_pMeshMngr = MeshManager::GetInstance();
		m_pEntityMngr = MyEntityManager::GetInstance();

		m_pRoot = nullptr;
		m_pParent = nullptr;
		for (uint n = 0; n < 8; n++)
		{
			m_pChild[n] = nullptr;
		}
	}

	void MyOctant::ConstructTree(uint a_nMaxLevel)
	{
		if (m_uLevel != 0) // Check to make sure we're at root level, so only root is able to construct the tree
		{
			return;
		}

		m_uMaxLevel = a_nMaxLevel;
		m_uOctantCount = 1; // Denotes we're at the first octant

		m_EntityList.clear(); // Clears the list of entities in case there are any left over
		KillBranches(); // Kills the branches of the tree to make sure it's empty
		m_lChild.clear(); // Clears the list of children for the same reasons as above

		if (ContainsMoreThan(m_uIdealEntityCount))
		{
			Subdivide();
		}

		AssignIDtoEntity(); // sets the dimensions for the octree up from the root

		ConstructList(); // Constructs the list of children
	}

	void MyOctant::AssignIDtoEntity(void)
	{
		if (IsLeaf())
		{
			uint uEntityCount = m_pEntityMngr->GetEntityCount();

			for (uint i = 0; i < uEntityCount; i++) // Sets the dimensions within the bounding box
			{
				if (IsColliding(i))
				{
					m_EntityList.push_back(i);
					m_pEntityMngr->AddDimension(i, m_uID);
				}
			}
			return;
		}

		for (uint i = 0; i < m_uChildren; i++)
		{
			m_pChild[i]->AssignIDtoEntity();
		}

	}

	void MyOctant::ConstructList(void)
	{
		for (uint i = 0; i < m_uChildren; i++)
		{
			m_pChild[i]->ConstructList();
		}

		if (m_EntityList.size() > 0)
		{
			m_pRoot->m_lChild.push_back(this);
		}
	}

	void MyOctant::Swap(MyOctant & other)
	{
		std::swap(m_uChildren, other.m_uChildren);

		std::swap(m_uID, other.m_uID);
		std::swap(m_pRoot, other.m_pRoot);
		std::swap(m_lChild, other.m_lChild);

		std::swap(m_v3Center, other.m_v3Center);
		std::swap(m_v3Min, other.m_v3Min);
		std::swap(m_v3Max, other.m_v3Max);
		std::swap(m_fSize, other.m_fSize);

		m_pMeshMngr = MeshManager::GetInstance();
		m_pEntityMngr = MyEntityManager::GetInstance();

		std::swap(m_uLevel, other.m_uLevel);
		std::swap(m_pParent, other.m_pParent);

		for (uint i = 0; i < 8; i++)
		{
			std::swap(m_pChild[i], other.m_pChild[i]);
		}
	}
#pragma endregion


#pragma region Display
	// This contains Display and DisplayLeafs

	void MyOctant::Display(uint a_nIndex, vector3 a_v3Color)
	{
		if (m_uID == a_nIndex)
		{
			m_pMeshMngr->AddWireCubeToRenderList(
				glm::translate(m_v3Center) * glm::scale(vector3(m_fSize)),
				a_v3Color,
				RENDER_WIRE
			);

			return;
		}

		for (uint nIndex = 0; nIndex < m_uChildren; nIndex++)
		{
			m_pChild[nIndex]->Display(a_nIndex);
		}
	}

	void MyOctant::Display(vector3 a_v3Color)
	{
		m_pMeshMngr->AddWireCubeToRenderList(
			glm::translate(m_v3Center) * glm::scale(vector3(m_fSize)),
			a_v3Color,
			RENDER_WIRE
		);

		for (uint i = 0; i < m_uChildren; i++)
		{
			m_pChild[i]->Display(a_v3Color);
		}
	}

	void MyOctant::DisplayLeafs(vector3 a_v3Color)
	{
		m_pMeshMngr->AddWireCubeToRenderList(
			glm::translate(m_v3Center) * glm::scale(vector3(m_fSize)),
			a_v3Color,
			RENDER_WIRE
		);

		for (uint i = 0; i < m_lChild.size(); i++)
		{
			m_lChild[i]->DisplayLeafs(a_v3Color);
		}
	}
#pragma endregion


#pragma region Gets
	float MyOctant::GetSize(void)
	{
		return m_fSize;
	}

	vector3 MyOctant::GetCenterGlobal(void)
	{
		return m_v3Center;
	}

	vector3 MyOctant::GetMinGlobal(void)
	{
		return m_v3Min;
	}

	vector3 MyOctant::GetMaxGlobal(void)
	{
		return m_v3Max;
	}

	MyOctant * MyOctant::GetChild(uint a_nChild)
	{
		if (a_nChild >= 8 || a_nChild < 0)
		{
			return nullptr;
		}
		return m_pChild[a_nChild];
	}

	MyOctant * MyOctant::GetParent(void)
	{
		return m_pParent;
	}

	uint MyOctant::GetOctantCount(void)
	{
		return m_uOctantCount;
	}

#pragma endregion

#pragma region Checks
	bool MyOctant::IsColliding(uint a_uRBIndex)
	{
		uint numOfEntities = m_pEntityMngr->GetEntityCount();

		if (numOfEntities <= a_uRBIndex) // Stops if the index is out of bounds
		{
			return false;
		}


		MyEntity* pEntity = m_pEntityMngr->GetEntity(a_uRBIndex); // position of entity within index
		MyRigidBody* pRigidBody = pEntity->GetRigidBody();

		vector3 v3MinEntity = pRigidBody->GetMinGlobal();
		vector3 v3MaxEntity = pRigidBody->GetMaxGlobal();

		for (uint i = 0; i < 3; i++) // loop to check whether the check whether the entity is inside the bounds of the octant or not, if they aren't it returns false.
		{
			if (m_v3Max[i] < v3MinEntity[i] || m_v3Min[i] > v3MaxEntity[i]) {
				return false;
			}
		}

		return true; // Returns true if the entity is within the bounds of the octant
	}

	bool MyOctant::IsLeaf(void) // Checks if the object is a leaf
	{
		return m_uChildren == 0;
	}

	bool MyOctant::ContainsMoreThan(uint a_nEntities) // Checks if the octant contains more than a certain number of entities
	{
		uint numofObjects = m_pEntityMngr->GetEntityCount();
		uint numofCollidingObjects = 0;

		for (uint i = 0; i < numofObjects; i++) // This loop checks through all of the objects within the octant, returns true if it contains more than provided number
		{
			if (IsColliding(i))
			{
				numofCollidingObjects++;
			}
			if (numofCollidingObjects > a_nEntities)
			{
				return true;
			}
		}
		return false;
	}
#pragma endregion


#pragma region Subdivide
	void MyOctant::Subdivide(void) // Creates the subdivisions of the root octant
	{
		if (m_uLevel >= m_uMaxLevel) // Stops if we're already at the max level of subdivisions
		{
			return;
		}

		if (m_uChildren != 0) // Stops if the octant already has children
		{
			return;
		}

		m_uChildren = 8;

		// sets the size of the octant and half of its size, also sets default value of vector for the center of each child octant
		// for each individual octant, the x, y, or z, of the default v3center value, we start from lower left and work clockwise
		float fSize = m_fSize / 2.0f;
		float Half_fSize = fSize / 2.0f;
		vector3 v3Center = m_v3Center - vector3(Half_fSize);
#pragma region Octant Subdivisions
		// This is the calculations for each of the octant subdivisions, I mostly just made this so I wouldn't have to scroll as far each time.

		m_pChild[0] = new MyOctant(v3Center, fSize); // Lower Left Back Octant

		v3Center.x += fSize;
		m_pChild[1] = new MyOctant(v3Center, fSize); // Lower Right Back Octant

		v3Center.z += fSize;
		m_pChild[2] = new MyOctant(v3Center, fSize); // Lower Right Front Octant

		v3Center.x -= fSize;
		m_pChild[3] = new MyOctant(v3Center, fSize); // Lower Left Front Octant

		v3Center.y += fSize;
		m_pChild[4] = new MyOctant(v3Center, fSize); // Upper Left Front Octant

		v3Center.z -= fSize;
		m_pChild[5] = new MyOctant(v3Center, fSize); // Upper Left Back Octant

		v3Center.x += fSize;
		m_pChild[6] = new MyOctant(v3Center, fSize); // Upper Right Back Octant

		v3Center.z += fSize;
		m_pChild[7] = new MyOctant(v3Center, fSize); // Upper Right Front Octant
#pragma endregion
		uint uChildLevel = m_uLevel + 1; // increments child level

		for (uint nIndex = 0; nIndex < 8; nIndex++) // Sets the Root and Parent
		{
			MyOctant* pChild = m_pChild[nIndex];
			pChild->m_pRoot = m_pRoot;
			pChild->m_pParent = this;
			pChild->m_uLevel = uChildLevel;
			if (pChild->ContainsMoreThan(m_uIdealEntityCount)) // Checks if the child contains more entities than the idela entity count, and subdivides it further if true
			{
				pChild->Subdivide();
			}
		}
	}
#pragma endregion


#pragma region Destroyers/Destructors
	void MyOctant::KillBranches(void)
	{
		if (IsLeaf()) { // Stops if we're at the leaf
			return;
		}

		for (uint i = 0; i < m_uChildren; i++) // Deletes the child branches and the children
		{
			m_pChild[i]->KillBranches();
			delete m_pChild[i];
			m_pChild[i] = nullptr;
		}

		m_uChildren = 0;
	}

	void MyOctant::ClearEntityList(void)
	{
		for (uint i = 0; i < m_uChildren; i++)
		{
			m_pChild[i]->ClearEntityList();
		}

		m_EntityList.clear();
		m_uChildren = 0;
	}

	void MyOctant::Release(void)
	{
		if (m_uLevel == 0)
		{
			KillBranches();
		}
		m_EntityList.clear();
		m_lChild.clear();
		Init();
	}
#pragma endregion


}