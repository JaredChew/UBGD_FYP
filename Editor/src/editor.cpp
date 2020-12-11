#include "editor.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdio.h>
#include <dirent.h>

#include <tchar.h>
#include <fstream>
#include <filesystem>

//#include <memory>
//#include "imgui_internal.h"

#include "Manipulators/geometry.h"
#include "Compound/mesh.h"
#include "Compound/texture.h"
#include "Specification/entity.h"
#include "Compound/transform.h"
#include "Manipulators/shader.h"
#include "Manipulators/system.h"
#include "Modules BackEnd/camera.h"
#include "Modules BackEnd/window.h"
#include "Compound/vertexArrayObject.h"
#include "Data Structure/doubleLinkList.hpp"
#include "Compound/lightingContainer.h"
#include "Compound/material.h"
#include "Compound/model.h"


#include "global.h"
#include "defaultSettings.h"


#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


#include "portable-file-dialogs.h"


// Resource Manager Item Start   ++++++

enum class ResourcesTextureIndex : unsigned int { Box = 0, Test, Glass, Web, Awesomeface, None, __Index_Size };

const std::string resourcesTexturePath[static_cast<int>(ResourcesTextureIndex::__Index_Size)] = {
	"../Media/box.jpg",
	"../Media/test.bmp",
	"../Media/glass.png",
	"../Media/web.jpg",
	"../Media/awesomeface.png",
	"../Media/None.png",
};

Texture* resourcesTexture[static_cast<int>(ResourcesTextureIndex::__Index_Size)];

struct AssetInfo {

	enum AssetType
	{
		AssetType_Unknown = 0,
		AssetType_Folder,
		AssetType_Texture,
		AssetType_Model,
		AssetType_Font,
		AssetType_Shader,
		AssetType_Audio,
		AssetType_TextDocument
	} assetType;

	std::string path;
	std::string name;
	
	std::vector<AssetInfo> subdirectoriesAssetPaths;

};

std::string assetDragDropCell[] = {
			"ASSET_UNKNOWN_CELL",
			"ASSET_FOLDER_CELL",
			"ASSET_TEXTURE_CELL",
			"ASSET_MODEL_CELL",
			"ASSET_FONT_CELL",
			"ASSET_SHADER_CELL",
			"ASSET_AUDIO_CELL",
			"ASSET_TEXT_DOCUMENT_CELL"
};

AssetInfo::AssetType checkFileType(std::string type)
{

#define SOIL2_TYPE_MAX_AMOUNT 12
#define ASSIMP_TYPE_MAX_AMOUNT 45
#define FREETYPE_TYPE_MAX_AMOUNT 6
#define FMOD_TYPE_MAX_AMOUNT 21
#define	GLSL_TYPE_MAX_AMOUNT 21


	if(type == ".txt") return AssetInfo::AssetType_TextDocument;


	std::string SOIL2_supportType[SOIL2_TYPE_MAX_AMOUNT] = {
		".bmp", ".png", ".jpg", ".bmp", ".tga", ".dds", ".psd", ".hdr", ".gif", ".pic", ".pkm", "pvr"
	};
	for (size_t i = 0; i < SOIL2_TYPE_MAX_AMOUNT; i++)
	{
		if (type == SOIL2_supportType[i]) return AssetInfo::AssetType_Texture;
	}


	//Ogre(".mesh.xml", ".skeleton.xml", ".material");
	std::string ASSIMP_supportType[ASSIMP_TYPE_MAX_AMOUNT] = {
		".dae", ".xml", ".blend", ".bvh", ".3ds", ".ase", ".obj", ".ply", ".dxf", ".ifc", ".nff",
		".nff", ".smd", ".vta", ".mdl", ".md2", ".md3", ".pk3", ".mdc", ".md5mesh", ".md5anim", ".md5camera",
		".x", ".q3o", ".q3s", ".raw", ".ac",".stl", ".dxf", ".irrmesh", ".xml", ".irr", ".xml", ".off",
		".ter", ".mdl", ".hmp", ".ms3d", ".lwo", ".lws", ".lxo", ".csm", ".ply", ".cob", ".scn" 
	};
	for (size_t i = 0; i < ASSIMP_TYPE_MAX_AMOUNT; i++)
	{
		if (type == ASSIMP_supportType[i]) return AssetInfo::AssetType_Model;
	}


	std::string FREETYPE_supportType[FREETYPE_TYPE_MAX_AMOUNT] = {
		".ttf", // TrueType fonts
		".pfb", ".pfa", ".otf", // Postscript Type 1 fonts
		".cid" // Postscript CID - keyed fonts
		".cff" // OpenType CFF and CFF2, bare CFF, and CEF fonts (CEF is a derivative of CFF used by Adobe in its SVG viewer)
	};
	for (size_t i = 0; i < FREETYPE_TYPE_MAX_AMOUNT; i++)
	{
		if (type == FREETYPE_supportType[i]) return AssetInfo::AssetType_Font;
	}


	std::string FMOD_supportType[FMOD_TYPE_MAX_AMOUNT] = { 
		".m3u", ".mp2", ".mp3", ".xma", ".wav", ".wax", ".wma"
		".aiff", ".asf", "asx.", ".dls", ".flac", ".fsb", ".it",  ".midi", ".mod",
		".ogg", // ogg vorbis
		".pls", "s3m", ".vag", ".xm"	
	};
	for (size_t i = 0; i < FMOD_TYPE_MAX_AMOUNT; i++)
	{
		if (type == FMOD_supportType[i]) return AssetInfo::AssetType_Audio;
	}


	std::string GLSL_supportType[GLSL_TYPE_MAX_AMOUNT] = {
		".vert", // GL_VERTEX_SHADER
		
		".cont", // GL 4.0 - GL_TESS_CONTROL_SHADER
		".eval", // GL 4.0 - GL_TESS_EVALUATION_SHADER
		".tess", // Tessellation Control and Evaluation Shaders
		
		".geom", // GL_GEOMETRY_SHADER
		".flag", // GL_FRAGMENT_SHADER
		".comp", // GL 4.3 or ARB_compute_shader - GL_COMPUTE_SHADER

		".glsl"  // All in one
	};
	for (size_t i = 0; i < GLSL_TYPE_MAX_AMOUNT; i++)
	{
		if (type == GLSL_supportType[i]) return AssetInfo::AssetType_Shader;
	}


	return AssetInfo::AssetType::AssetType_Unknown;

}

std::vector<AssetInfo> resourcesAssetPaths;

// End Resource Manager Item  ------







namespace Editor {

	// Editor Manager Item Start   ++++++

	std::string _currentPath = "";
	std::string _assetPath = "";

	struct EntityObjectGUI {

		EntityObjectGUI* _parent;
		DoubleLinkList<EntityObjectGUI*> _child;

		Entity* _entity;

		Mesh::DefaultGeometry _geometry;
		Model* _model;
		Material* _material;
		//Texture* _texture;

		bool visibility;

	};

	DoubleLinkList<EntityObjectGUI*> _entityObjectGUI_List;

	ImGuiTextFilter _filterHierarchy;
	ImGuiTextFilter _filterAssetTracker;

	ImGuiTreeNodeFlags _entityHaveChild_Flags = ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_SpanAvailWidth;
	ImGuiTreeNodeFlags _entityNullChild_Flags = ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_NoTreePushOnOpen;

	LightingContainer* _lightingContainer;

	EntityObjectGUI* _selectedEntityObjectGUI;

	char _selectedEntityName_char[128];
	std::string _selectedEntityName_string;

