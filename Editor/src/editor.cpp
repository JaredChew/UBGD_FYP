#include "editor.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Manipulators/geometry.h"
#include "Compound/mesh.h"
#include "Compound/texture.h"
#include "Specification/entity.h"
#include "Compound/transform.h"
#include "Manipulators/shader.h"
#include "Manipulators/system.h"
#include "Modules BackEnd/camera.h"
#include "Modules BackEnd/window.h"
#include "Compound/VertexArrayObject.h"

#include "global.h"
#include "defaultSettings.h"
#include "doubleLinkList.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


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

// End Resource Manager Item  ------






namespace Editor {

	// Editor Manager Item Start   ++++++

	struct EntityObjectGUI {

		Entity _entity;
		Mesh* _mesh;
		Texture* _texture;

		bool visibility;

	};

	DoubleLinkList<EntityObjectGUI*> _entityObjectGUI;

	ImGuiTextFilter _filter;

	ImGuiTreeNodeFlags _entityHaveChild_Flags = ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_SpanAvailWidth;
	ImGuiTreeNodeFlags _entityNullChild_Flags = ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_NoTreePushOnOpen;



	EntityObjectGUI* _selectedEntityObjectGUI;

	std::vector<char> _selectedEntityName;

	glm::vec3 _selectedTranslation;
	glm::vec3 _selectedRotation;
	glm::vec3 _selectedDimension;

	const char* _geometryTypesName[] = { "TRIANGLE", "SQUARE", "CIRCLE", "STADIUM", "PYRAMID", "CUBE", "SPHERE", "CONE", "CYLINDER" };
	Mesh::DefaultGeometry _selectedGeometryType;

	int _selectedTextureIndex;

	Texture* _screenTexture;
	Texture* _screenDepth;

	Camera* _camera;

	enum class WorldRenderStyleType : int { Diffuse = 0, Polygon, Point, Lighting };
	int _worldRenderStyle;

	unsigned int _differentEntityNameIndex = 0;

	// End Editor Manager Item  ------



	void __editorHierarchyOwn_addEntityObject(EntityObjectGUI* entityObjectGUIData);
	void __editorHierarchyOwn_addNewEntityObject();
	void __editorHierarchyOwn_initSelectedEntityVariable(EntityObjectGUI* entityObjectGUI);

	void initEditor()
	{
		for (size_t i = 0; i < (int)ResourcesTextureIndex::__Index_Size; i++)
		{
			resourcesTexture[i] = new Texture(resourcesTexturePath[i].c_str());
		}

		_screenTexture = new Texture(0.0f, 0.0f);
		
		_screenDepth = new Texture(0.0f, 0.0f);
		glDeleteTextures(1, &_screenDepth->getTextureID());
		System::initDepthBufferTexture(*_screenDepth, 0.0f, 0.0f);
		
		// Finding, Loading, and Assigning entity here from json file
		int loadedSize = 1;
		for (size_t i = 0; i < loadedSize; i++)
		{
			EntityObjectGUI* loadedEntity = new EntityObjectGUI;
			loadedEntity->_entity.name = "Current entity";
			loadedEntity->visibility = true;
			loadedEntity->_mesh = new Mesh(Mesh::DefaultGeometry::SQUARE);
			loadedEntity->_texture = resourcesTexture[(int)ResourcesTextureIndex::None];
			loadedEntity->_entity.child.clear();
			loadedEntity->_entity.parent = nullptr;
			__editorHierarchyOwn_addEntityObject(loadedEntity);
		}
		if (loadedSize <= 0)
		{
			__editorHierarchyOwn_addNewEntityObject();
		}

		__editorHierarchyOwn_initSelectedEntityVariable(_entityObjectGUI.findData(0));

	
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

	}


	void __editorHierarchyOwn_initSelectedEntityVariable(EntityObjectGUI* entityObjectGUI)
	{
		_selectedEntityObjectGUI = entityObjectGUI;

		_selectedEntityName = std::vector<char>(_selectedEntityObjectGUI->_entity.name.begin(), _selectedEntityObjectGUI->_entity.name.end());
		_selectedEntityName.resize(128);

		_selectedTranslation = _selectedEntityObjectGUI->_entity.transform->getPosition();
		_selectedRotation = _selectedEntityObjectGUI->_entity.transform->getRotation();
		_selectedDimension = _selectedEntityObjectGUI->_entity.transform->getDimension();
		
		_selectedGeometryType = _selectedEntityObjectGUI->_mesh->getGeometryType();
		
		for (int i = 0; i < (int)ResourcesTextureIndex::__Index_Size; i++)
		{
			if (_selectedEntityObjectGUI->_texture->getTextureID() == resourcesTexture[i]->getTextureID())
			{
				_selectedTextureIndex = i;
			}
		}

	}

	void __editorHierarchyOwn_addEntityObject(EntityObjectGUI* entityObjectGUIData)
	{
		_entityObjectGUI.push_back(entityObjectGUIData);
		
		++_differentEntityNameIndex;
	}

	void __editorHierarchyOwn_addNewEntityObject()
	{
		EntityObjectGUI* newEntity = new EntityObjectGUI;

		newEntity->_entity.name = "New entity " + std::to_string(_differentEntityNameIndex);
		newEntity->visibility = true;
		newEntity->_mesh = new Mesh(Mesh::DefaultGeometry::SQUARE);
		newEntity->_texture = resourcesTexture[(int)ResourcesTextureIndex::Glass];
		newEntity->_entity.child.clear();
		newEntity->_entity.parent = nullptr;

		_entityObjectGUI.push_back(newEntity);

		++_differentEntityNameIndex;
	}

	void __editorHierarchyOwn_defineWithChildSelectedState(EntityObjectGUI* entityObjectGUI)
	{

		if (ImGui::TreeNodeEx(entityObjectGUI->_entity.name.c_str(), (_selectedEntityObjectGUI == entityObjectGUI) ? (_entityHaveChild_Flags | ImGuiTreeNodeFlags_Selected) : _entityHaveChild_Flags))
		{
			for (size_t i = 0; i < entityObjectGUI->_entity.child.size(); i++)
			{
				//showEntityToList(parentEntity->_entity.child.findData(i), i);
			}
			ImGui::TreePop();
		}

	}

	void __editorHierarchyOwn_defineWithoutChildSelectedState(EntityObjectGUI* entityObjectGUI)
	{
		
		if (ImGui::TreeNodeEx(entityObjectGUI->_entity.name.c_str(), (_selectedEntityObjectGUI == entityObjectGUI) ? (_entityNullChild_Flags | ImGuiTreeNodeFlags_Selected) : _entityNullChild_Flags))
		{
			for (size_t i = 0; i < entityObjectGUI->_entity.child.size(); i++)
			{
				//showEntityToList(parentEntity->_entity.child.findData(i), i);
			}
		}

	}