	glm::vec3 _selectedTranslation;
	glm::vec3 _selectedRotation;
	glm::vec3 _selectedDimension;

	const char* _geometryTypesName[] = { "Render Board", "Triangle", "Square", "Circle", "Stadium", "Pyramid", "Cube", "Sphere", "Cone", "Cylinder", "Torus" };
	Mesh::DefaultGeometry _selectedGeometryType;

	int _selectedTextureIndex;
	Material* _seletedMaterial;

	Texture* _screenTexture;
	Texture* _screenDepth;

	EntityObjectGUI* _draggingEntityObjectGUI = nullptr;
	bool _isDragging = false;


	Camera* _camera;

	enum class WorldRenderStyleType : int { Diffuse = 0, Polygon, Point, Lighting };
	int _worldRenderStyle;

	unsigned int _differentEntityNameIndex = 0;

	// End Editor Manager Item  ------



	void __editorHierarchyOwn_addEntityObject(EntityObjectGUI* entityObjectGUIData);
	void __editorHierarchyOwn_addNewEntityObject();
	void __editorHierarchyOwn_initSelectedEntityVariable(EntityObjectGUI* entityObjectGUI);
	void __editorHierarchyOwn_showEntityToList(EntityObjectGUI* entityObjectGUI, int& index);
	bool __editorHierarchyOwn_isOneOfChild(EntityObjectGUI* objectEntityObjectGUI, EntityObjectGUI* targetEntityObjectGUI);

	void __editorAssetTrackerOwn_generateAssetList(const std::string& folderDir, std::vector<AssetInfo>& currentAseetList);

	std::wstring getAbsoluteExecutionDirectory()
	{
		TCHAR szPath[MAX_PATH] = { 0 };
		GetModuleFileName(NULL, szPath, MAX_PATH);
		//(_tcsrchr(szPath, _T('\\')))[1] = 0;

		std::wstring directory = L"";
		for (size_t i = 0; i < MAX_PATH; i++)
		{
			if (szPath[i] == 0)
				break;

			directory += szPath[i];
		}

		return directory;

	}

	std::wstring getFileNameFromAbsoluteExecutionDirectory(std::wstring filename)
	{
		std::wstring path = getAbsoluteExecutionDirectory();
		std::wstring currentFilename = L"";
		while (true)
		{
			currentFilename = path.substr(path.find_last_of('\\') + 1, path.size());

			if (currentFilename.size() <= 0)
			{
				return currentFilename;
			}

			if (currentFilename.compare(filename))
			{
				path += L"\\";
				return path;
			}

			path = path.substr(0, path.find_last_of('\\'));

		}
	}

	void initEditor()
	{
		//Texture* temp = new Texture();

		_currentPath = std::filesystem::current_path().u8string();
		_assetPath = _currentPath + "\\..\\Assets\\";

		// Check that a backend is available
		if (!pfd::settings::available())
		{
			std::cout << "Portable File Dialogs are not available on this platform.\n";
			return;
		}

		// Set verbosity to true
		pfd::settings::verbose(true);

		// Notification
		pfd::notify("Welcome To Use Our Game Engine",
			"Thank you for trying!",
			pfd::icon::info);

		for (size_t i = 0; i < (int)ResourcesTextureIndex::__Index_Size; i++)
		{
			resourcesTexture[i] = new Texture(resourcesTexturePath[i].c_str());
		}

		_screenTexture = new Texture(0.0f, 0.0f);
		
		_screenDepth = new Texture(0.0f, 0.0f);
		glDeleteTextures(1, &_screenDepth->getTextureID());
		System::initDepthBufferTexture(*_screenDepth, 0.0f, 0.0f);
		
		DirectionLight* directionLight = new DirectionLight;
		directionLight->direction = glm::vec3(-0.2f, -1.0f, -0.3f);
		directionLight->ambient = glm::vec3(0.7f, 0.7f, 0.7f);
		directionLight->diffuse = glm::vec3(0.4f, 0.4f, 0.4f);
		directionLight->specular = glm::vec3(0.5f, 0.5f, 0.5f);

		PointLight* pointLight = new PointLight;
		pointLight->position = glm::vec3(0.7f, 0.2f, 2.0f);
		pointLight->constant = 100.0f;
		pointLight->linear = 0.09f;
		pointLight->quadratic = 0.032f;
		pointLight->ambient = glm::vec3(0.05f, 0.05f, 0.05f);
		pointLight->diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
		pointLight->specular = glm::vec3(1.0f, 1.0f, 1.0f);

		_lightingContainer = new LightingContainer(true);
		_lightingContainer->addDirectionLight(directionLight);
		_lightingContainer->addPointLight(pointLight);

	
		_camera = new Camera(glm::vec3(0.0f, 0.0f, -20.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		float w = 0.0f, h = 0.0f;
		float winH = static_cast<float>(Global::wnd->getHeight()), winW = static_cast<float>(Global::wnd->getWidth());
		if (winH < winW)
		{
			w = 0.1f * FOV;
			h = 0.1f * winH / winW * FOV;
		}
		else if (winH > winW)
		{
			w = 0.1f * winW / winH * FOV;
			h = 0.1f * FOV;
		}
		else
		{
			w = 0.1f * FOV;
			h = 0.1f * FOV;
		}


		_camera->setProjectionOrthographic(-w, w, -h, h, 0.1f, 300.0f);

		_worldRenderStyle = (int)WorldRenderStyleType::Diffuse;

		// Finding, Loading, and Assigning entity here from json file
		int loadedSize = 1;
		for (size_t i = 0; i < loadedSize; i++)
		{
			EntityObjectGUI* newEntityObjectGUI = new EntityObjectGUI;

			newEntityObjectGUI->_parent = nullptr;
			newEntityObjectGUI->_child.clear();

			newEntityObjectGUI->_entity = new Entity();
			newEntityObjectGUI->_entity->id = _differentEntityNameIndex;
			newEntityObjectGUI->_entity->name = "New entity " + std::to_string(_differentEntityNameIndex);
			newEntityObjectGUI->_entity->parent = nullptr;
			newEntityObjectGUI->_entity->child.clear();
			newEntityObjectGUI->_entity->transform->setTransform(_camera->transform->getPosition(), glm::vec3(0.0f), glm::vec3(1.0f));
			newEntityObjectGUI->_entity->group = 0;

			newEntityObjectGUI->_material = new Material(resourcesTexture[(int)ResourcesTextureIndex::Glass]);
			newEntityObjectGUI->_geometry = Mesh::DefaultGeometry::SQUARE;
			newEntityObjectGUI->_model = new Model(new Mesh(newEntityObjectGUI->_geometry), newEntityObjectGUI->_material);

			newEntityObjectGUI->visibility = true;

			++_differentEntityNameIndex;

			__editorHierarchyOwn_addEntityObject(newEntityObjectGUI);
		}
		if (loadedSize <= 0)
		{
			__editorHierarchyOwn_addNewEntityObject();
		}

		__editorHierarchyOwn_initSelectedEntityVariable(_entityObjectGUI_List.findData(0));

		__editorAssetTrackerOwn_generateAssetList(_assetPath, resourcesAssetPaths);

	}


	void __editorHierarchyOwn_initSelectedEntityVariable(EntityObjectGUI* entityObjectGUI)
	{
		_selectedEntityObjectGUI = entityObjectGUI;

		strcpy_s(_selectedEntityName_char, _selectedEntityObjectGUI->_entity->name.c_str());
		_selectedEntityName_string.assign(_selectedEntityName_char, 128);
		

		_selectedTranslation = _selectedEntityObjectGUI->_entity->transform->getPosition();
		_selectedRotation = _selectedEntityObjectGUI->_entity->transform->getRotation();
		_selectedDimension = _selectedEntityObjectGUI->_entity->transform->getDimension();
		
		_selectedGeometryType = _selectedEntityObjectGUI->_geometry;
		
		_seletedMaterial = _selectedEntityObjectGUI->_material;

	}

	void __editorHierarchyOwn_addEntityObject(EntityObjectGUI* entityObjectGUIData)
	{
		_entityObjectGUI_List.push_back(entityObjectGUIData);
		
		++_differentEntityNameIndex;
	}

	void __editorHierarchyOwn_addNewEntityObject()
	{
		EntityObjectGUI* newEntityObjectGUI = new EntityObjectGUI;

		newEntityObjectGUI->_parent = nullptr;
		newEntityObjectGUI->_child.clear();

		newEntityObjectGUI->_entity = new Entity();
		newEntityObjectGUI->_entity->id = _differentEntityNameIndex;
		newEntityObjectGUI->_entity->name = "New entity " + std::to_string(_differentEntityNameIndex);
		newEntityObjectGUI->_entity->parent = nullptr;
		newEntityObjectGUI->_entity->child.clear();
		newEntityObjectGUI->_entity->transform->setTransform(_camera->transform->getPosition(), glm::vec3(0.0f), glm::vec3(1.0f));
		newEntityObjectGUI->_entity->group = 0;

		newEntityObjectGUI->_material = new Material(resourcesTexture[(int)ResourcesTextureIndex::Glass]);
		newEntityObjectGUI->_geometry = Mesh::DefaultGeometry::SQUARE;
		newEntityObjectGUI->_model = new Model(new Mesh(newEntityObjectGUI->_geometry), newEntityObjectGUI->_material);
		
		newEntityObjectGUI->visibility = true;


		_entityObjectGUI_List.push_back(newEntityObjectGUI);

		__editorHierarchyOwn_initSelectedEntityVariable(newEntityObjectGUI);

		++_differentEntityNameIndex;

	}

	void __editorHierarchyOwn_deleteEntityObjectFromParent(EntityObjectGUI* entityObjectGUIData)
	{
		EntityObjectGUI* parent = entityObjectGUIData->_parent;
		if (parent == nullptr)
		{
			for (auto iter = _entityObjectGUI_List.begin(); iter != _entityObjectGUI_List.end(); iter++)
			{
				if (*iter == entityObjectGUIData)
				{
					auto temp = *iter;
					iter = _entityObjectGUI_List.erase(iter);
					
					break;
				}
			}
		}
		else
		{
			for (auto iter = parent->_entity->child.begin(); iter != parent->_entity->child.end(); iter++)
			{
				if (*iter == entityObjectGUIData->_entity)
				{
					iter = parent->_entity->child.erase(iter);
					break;
				}
			}
			for (auto iter = parent->_child.begin(); iter != parent->_child.end(); iter++)
			{
				if (*iter == entityObjectGUIData)
				{
					iter = parent->_child.erase(iter);
					break;
				}
			}
			

			entityObjectGUIData->_entity->parent = nullptr;
			entityObjectGUIData->_parent = nullptr;
		}

		for (auto iter = entityObjectGUIData->_child.begin(); iter != entityObjectGUIData->_child.end();)
		{
			auto temp = iter++;
			__editorHierarchyOwn_deleteEntityObjectFromParent(*temp);
		}

	}

	bool __editorHierarchyOwn_switchSelectedToAvailableRelationship(DoubleLinkList<EntityObjectGUI*>& parentEntityObjectGUIList, EntityObjectGUI* entityObjectGUIData, const bool& isNotParent)
	{
		for (auto iter = parentEntityObjectGUIList.begin(); iter != parentEntityObjectGUIList.end(); iter++)
		{
			if (*iter == entityObjectGUIData)
			{
				auto next = iter;
				if (++next != parentEntityObjectGUIList.end())
				{
					__editorHierarchyOwn_initSelectedEntityVariable(*next);
					return true;
				}

				auto prev = iter;
				if (--prev != parentEntityObjectGUIList.end())
				{
					__editorHierarchyOwn_initSelectedEntityVariable(*prev);
					return true;
				}

				if (isNotParent)
				{
					ImGui::OpenPopup("Delete Failed");
					return false;
				}
				
				__editorHierarchyOwn_initSelectedEntityVariable(entityObjectGUIData->_parent);
				return true;

			}
		}
		
	}

	void __editorHierarchyOwn_deleteEntityObject(EntityObjectGUI* entityObjectGUIData)
	{
		EntityObjectGUI* parent = entityObjectGUIData->_parent;
		if (parent == nullptr) 
		{
			if (!__editorHierarchyOwn_switchSelectedToAvailableRelationship(_entityObjectGUI_List, entityObjectGUIData, true)) 
			{
				return;
			}
		}
		else
		{
			__editorHierarchyOwn_switchSelectedToAvailableRelationship(parent->_child, entityObjectGUIData, false);
		}

		__editorHierarchyOwn_deleteEntityObjectFromParent(entityObjectGUIData);

	}

	void __editorHierarchyOwn_setEntityParentObject(EntityObjectGUI* newParent, EntityObjectGUI* child, int& childIndexInOldParent)
	{
		if (child->_parent == newParent) return;

		if (child->_parent == nullptr)
		{
			_entityObjectGUI_List.erase(childIndexInOldParent);
		}
		else
		{
			EntityObjectGUI* oldParent = child->_parent;

			// erase EntityObjectGUI from child of old parant EntityObjectGUI
			oldParent->_child.erase(childIndexInOldParent);

			// erase real Entity from the child of old parant Entity
			for (auto iter = oldParent->_entity->child.begin(); iter != oldParent->_entity->child.end(); iter++)
			{
				const Entity* temp = *iter;
				if (temp == child->_entity)
				{
					iter = oldParent->_entity->child.erase(iter);
					break;
				}
			}
		}

		// push newChild to parent
		if (newParent != nullptr)
		{
			newParent->_child.push_back(child);
			newParent->_entity->child.push_back(child->_entity);

			child->_parent = newParent;
			child->_entity->parent = newParent->_entity;
		}
		else
		{
			_entityObjectGUI_List.push_back(child);

			child->_parent = nullptr;
			child->_entity->parent = nullptr;
		}

	}
	
	bool __editorHierarchyOwn_entityInheritDragDropAction(EntityObjectGUI* entityObjectGUI, int& index)
	{
		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ENTITY_CELL"))
			{
				IM_ASSERT(payload->DataSize == sizeof(int));
				int payload_index = *(const int*)payload->Data;

				__editorHierarchyOwn_setEntityParentObject(entityObjectGUI, _draggingEntityObjectGUI, payload_index);

				_draggingEntityObjectGUI = nullptr;

			}
			ImGui::EndDragDropTarget();
		}
		return false;

	}

	void __editorHierarchyOwn_entityDragDropAction(EntityObjectGUI* entityObjectGUI, int& index)
	{
		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
		{
			// Set payload to carry the index of our item (could be anything)
			ImGui::SetDragDropPayload("ENTITY_CELL", &index, sizeof(int));

			_isDragging = true;
			_draggingEntityObjectGUI = entityObjectGUI;

			// Display preview (could be anything, e.g. when dragging an image we could decide to display
			// the filename and a small preview of the image, etc.)
			ImGui::Text("Move %s", entityObjectGUI->_entity->name.c_str());
			ImGui::EndDragDropSource();

		}

		if (__editorHierarchyOwn_isOneOfChild(_draggingEntityObjectGUI, entityObjectGUI))
		{
			return;
		}

		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ENTITY_CELL"))
			{
				IM_ASSERT(payload->DataSize == sizeof(int));
				int payload_index = *(const int*)payload->Data;

				if (_draggingEntityObjectGUI->_parent == entityObjectGUI->_parent)
				{
					if (_draggingEntityObjectGUI->_parent == nullptr)
					{
						if ((index - payload_index) > 0)
							_entityObjectGUI_List.moveNode(payload_index, index, false);
						else
							_entityObjectGUI_List.moveNode(payload_index, index, true);
					}
					else {
						if ((index - payload_index) > 0)
							entityObjectGUI->_parent->_child.moveNode(payload_index, index, false);
						else
							entityObjectGUI->_parent->_child.moveNode(payload_index, index, true);
					}
				}
				else if (_draggingEntityObjectGUI->_parent != entityObjectGUI->_parent)
				{
					EntityObjectGUI* targetParent = entityObjectGUI->_parent;

					__editorHierarchyOwn_setEntityParentObject(targetParent, _draggingEntityObjectGUI, payload_index);
					
					if(targetParent != nullptr)
						targetParent->_child.moveNode(targetParent->_child.size()-1, index);
					else
						_entityObjectGUI_List.moveNode(_entityObjectGUI_List.size() - 1, index);

				}

				_draggingEntityObjectGUI = nullptr;

			}
			ImGui::EndDragDropTarget();
		}
		

	}