	void __editorHierarchyOwn_showEntityToList(EntityObjectGUI* entityObjectGUI, int& index)
	{
		ImGui::Separator();

		ImGui::Checkbox("", &entityObjectGUI->visibility);
		ImGui::SameLine(); ImGui::Spacing();
		ImGui::SameLine();

		
		if (entityObjectGUI->_entity.child.size() != 0)
		{
			__editorHierarchyOwn_defineWithChildSelectedState(entityObjectGUI);
		}
		else
		{
			__editorHierarchyOwn_defineWithoutChildSelectedState(entityObjectGUI);
		}
		
		if (ImGui::IsItemClicked())
		{
			__editorHierarchyOwn_initSelectedEntityVariable(entityObjectGUI);
		}
		
		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
		{
			// Set payload to carry the index of our item (could be anything)
			ImGui::SetDragDropPayload("ENTITY_CELL", &index, sizeof(int));

			// Display preview (could be anything, e.g. when dragging an image we could decide to display
			// the filename and a small preview of the image, etc.)
			ImGui::Text("Move %s", entityObjectGUI->_entity.name.c_str());
			ImGui::EndDragDropSource();
		}

		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ENTITY_CELL"))
			{
				IM_ASSERT(payload->DataSize == sizeof(int));
				int payload_index = *(const int*)payload->Data;

				if ((index - payload_index) > 0)
					_entityObjectGUI.moveNode(payload_index, index, false);
				else
					_entityObjectGUI.moveNode(payload_index, index, true);

			}
			ImGui::EndDragDropTarget();
		}
		
		
	}

	void __editorHierarchyOwn_filterEntityName(EntityObjectGUI* entityObjectGUI, int& index)
	{
		if (_filter.PassFilter(entityObjectGUI->_entity.name.c_str()))
		{
			__editorHierarchyOwn_showEntityToList(entityObjectGUI, index);
			
		}

	}

	void showEditor_Hierarchy()
	{
		if (ImGui::Begin("Hierarchy"))
		{
			static int e = 0;
			ImGui::RadioButton("Move", &e, 0); ImGui::SameLine();
			ImGui::RadioButton("In To", &e, 1); ImGui::SameLine();
			ImGui::RadioButton("Out To", &e, 2);

			ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.7f, 0.6f, 0.6f));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.8f, 0.7f, 0.7f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.9f, 0.8f, 0.8f));
			if (ImGui::Button("+ Add New "))
			{
				__editorHierarchyOwn_addNewEntityObject();
			}
			ImGui::SameLine();
			ImGui::PopStyleColor(3);

			_filter.Draw();

			ImGui::Separator();

			ImGuiWindowFlags window_flags = ImGuiWindowFlags_::ImGuiWindowFlags_MenuBar;// | ImGuiWindowFlags_::ImGuiWindowFlags_NoScrollbar;
			ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
			ImGui::BeginChild("Entity", ImVec2(-FLT_MIN, -FLT_MIN), true, window_flags);
			{

				if (ImGui::BeginMenuBar())
				{
					ImGui::Text("Entities Hierarchy");
					ImGui::EndMenuBar();
				}

				for (int i = 0; i < _entityObjectGUI.size(); i++)
				{
					ImGui::PushID(i);
					__editorHierarchyOwn_filterEntityName(_entityObjectGUI.findData(i), i);
					ImGui::PopID();
				}

			}
			ImGui::EndChild();
			ImGui::PopStyleVar();

		}
		ImGui::End();


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


			if (ImGui::DragFloat3("Position", glm::value_ptr(_selectedTranslation), 0.1f, -FLT_MIN, -FLT_MIN, "%.3f")) {

				_selectedEntityObjectGUI->_entity.transform->setPosition(_selectedTranslation);
			}
			if (ImGui::DragFloat3("Rotation", glm::value_ptr(_selectedRotation), 0.1f, -FLT_MIN, -FLT_MIN, "%.3f")) {
				_selectedRotation.x = glm::mod<float>(_selectedRotation.x, 360.0f);
				_selectedRotation.y = glm::mod<float>(_selectedRotation.y, 360.0f);
				_selectedRotation.z = glm::mod<float>(_selectedRotation.z, 360.0f);

				_selectedEntityObjectGUI->_entity.transform->setRotationLocal(_selectedRotation);
			}
			if (ImGui::DragFloat3("Dimension", glm::value_ptr(_selectedDimension), 0.1f, -FLT_MIN, -FLT_MIN, "%.3f")) {

				_selectedEntityObjectGUI->_entity.transform->setDimensionLocal(_selectedDimension);
			}

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
							_selectedEntityObjectGUI->_mesh->setGeometryType(static_cast<Mesh::DefaultGeometry>(type));

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
							_selectedEntityObjectGUI->_texture = resourcesTexture[i];

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


				ImGui::Text("Name   : ");
				ImGui::SameLine();

				//static char buf[32] = u8"NIHONGO"; // <- this is how you would write it with C++11, using real kanjis
				if (ImGui::InputText("", _selectedEntityName.data(), _selectedEntityName.size()))
				{
					std::string s;
					for (char c : _selectedEntityName)
					{
						s += c;
					}
					_selectedEntityObjectGUI->_entity.name = s;
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
				__editorPropertyOwn_meshComponent();
			}
			ImGui::EndChild();

		}
		ImGui::End();

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

			static glm::mat4 mat;
			for (size_t i = 0; i < _entityObjectGUI.size(); i++)
			{
				EntityObjectGUI* temp = _entityObjectGUI.findData(i);

				mat = _camera->getProjectionMatrix() * _camera->getViewMatrix() * temp->_entity.transform->getModelMatrix();
				Shader::defaultDraw(mat);
				glBindTexture(GL_TEXTURE_2D, temp->_texture->getTextureID());

				glBindVertexArray(temp->_mesh->getVertexArrayObject()->vaoID);
				glDrawElements(GL_TRIANGLES, temp->_mesh->getVertexArrayObject()->indicesSize, GL_UNSIGNED_INT, 0);

			}

		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void showEditor_WorldEditor()
	{
		//Transform* tempTran = _entityObjectGUI.findData(0)->_entity.transform;
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

	void terminateEditor()
	{
		_selectedEntityObjectGUI = nullptr;
		_entityObjectGUI.clear();
		_selectedEntityName.clear();

		delete _screenTexture;
		delete _screenDepth;

		delete _camera;
	}

}