	void __editorHierarchyOwn_defineWithChildSelectedState(EntityObjectGUI* entityObjectGUI, int& index)
	{
		ImGui::PushID(index);
		bool isOpen = ImGui::TreeNodeEx(entityObjectGUI->_entity->name.c_str(), (_selectedEntityObjectGUI == entityObjectGUI) ? (_entityHaveChild_Flags | ImGuiTreeNodeFlags_Selected) : _entityHaveChild_Flags);
		ImGui::PopID();

		if (ImGui::IsItemClicked())
		{
			__editorHierarchyOwn_initSelectedEntityVariable(entityObjectGUI);
		}
		
		__editorHierarchyOwn_entityDragDropAction(entityObjectGUI, index);

		if (isOpen)
		{
			for (int i = 0; i < entityObjectGUI->_child.size(); i++)
			{
				__editorHierarchyOwn_showEntityToList(entityObjectGUI->_child.findData(i), i);
			}
			ImGui::TreePop();
		}
		
	}

	void __editorHierarchyOwn_defineWithoutChildSelectedState(EntityObjectGUI* entityObjectGUI, int& index)
	{
		ImGui::PushID(index);
		bool isOpen = ImGui::TreeNodeEx(entityObjectGUI->_entity->name.c_str(), (_selectedEntityObjectGUI == entityObjectGUI) ? (_entityNullChild_Flags | ImGuiTreeNodeFlags_Selected) : _entityNullChild_Flags);
		ImGui::PopID();

		if (ImGui::IsItemClicked())
		{
			__editorHierarchyOwn_initSelectedEntityVariable(entityObjectGUI);
		}

		__editorHierarchyOwn_entityDragDropAction(entityObjectGUI, index);

		if (isOpen)
		{
			// pressed action here
		}

	}

	bool __editorHierarchyOwn_isOneOfChild(EntityObjectGUI* objectEntityObjectGUI, EntityObjectGUI* targetEntityObjectGUI)
	{
		if (objectEntityObjectGUI == nullptr) return false;

		for (auto iter = objectEntityObjectGUI->_child.begin(); iter != objectEntityObjectGUI->_child.end(); iter++)
		{
			if (*iter == targetEntityObjectGUI)
			{
				return true;
			}
			if (__editorHierarchyOwn_isOneOfChild(*iter, targetEntityObjectGUI))
			{
				return true;
			}
		}

		return false;
	}

	void __editorHierarchyOwn_showEntityToList(EntityObjectGUI* entityObjectGUI, int& index)
	{
		ImGui::Separator();

		ImGui::PushID(entityObjectGUI->_entity->name.c_str() + index);
		ImGui::Checkbox("", &entityObjectGUI->visibility); 
		ImGui::PopID();
		ImGui::SameLine(); ImGui::Spacing(); ImGui::SameLine();
		
		if (_isDragging && ImGui::IsMouseReleased(ImGuiMouseButton_::ImGuiMouseButton_Left))
		{
			_isDragging = false;
		}

		if (ImGui::IsMouseDragging(ImGuiMouseButton_::ImGuiMouseButton_Left) && _isDragging && (_draggingEntityObjectGUI != entityObjectGUI))
		{
			
			if (!__editorHierarchyOwn_isOneOfChild(_draggingEntityObjectGUI, entityObjectGUI))
			{
				ImGui::Selectable("P >", false, ImGuiSelectableFlags_::ImGuiSelectableFlags_None, ImVec2(18.0f, 0.0f));
				__editorHierarchyOwn_entityInheritDragDropAction(entityObjectGUI, index);
				ImGui::SameLine();
			}
			else
			{
				ImGui::Selectable("", false, ImGuiSelectableFlags_::ImGuiSelectableFlags_Disabled, ImVec2(18.0f, 0.0f));
				//__editorHierarchyOwn_InheritDragDropAction(entityObjectGUI, index, inheritCount);
				ImGui::SameLine();
			}

		}
		else
		{
			ImGui::Selectable("", false, ImGuiSelectableFlags_::ImGuiSelectableFlags_Disabled, ImVec2(18.0f, 0.0f));
			if (_draggingEntityObjectGUI != entityObjectGUI) 
			{
				__editorHierarchyOwn_entityInheritDragDropAction(entityObjectGUI, index);
			}
			ImGui::SameLine();
		}

		if (entityObjectGUI->_child.size() != 0)
		{
			__editorHierarchyOwn_defineWithChildSelectedState(entityObjectGUI, index);
		}
		else
		{
			__editorHierarchyOwn_defineWithoutChildSelectedState(entityObjectGUI, index);
		}

		//ImGui::Text("%s", ImGui::IsItemClicked() ? "true" : "false"); ImGui::SameLine();

	}

	void __editorHierarchyOwn_filterEntityName(EntityObjectGUI* entityObjectGUI, int& index)
	{
		if (_filterHierarchy.PassFilter(entityObjectGUI->_entity->name.c_str()))
		{
			__editorHierarchyOwn_showEntityToList(entityObjectGUI, index);
		}
	}

	void __editorHierarchyOwn_generateEntityWindow()
	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_::ImGuiWindowFlags_MenuBar;// | ImGuiWindowFlags_::ImGuiWindowFlags_NoScrollbar;
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::BeginChild("Entity", ImVec2(-FLT_MIN, -FLT_MIN), true, window_flags);
		{
			if (ImGui::BeginMenuBar())
			{
				ImGui::Text("Entities Hierarchy");
				ImGui::EndMenuBar();
			}

			// Always center this window when appearing
			ImVec2 center = ImGui::GetMainViewport()->GetCenter();
			ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
			if (ImGui::BeginPopupModal("Delete Failed", NULL, ImGuiWindowFlags_AlwaysAutoResize))
			{
				ImGui::Text("The scene must at least have one Entity!!\n\n");
				ImGui::NewLine();
				ImGui::NewLine();
				ImGui::Separator();

				ImGui::Spacing();
				ImGui::SameLine(ImGui::GetContentRegionAvailWidth() - 120);
				if (ImGui::Button("OK", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
				ImGui::SetItemDefaultFocus();
				ImGui::EndPopup();
			}

			if (ImGui::IsKeyPressed(GLFW_KEY_DELETE, false) && !_isDragging)
			{
				__editorHierarchyOwn_deleteEntityObject(_selectedEntityObjectGUI);
			}

			for (int i = 0; i < _entityObjectGUI_List.size(); i++)
			{
				__editorHierarchyOwn_filterEntityName(_entityObjectGUI_List.findData(i), i);
			}

		}
		ImGui::EndChild();
		ImGui::PopStyleVar();
	}

	void showEditor_Hierarchy()
	{
		if (ImGui::Begin("Hierarchy"))
		{
			ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.7f, 0.6f, 0.6f));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.8f, 0.7f, 0.7f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.9f, 0.8f, 0.8f));
			if (ImGui::Button("+ Add New "))
			{
				__editorHierarchyOwn_addNewEntityObject();
			}
			ImGui::SameLine();
			ImGui::PopStyleColor(3);

			_filterHierarchy.Draw();

			ImGui::Separator();

			__editorHierarchyOwn_generateEntityWindow();

		}
		ImGui::End();


	}

	void __editorPropertyOwn_saveCursorPosition(const int& boolean, const int& booleanInTyping)
	{
		static double mousePosX = 0.0f, mousePosY = 0.0f;
		static int booleanState = 0;

		if ((booleanState & boolean) > 0)
		{
			if ((booleanState & booleanInTyping) == 0)
			{
				if (ImGui::IsItemActive() && ImGui::IsMouseReleased(ImGuiMouseButton_::ImGuiMouseButton_Left))
				{
					booleanState |= booleanInTyping;
				}
			}
			else if (!ImGui::IsItemActive())
			{
				booleanState -= boolean;
				booleanState -= booleanInTyping;
				mousePosX = mousePosY = 0.0f;
			}
			else
				return;
		}


		if (ImGui::IsItemActive())
		{
			if ((booleanState & boolean) == 0)
				booleanState |= boolean;

			if (mousePosX == 0.0f && mousePosY == 0.0f)
			{
				mousePosX = ImGui::GetMousePos().x;
				mousePosY = ImGui::GetMousePos().y;
			}
			ImGui::SetMouseCursor(ImGuiMouseCursor_::ImGuiMouseCursor_None);
		}
		else if (mousePosX != 0.0f && mousePosY != 0.0f && (booleanState & boolean) > 0)
		{
			booleanState -= boolean;

			glfwSetCursorPos(Global::wnd->getWindow(), mousePosX, mousePosY);
			mousePosX = mousePosY = 0.0f;
		}
	}

	void __editorPropertyOwn_transformComponent()
	{
		ImGui::Columns(1, NULL, false);

		ImGui::BeginChild("Transform Component", ImVec2(-FLT_MIN, 150.0f), true, ImGuiWindowFlags_::ImGuiWindowFlags_MenuBar);
		{
			if (ImGui::BeginMenuBar())
			{
				ImGui::Text("Transform Component");
				ImGui::EndMenuBar();
			}

			const float eachNextPosX = ImGui::GetCursorPosX() + ((ImGui::GetColumnWidth() / 80.0f) * 17.6f - ImGui::CalcTextSize("X").x) - ImGui::GetScrollX() * ImGui::GetStyle().ItemSpacing.x;
			const float eachHalfPosX = ImGui::GetCursorPosX() + ((ImGui::GetColumnWidth() / 80.0f) * 17.6f - ImGui::CalcTextSize("X").x) / 2.0f - ImGui::GetScrollX() * ImGui::GetStyle().ItemSpacing.x;

			ImGui::SetCursorPosX(eachHalfPosX);
			ImGui::Text("X");
			ImGui::SameLine();

			ImGui::SetCursorPosX(eachNextPosX + eachHalfPosX);
			ImGui::Text("Y");
			ImGui::SameLine();

			ImGui::SetCursorPosX(eachNextPosX + eachNextPosX + eachHalfPosX);
			ImGui::Text("Z");
			ImGui::SameLine();

			ImGui::Separator();

			#define positionBoolean 1 << 0
			#define rotationBoolean 1 << 1
			#define scaleBoolean 1 << 2
			#define positionInTypingBoolean 1 << 3
			#define rotationInTypingBoolean 1 << 4
			#define scaleInTypingBoolean 1 << 5

			if (ImGui::DragFloat3("Position", glm::value_ptr(_selectedTranslation), 0.01f, -FLT_MIN, -FLT_MIN, "%.3f")) {

				_selectedEntityObjectGUI->_entity->transform->setPosition(_selectedTranslation);
			}
			//__editorPropertyOwn_saveCursorPosition(positionBoolean, positionInTypingBoolean);

			if (ImGui::DragFloat3("Rotation", glm::value_ptr(_selectedRotation), 0.025f, -FLT_MIN, -FLT_MIN, "%.3f")) {
				_selectedRotation.x = glm::mod<float>(_selectedRotation.x, 360.0f);
				_selectedRotation.y = glm::mod<float>(_selectedRotation.y, 360.0f);
				_selectedRotation.z = glm::mod<float>(_selectedRotation.z, 360.0f);

				_selectedEntityObjectGUI->_entity->transform->setRotation(_selectedRotation);
			}
			//__editorPropertyOwn_saveCursorPosition(rotationBoolean, rotationInTypingBoolean);

			if (ImGui::DragFloat3("Dimension", glm::value_ptr(_selectedDimension), 0.01f, -FLT_MIN, -FLT_MIN, "%.3f")) {

				_selectedEntityObjectGUI->_entity->transform->setDimension(_selectedDimension);
			}
			//__editorPropertyOwn_saveCursorPosition(scaleBoolean, scaleInTypingBoolean);

		}
		ImGui::EndChild();

	}

	void __editorPropertyOwn_meshComponent()
	{
		ImGui::Columns(1, NULL, false);

		ImGui::BeginChild("Material Component", ImVec2(-FLT_MIN, 120.0f), true, ImGuiWindowFlags_::ImGuiWindowFlags_MenuBar);
		{
			if (ImGui::BeginMenuBar())
			{
				ImGui::Text("Material Component");
				ImGui::EndMenuBar();
			}

			if (_selectedEntityObjectGUI->_model->getMesh().size() > 1)
			{
				_selectedEntityObjectGUI->_model->getMesh().resize(1);
				_selectedEntityObjectGUI->_model->getMaterials().resize(1);
				_selectedEntityObjectGUI->_model->getMesh()[0]->setGeometryType(_selectedEntityObjectGUI->_geometry);
				_selectedEntityObjectGUI->_model->getMaterials()[0]->setTexture(Material::PhongTextureType::DIFFUSE, resourcesTexture[(int)_selectedGeometryType]);
				_selectedEntityObjectGUI->_model->getMaterials()[0]->setTexture(Material::PhongTextureType::SPECULAR, resourcesTexture[(int)ResourcesTextureIndex::None]);
				_selectedEntityObjectGUI->_model->getMaterials()[0]->setTexture(Material::PhongTextureType::EMISSION, resourcesTexture[(int)ResourcesTextureIndex::None]);
			}

			if (ImGui::BeginCombo("Mesh", _geometryTypesName[static_cast<int>(_selectedGeometryType)]))
			{
				for (int type = 0; type < IM_ARRAYSIZE(_geometryTypesName); type++)
				{
					const bool is_selected = (_selectedGeometryType == static_cast<Mesh::DefaultGeometry>(type));

					if (ImGui::Selectable(_geometryTypesName[type], is_selected))
					{
						if (_selectedGeometryType != static_cast<Mesh::DefaultGeometry>(type))
						{
							// Switch mesh
							_selectedEntityObjectGUI->_model->getMesh()[0]->setGeometryType(_selectedEntityObjectGUI->_geometry = static_cast<Mesh::DefaultGeometry>(type));

						}

						_selectedGeometryType = static_cast<Mesh::DefaultGeometry>(type);

					}

					// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
					if (is_selected)
						ImGui::SetItemDefaultFocus();

				}

				ImGui::EndCombo();
			}

			ImGui::Dummy(ImVec2(-FLT_MIN, 1.0f));

			if (ImGui::BeginCombo("Texture", resourcesTexturePath[_selectedTextureIndex].c_str()))
			{
				for (int i = 0; i < IM_ARRAYSIZE(resourcesTexturePath); i++)
				{
					const bool is_selected = (i == _selectedTextureIndex);

					if (ImGui::Selectable(resourcesTexturePath[i].c_str(), is_selected))
					{
						if (_selectedTextureIndex != i)
						{
							// Switch mesh
							_selectedEntityObjectGUI->_material->textures[(int)Material::PhongTextureType::DIFFUSE] = resourcesTexture[i];

						}

						_selectedTextureIndex = i;

					}

					// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
					if (is_selected)
						ImGui::SetItemDefaultFocus();

				}

				ImGui::EndCombo();
			}


			/*
			// Dummy
			ImVec2 button_sz(40, 40);
			//mGui::Button("A", button_sz); ImGui::SameLine();
			//ImGui::Dummy(button_sz); ImGui::SameLine();
			//ImGui::Button("B", button_sz);

			ImGui::Text("Textures:");
			ImGuiStyle& style = ImGui::GetStyle();
			int buttons_count = 20;
			float window_visible_x2 = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;
			for (int n = 0; n < buttons_count; n++)
			{
				ImGui::PushID(n);
				ImGui::Button("Box", button_sz);
				float last_button_x2 = ImGui::GetItemRectMax().x;
				float next_button_x2 = last_button_x2 + style.ItemSpacing.x + button_sz.x; // Expected position if next button was on same line
				if (n + 1 < buttons_count && next_button_x2 < window_visible_x2)
					ImGui::SameLine();
				ImGui::PopID();
			}
			*/

		}

		ImGui::EndChild();

	}
	static AssetInfo* _draggingAsset;
	static AssetInfo* assetInfo = nullptr;
	void __editorPropertyOwn_propertyDropModelAssetCellAction()
	{
		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(assetDragDropCell[(int)AssetInfo::AssetType_Model].c_str()))
			{
				//IM_ASSERT(payload->DataSize == sizeof(AssetInfo));
				//AssetInfo* payload_index = (AssetInfo*)payload->Data;
				
				assetInfo = _draggingAsset;
				std::string path = assetInfo->path.substr(_currentPath.size() + 1);
				System::loadModel(path.c_str(), _selectedEntityObjectGUI->_model->getMesh(), _selectedEntityObjectGUI->_model->getMaterials());
				_seletedMaterial = _selectedEntityObjectGUI->_material = _selectedEntityObjectGUI->_model->getMaterials()[0];
			}
			ImGui::EndDragDropTarget();
		}
	}

	void __editorPropertyOwn_propertyDropTextureAssetCellAction(Material::PhongTextureType phongTextureTypeIndex)
	{
		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(assetDragDropCell[(int)AssetInfo::AssetType_Texture].c_str()))
			{
				//IM_ASSERT(payload->DataSize == sizeof(AssetInfo));
				//AssetInfo* payload_index = (AssetInfo*)payload->Data;

				std::string path = _draggingAsset->path.substr(_currentPath.size() + 1);
				_seletedMaterial->textures[(int)phongTextureTypeIndex] = new Texture(path.c_str());
				//printf(path.c_str());

			}
			ImGui::EndDragDropTarget();
		}
	}

	void __editorPropertyOwn_modelComponent()
	{
		ImGui::Columns(1, NULL, false);

		ImGui::BeginChild("Material Component", ImVec2(-FLT_MIN, 120.0f), true, ImGuiWindowFlags_::ImGuiWindowFlags_MenuBar);
		{
			if (ImGui::BeginMenuBar())
			{
				ImGui::Text("Material Component");
				ImGui::EndMenuBar();
			}

			if(assetInfo != nullptr)
				ImGui::Selectable(("Model - " + assetInfo->name).c_str());
			else
				ImGui::Selectable("Model - [NONE]");
			__editorPropertyOwn_propertyDropModelAssetCellAction();

			ImGui::Selectable(("Texture Diffuse : " + _seletedMaterial->textures[(int)Material::PhongTextureType::DIFFUSE]->getPath()).c_str());
			__editorPropertyOwn_propertyDropTextureAssetCellAction(Material::PhongTextureType::DIFFUSE);

			ImGui::Selectable(("Texture Specular : " + _seletedMaterial->textures[(int)Material::PhongTextureType::SPECULAR]->getPath()).c_str());
			__editorPropertyOwn_propertyDropTextureAssetCellAction(Material::PhongTextureType::SPECULAR);

			ImGui::Selectable(("Texture Emission : " + _seletedMaterial->textures[(int)Material::PhongTextureType::EMISSION]->getPath()).c_str());
			__editorPropertyOwn_propertyDropTextureAssetCellAction(Material::PhongTextureType::EMISSION);

		}

		ImGui::EndChild();

	}

	void showEditor_Property()
	{
		if (ImGui::Begin("Property"))
		{
			ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(255, 155, 255, 50)); //For visibility
			ImGui::BeginChild("Entity Identity", ImVec2(0, 100.0f), true, ImGuiWindowFlags_::ImGuiWindowFlags_MenuBar);
			{
				if (ImGui::BeginMenuBar())
				{
					ImGui::Text("Entity Identity");
					ImGui::EndMenuBar();
				}


				//ImGui::Text("Name   : ");
				//ImGui::SameLine();

				//static char buf[32] = u8"NIHONGO"; // <- this is how you would write it with C++11, using real kanjis
				if (ImGui::InputText(" : Entity Name", _selectedEntityName_char, 128))
				{
					_selectedEntityName_string = "";
					for (size_t i = 0; i < 128; i++)
					{
						if (_selectedEntityName_char[i] == 0)
							break;

						_selectedEntityName_string += _selectedEntityName_char[i];
					}
					
				}

				

				if (!ImGui::IsItemActive() && _selectedEntityName_string != _selectedEntityObjectGUI->_entity->name)
				{
					if (_selectedEntityName_string == "")
					{
						strcpy_s(_selectedEntityName_char, _selectedEntityObjectGUI->_entity->name.c_str());
						_selectedEntityName_string = _selectedEntityObjectGUI->_entity->name;
					}
					else
					{
						_selectedEntityObjectGUI->_entity->name = _selectedEntityName_string;
					}
					
				}

			}
			ImGui::EndChild();
			ImGui::PopStyleColor();


			ImGui::Spacing(); ImGui::Spacing();
			ImGui::Separator();
			ImGui::Spacing();


			ImGui::BeginChild("Editor", ImVec2(-FLT_MIN, -FLT_MIN), true);
			{
				__editorPropertyOwn_transformComponent();
				static int meshType = 0;

				ImGui::RadioButton("Default Geometry", &meshType, 0);
				ImGui::RadioButton("Model", &meshType, 1);

				if(meshType == 0)
					__editorPropertyOwn_meshComponent();
				else if(meshType == 1)
					__editorPropertyOwn_modelComponent();
			}
			ImGui::EndChild();

		}
		ImGui::End();

	}

	void __editorWorldEditorOwn_renderEntity(EntityObjectGUI* entityObjectGUI)
	{
		if (entityObjectGUI->visibility)
		{
			glm::mat4 mat = _camera->getProjectionMatrix() * _camera->getViewMatrix() * entityObjectGUI->_entity->transform->getModelMatrix();
			//Shader::defaultDraw(mat);

			for (size_t i = 0; i < entityObjectGUI->_model->getMesh().size(); i++)
			{
				Shader::phongLightDraw(entityObjectGUI->_entity->transform->getModelMatrix(), _camera->getViewMatrix(), _camera->getProjectionMatrix(), *entityObjectGUI->_model->getMaterials()[i], *_lightingContainer);

				glBindVertexArray(entityObjectGUI->_model->getMesh()[i]->getVertexArrayObject()->vaoID);
				glDrawElements(GL_TRIANGLES, entityObjectGUI->_model->getMesh()[i]->getVertexArrayObject()->indicesSize, GL_UNSIGNED_INT, 0);

			}

			for (size_t i = 0; i < entityObjectGUI->_child.size(); i++)
			{
				EntityObjectGUI* temp = entityObjectGUI->_child.findData(i);
				__editorWorldEditorOwn_renderEntity(temp);
			}

		}

	}

	void __editorWorldEditorOwn_renderScreen(ImVec2& size)
	{
		static GLuint fb_tex = 0;
		if (fb_tex == 0) // init framebuffer
		{
			glEnable(GL_DEPTH_TEST);
			//glEnable(GL_CULL_FACE);
			glGenFramebuffers(1, &fb_tex);
		}

		

		switch ((WorldRenderStyleType)_worldRenderStyle)
		{
		case WorldRenderStyleType::Diffuse:
			glDisable(GL_POLYGON_OFFSET_LINE);
			glDisable(GL_LINE_SMOOTH);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			break;

		case WorldRenderStyleType::Polygon:
			glPolygonOffset(-1.0f, -1.0f);
			glEnable(GL_POLYGON_OFFSET_LINE);
			glEnable(GL_LINE_SMOOTH);

			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glLineWidth(2.5f);
			break;

		case WorldRenderStyleType::Point:
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
			glPointSize(5.0f);
			break;

		case WorldRenderStyleType::Lighting:
			break;
		}

		glBindFramebuffer(GL_FRAMEBUFFER, fb_tex);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _screenTexture->getTextureID(), 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _screenDepth->getTextureID(), 0);
		// Graphics renderer
		if (glCheckFramebufferStatus(fb_tex))
		{
			glViewport(0, 0, static_cast<int>(size.x), static_cast<int>(size.y));
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			
			for (size_t i = 0; i < _entityObjectGUI_List.size(); i++)
			{
				EntityObjectGUI* temp = _entityObjectGUI_List.findData(i);
				
				__editorWorldEditorOwn_renderEntity(temp);

			}

		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void showEditor_WorldEditor()
	{
		//Transform* tempTran = _entityObjectGUI_List.findData(0)->_entity.transform;
		//glm::vec3 tempRot;
		//tempRot.x = tempTran->getRotationLocal().x;
		//tempRot.y = tempTran->getRotationLocal().y + 0.1f;
		//tempRot.z = tempTran->getRotationLocal().z;

		//tempTran->setRotationLocal(tempRot);
		//_selectedRotation = tempRot;

		if (ImGui::Begin("WorldEditor"))
		{
			static ImVec2 size;
			size.x = ImGui::GetContentRegionAvail().x;
			size.y = ImGui::GetContentRegionAvail().y;

			if (_screenTexture->getWidth() != size.x || _screenTexture->getHeight() != size.y)
			{
				_screenTexture->setSize(size.x, size.y);
				_screenDepth->setSize(size.x, size.y);

				float w = 0.0f, h = 0.0f;
				float winH = static_cast<float>(size.y), winW = static_cast<float>(size.x);
				if (winH < winW)
				{
					w = 0.1f * FOV;
					h = 0.1f * winH / winW * FOV;
				}
				else if (winH > winW)
				{
					w = 0.1f * winW / winH * FOV;
					h = 0.1f * FOV;
				}
				else
				{
					w = 0.1f * FOV;
					h = 0.1f * FOV;
				}
				_camera->setProjectionOrthographic(-w, w, -h, h, 0.1f, 300.0f);
				//_camera->setProjectionPerspective(FOV, winW / winH, 0.1f, 300.0f);

			}

			__editorWorldEditorOwn_renderScreen(size);

			ImGui::RadioButton("Diffuse", &_worldRenderStyle, static_cast<int>(WorldRenderStyleType::Diffuse)); ImGui::SameLine();
			ImGui::RadioButton("Polygon", &_worldRenderStyle, static_cast<int>(WorldRenderStyleType::Polygon)); ImGui::SameLine();
			ImGui::RadioButton("Point", &_worldRenderStyle, static_cast<int>(WorldRenderStyleType::Point));
			/*
			if (ImGui::ImageButton((void*)(intptr_t)resourcesTexture[(int)ResourcesTextureIndex::Box]->getTextureID(), ImVec2(30.0f, 30.0f)))
			{
				_worldRenderStyle = (int)WorldRenderStyleType::Diffuse;
			}
			ImGui::SameLine();
			if (ImGui::ImageButton((void*)(intptr_t)resourcesTexture[(int)ResourcesTextureIndex::Box]->getTextureID(), ImVec2(30.0f, 30.0f)))
			{
				_worldRenderStyle = (int)WorldRenderStyleType::Polygon;
			}
			ImGui::SameLine();
			if (ImGui::ImageButton((void*)(intptr_t)resourcesTexture[(int)ResourcesTextureIndex::Box]->getTextureID(), ImVec2(30.0f, 30.0f)))
			{
				_worldRenderStyle = (int)WorldRenderStyleType::Point;
			}
			ImGui::Dummy(ImVec2(20.0f, 20.0f));
			*/

			//ImGui::SetWindowSize(ImVec2(size.x + 15, size.y + 35));
			//ImGui::GetCursorPosX() + ((ImGui::GetColumnWidth() / 80.0f) * 17.6f - ImGui::CalcTextSize("X").x) - ImGui::GetScrollX() * ImGui::GetStyle().ItemSpacing.x;
			ImGui::Image((void*)(intptr_t)_screenTexture->getTextureID(), ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), ImVec2(0, 1), ImVec2(1, 0));

		}
		ImGui::End();

	}

	void testing()
	{
		// Check that a backend is available
		if (!pfd::settings::available())
		{
			std::cout << "Portable File Dialogs are not available on this platform.\n";
			return;
		}

		// Set verbosity to true
		pfd::settings::verbose(true);

		// Notification
		pfd::notify("Important Notification",
			"This is ' a message, pay \" attention \\ to it!",
			pfd::icon::info);

		// Message box with nice message
		auto m = pfd::message("Personal Message",
			"You are an amazing person, don’t let anyone make you think otherwise.",
			pfd::choice::yes_no_cancel,
			pfd::icon::warning);

		// Optional: do something while waiting for user action
		for (int i = 0; i < 10 && !m.ready(1000); ++i)
			std::cout << "Waited 1 second for user input...\n";

		// Do something according to the selected button
		switch (m.result())
		{
		case pfd::button::yes: std::cout << "User agreed.\n"; break;
		case pfd::button::no: std::cout << "User disagreed.\n"; break;
		case pfd::button::cancel: std::cout << "User freaked out.\n"; break;
		default: break; // Should not happen
		}

		// Directory selection
		auto dir = pfd::select_folder("Select any directory", "C:\\").result();
		std::cout << "Selected dir: " << dir << "\n";

		// File open
		/*
		auto f = pfd::open_file("Choose files to read", "C:\\",
			{ "Text Files (.txt .text)", "*.txt *.text",
			  "All Files", "*" },
			pfd::opt::multiselect);
		*/
		auto f = pfd::open_file("Choose files to read", "C:\\",
			{ "All Files", "*" },
			pfd::opt::force_path);
		std::cout << "Selected files:";
		for (auto const& name : f.result())
			std::cout << " " + name;
		std::cout << "\n";
	}

	void testing2()
	{
		// Set verbosity to true
		pfd::settings::verbose(true);

		// Message box with nice message
		auto m = pfd::message("Upgrade software?",
			"Press OK to upgrade this software.\n"
			"\n"
			"By default, the software will update itself\n"
			"automatically in 10 seconds.",
			pfd::choice::ok_cancel,
			pfd::icon::warning);

		// Wait for an answer for up to 10 seconds
		for (int i = 0; i < 10 && !m.ready(1000); ++i)
			;

		// Upgrade software if user clicked OK, or if user didn’t interact
		bool upgrade = m.ready() ? m.result() == pfd::button::ok : m.kill();
		if (upgrade)
			std::cout << "Upgrading software!\n";
		else
			std::cout << "Not upgrading software.\n";
		
	}
	
	void __editorAssetTrackerOwn_assetDragDropAction(AssetInfo& assetInfo)
	{
		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
		{
			// Set payload to carry the index of our item (could be anything)
			
			ImGui::SetDragDropPayload(assetDragDropCell[(int)assetInfo.assetType].c_str(), &assetInfo, sizeof(AssetInfo));

			_draggingAsset = &assetInfo;

			// Display preview (could be anything, e.g. when dragging an image we could decide to display
			// the filename and a small preview of the image, etc.)
			ImGui::Text("Move %s", 
				("[" + assetDragDropCell[(int)assetInfo.assetType] + "]" + assetInfo.name).c_str());
			ImGui::EndDragDropSource();

		}

		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ASSET_TEXTURE_CELL"))
			{
				IM_ASSERT(payload->DataSize == sizeof(AssetInfo));
				AssetInfo* payload_index = (AssetInfo*)payload->Data;

			}
			ImGui::EndDragDropTarget();
		}


	}

	void __editorAssetTrackerOwn_generateAssetList(const std::string& folderDir, std::vector<AssetInfo>& currentAseetList)
	{
		currentAseetList.clear();

		DIR* dir;
		struct dirent* ent;
		
		if ((dir = opendir(folderDir.c_str())) != NULL) {

			int i = 0;

			// print all the files and directories within directory
			while ((ent = readdir(dir)) != NULL) {

				if (i < 2) 
				{
					i++;
					continue;
				}

				//printf("%s\n", ent->d_name);
				std::string name(ent->d_name);
				size_t loc = name.find_last_of(".");

				if (loc != std::string::npos)
				{
					AssetInfo info;
					info.name = ent->d_name;
					info.path = folderDir + info.name;
					info.assetType = checkFileType(name.substr(loc));
					info.subdirectoriesAssetPaths.clear();
					
					currentAseetList.push_back(info);
				}
				else 
				{
					AssetInfo info;
					info.name = ent->d_name;
					info.path = folderDir + info.name + "\\";
					info.assetType = AssetInfo::AssetType_Folder;
					__editorAssetTrackerOwn_generateAssetList(info.path, info.subdirectoriesAssetPaths);

					currentAseetList.push_back(info);
				}
			}
			closedir(dir);
		}
		else {
			// could not open directory
			perror("");
			return;
		}
	}

	bool __editorAssetTrackerOwn_checkfolderSubdirectoriesIsInFilter(AssetInfo& assetInfo)
	{
		bool showParent = _filterAssetTracker.PassFilter(assetInfo.name.c_str());

		for (auto iter = assetInfo.subdirectoriesAssetPaths.begin(); iter != assetInfo.subdirectoriesAssetPaths.end(); iter++)
		{
			if (__editorAssetTrackerOwn_checkfolderSubdirectoriesIsInFilter(*iter))
			{
				showParent = true;
			}
		}

		return showParent;

	}

	void __editorAssetTrackerOwn_showAssetList(std::vector<AssetInfo>& currentAseetList)
	{
		
		for (size_t i = 0; i < currentAseetList.size(); i++)
		{
			if (!__editorAssetTrackerOwn_checkfolderSubdirectoriesIsInFilter(currentAseetList[i])) continue;

			switch (currentAseetList[i].assetType) {
			case AssetInfo::AssetType::AssetType_Unknown:
				ImGui::Text("[Unknown]       : ");
				break;

			case AssetInfo::AssetType::AssetType_Texture:
				ImGui::Text("[Texture]       : ");
				break;

			case AssetInfo::AssetType::AssetType_TextDocument:
				ImGui::Text("[Text Document] : ");
				break;

			case AssetInfo::AssetType::AssetType_Shader:
				ImGui::Text("[Shader]        : ");
				break;

			case AssetInfo::AssetType::AssetType_Model:
				ImGui::Text("[Model]         : ");
				break;

			case AssetInfo::AssetType::AssetType_Font:
				ImGui::Text("[Font]          : ");
				break;

			case AssetInfo::AssetType::AssetType_Folder:
				ImGui::Text("[Folder]        : ");
				break;

			case AssetInfo::AssetType::AssetType_Audio:
				ImGui::Text("[Audio]         : ");
				break;

			}
			ImGui::SameLine();
			if(ImGui::IsKeyDown(GLFW_KEY_P) && ImGui::IsWindowHovered())
				ImGui::Selectable(currentAseetList[i].path.c_str());
			else
				ImGui::Selectable(currentAseetList[i].name.c_str());

			__editorAssetTrackerOwn_assetDragDropAction(currentAseetList[i]);
			
			ImGui::Indent();
			__editorAssetTrackerOwn_showAssetList(currentAseetList[i].subdirectoriesAssetPaths);
			ImGui::Unindent();
		}
	}

	void showEditor_AssetTracker()
	{
		if (ImGui::Begin("AssetTracker"))
		{
			if (ImGui::Button("Refresh"))
			{
				//auto f = pfd::open_file("Choose files to read", _currentPath.c_str(), { "All Files", "*" }, pfd::opt::force_path);
				//testing();
				//testing2();
				__editorAssetTrackerOwn_generateAssetList(_assetPath, resourcesAssetPaths);
			}
			ImGui::SameLine();
			_filterAssetTracker.Draw();

			ImGuiWindowFlags window_flags = ImGuiWindowFlags_::ImGuiWindowFlags_MenuBar;// | ImGuiWindowFlags_::ImGuiWindowFlags_NoScrollbar;
			ImGui::BeginChild("Asset File", ImVec2(-FLT_MIN, -FLT_MIN), true, window_flags);
			{
				if (ImGui::BeginMenuBar())
				{
					ImGui::Text("Assets");
					ImGui::EndMenuBar();
				}

				__editorAssetTrackerOwn_showAssetList(resourcesAssetPaths);
			
			}
			ImGui::EndChild();
		}
		ImGui::End();
	}

	void terminateEditor()
	{
		_selectedEntityObjectGUI = nullptr;
		_entityObjectGUI_List.clear();

		delete _screenTexture;
		delete _screenDepth;

		delete _camera;
	}

}
